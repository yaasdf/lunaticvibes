#pragma once
#include <vector>
#include <array>
#include <bitset>
#include <map>
#include <functional>
#include "input_keys.h"

namespace Input
{
    enum DeviceType
    {
        KEYBOARD = 0,
        JOYSTICK,
        CONTROLLER,
        MOUSE,          // ???
    };

    typedef size_t DeviceID;
    struct KeyMap
    {
        DeviceType  type;
        DeviceID    device;
        Key		    key;
    };

    const std::size_t MAX_JOYSTICK_COUNT = 8;
    const std::size_t MAX_BINDINGS_PER_KEY = 10;
    typedef std::array<KeyMap, MAX_BINDINGS_PER_KEY> Binding;

};

////////////////////////////////////////////////////////////////////////////////
// Input manager
// fetch real-time system keyscan status
// Do not use this class directly. Use InputWrapper instead.
class InputMgr
{
private:
    static InputMgr _inst;
    InputMgr() = default;
    ~InputMgr() = default;

public:

    // Game keys param / functions
private:
    std::bitset<Input::MAX_JOYSTICK_COUNT> joysticksConnected{};
    std::array<Input::Binding, Input::ESC> bindings{};
	bool haveJoystick = false;
	int analogDeadZone = 25;

public:
    // Game keys param / functions
    static void updateDevices();
    static void updateBindings(Input::Ingame K);
    static std::bitset<Input::KEY_COUNT> detect();

};

////////////////////////////////////////////////////////////////////////////////
// System specific range

extern const std::array<std::string, 0xFF> keyNameMap;

// Keyboard detect
bool isKeyPressed(Input::Key c);

// Joystick detect
typedef int JoyBtn;
//bool isButtonPressed(Device d, Button b);