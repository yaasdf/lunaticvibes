#include "asynclooper.h"
#include <numeric>
#include <chrono>
#include <plog/Log.h>

AsyncLooper::AsyncLooper(std::function<void()> func, unsigned rate_per_sec, bool single_inst) : _do(func), _single_inst(single_inst)
{
    _run = std::bind(single_inst ? &AsyncLooper::run_single : &AsyncLooper::run, this);
    _loopTimeBuffer.assign(LOOP_TIME_BUFFER_SIZE, 0);
    _bufferIt = _loopTimeBuffer.begin();
    
    _rate = rate_per_sec;
    _rateTime = 1000 / rate_per_sec;
}

AsyncLooper::~AsyncLooper()
{
    loopEnd();
    //if (_single_inst)
    //    std::unique_lock<decltype(_mutex)> _lock(_mutex);
}

void AsyncLooper::run()
{
    _do();
}

void AsyncLooper::run_single()
{
    //std::unique_lock<decltype(_mutex)> _lock(_mutex, std::try_to_lock);
    //if (_lock.owns_lock())
    //    _do();

    if (_in_do) return;

    _in_do = true;
    _do();
    _in_do = false;
}

unsigned AsyncLooper::getRate()
{
    return _rate;
}

void AsyncLooper::_recordLoopTime()
{
    auto current = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());

    // Skip first invoke
    if (_prevLoopTime == 0)
    {
        _prevLoopTime = current.count();
        return;
    }

    // ring-buffer simulation
    if (++_bufferIt == _loopTimeBuffer.end())
    {
        _bufferIt = _loopTimeBuffer.begin();
        _statReady = true;
    }

    // save duration from previous invoke
    *_bufferIt = current.count() - _prevLoopTime;
    _prevLoopTime = current.count();
}

unsigned AsyncLooper::getRateRealtime()
{
    auto sum = std::reduce(_loopTimeBuffer.begin(), _loopTimeBuffer.end());
    return (unsigned)(1000.0 / ((double)sum / LOOP_TIME_BUFFER_SIZE));
}

#if WIN32

typedef HANDLE LooperHandler;
VOID CALLBACK WaitOrTimerCallback(_In_ PVOID lpParameter, _In_ BOOLEAN TimerOrWaitFired)
{
    ((AsyncLooper*)lpParameter)->_run();
}

void AsyncLooper::loopStart()
{
    _running = CreateTimerQueueTimer(
        &handler,
        NULL, WaitOrTimerCallback,
        this,
        0,
        _rateTime,
        WT_EXECUTEDEFAULT
    );

    if (!_running)
    {
        LOG_DEBUG << "[Looper] Started with rate " << _rateTime;
    }
}

void AsyncLooper::loopEnd()
{
    if (!_running) return;

    if (DeleteTimerQueueTimer(NULL, handler, NULL))
    {
        // ..?
    }
    _running = false;
    LOG_DEBUG << "[Looper] Ended of rate " << _rateTime;
}

#elif LINUX

#else // FALLBACK
void AsyncLooper::_loopWithSleep()
{
    while (_running)
    {
        _run();
        std::this_thread::sleep_for(std::chrono::milliseconds(_rateTime));
    }
}

void AsyncLooper::loopStart()
{
    handler = std::thread(&AsyncLooper::loopWithSleep, this);
    _running = true;
}

void AsyncLooper::loopEnd()
{
    if (!_running) return;
    _running = false;
    handler.join();
}
#endif