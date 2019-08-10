#pragma once
#include "types.h"
#include "chart/chart.h"
#include "game/scroll/scroll.h"
#include "game/ruleset/ruleset.h"
#include <memory>
#include <string>

inline struct __chart_context_params
{
    Path path{};
    HashMD5 hash{};
    std::shared_ptr<vChart> chartObj{ nullptr };
    std::shared_ptr<vScroll> scrollObj{ nullptr };
    //bool isChartSamplesLoaded;
    bool isSampleLoaded = false;
    bool isBgaLoaded = false;
	bool started = false;

    // For displaying purpose, typically fetch from song db directly
    StringContent title{};
    StringContent title2{};
    StringContent artist{};
    StringContent artist2{};
    StringContent genre{};
    StringContent version{};
    double level = 0.0;

    BPM minBPM = 150;
    BPM itlBPM = 150;
    BPM maxBPM = 150;

} context_chart;

constexpr size_t MAX_PLAYERS = 8;
constexpr size_t PLAYER_SLOT_1P = 0;
constexpr size_t PLAYER_SLOT_2P = 1;
inline struct __play_context_params
{
    eMode mode = eMode::PLAY7;
    size_t playerSlot = PLAYER_SLOT_1P;  // 1P starts from 0
    unsigned judgeLevel = 0;

    std::shared_ptr<vScroll> scrollObj[2]{ nullptr, nullptr };

    // gauge/score graph key points
    // managed by SLOT, which includes local battle 1P/2P and multi battle player slots
    // maximum slot is MAX_PLAYERS
    std::array<std::vector<int>, MAX_PLAYERS> graphGauge;
    std::array<std::vector<int>, MAX_PLAYERS> graphScore;
    std::array<eGaugeOp, MAX_PLAYERS> gaugeType{};        // resolve on ruleset construction
    std::array<PlayMod, MAX_PLAYERS> mods{};         // eMod: 

    eRuleset rulesetType;
    std::array<std::shared_ptr<vRuleset>, MAX_PLAYERS> ruleset;

    timestamp remainTime;

} context_play;

void clearContextPlay();