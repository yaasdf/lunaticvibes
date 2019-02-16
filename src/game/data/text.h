#pragma once
#include "buffered_global.h"

enum class eText: unsigned
{
    INVALID = 0,           // should be initialized with ""

    TARGET_NAME = 1,
    PLAYER_NAME,

    PLAY_TITLE = 10,
    PLAY_SUBTITLE,
    PLAY_FULLTITLE,
    PLAY_GENRE,
    PLAY_ARTIST,
    PLAY_SUBARTIST,
    PLAY_TAG,
    PLAY_PLAYLEVEL,
    PLAY_DIFFICULTY,
    
    EDIT_TITLE = 20,
    EDIT_SUBTITLE,
    EDIT_FULLTITLE,
    EDIT_GENRE,
    EDIT_ARTIST,
    EDIT_SUBARTIST,
    EDIT_TAG,
    EDIT_PLAYLEVEL,
    EDIT_DIFFICULTY,
    EDIT_INSANE_LEVEL,
    EDIT_JUKEBOX_NAME,

    KEYCONFIG_SLOT1 = 40,
    KEYCONFIG_SLOT2,
    KEYCONFIG_SLOT3,
    KEYCONFIG_SLOT4,
    KEYCONFIG_SLOT5,
    KEYCONFIG_SLOT6,
    KEYCONFIG_SLOT7,
    KEYCONFIG_SLOT8,        // not defined
    KEYCONFIG_SLOT9,        // not defined

    SKIN_NAME = 50,
    SKIN_MAKER_NAME,

    PLAY_MODE = 60,         // #MODE, ALL KEYS, SINGLE, 7KEYS, 5KEYS, DOUBLE, 14KEYS, 10KEYS, 9KEYS, 
    SORT_MODE,              // #SORT, OFF, TITLE, LEVEL, FOLDER, CLEAR, RANK, 
    DIFFICULTY,             // #DIFFICULTY, ALL, EASY, STANDARD, HARD, EXPERT, ULTIMATE,

    RANDOM_1P,
    RANDOM_2P,
    GAUGE_1P,
    GAUGE_2P,
    ASSIST_1P,
    ASSIST_2P,
    BATTLE,
    FLIP,
    SCORE_GRAPH,
    GHOST,
    SHUTTER,
    SCROLL_TYPE,
    BGA_SIZE,
    BGA,
    COLOR_DEPTH,
    VSYNC,
    WINDOWMODE,             // Fullscreen, Windowed
    JUDGE_AUTO,
    REPLAY_SAVE_TYPE,
    TRIAL1,
    TRIAL2,
    EFFECT_1P,
    EFFECT_2P,

    スキンカスタマイズカテゴリ兆1��朕 = 100,
    スキンカスタマイズカテゴリ兆2��朕 = 101,
    スキンカスタマイズカテゴリ兆3��朕 = 102,
    スキンカスタマイズカテゴリ兆4��朕 = 103,
    スキンカスタマイズカテゴリ兆5��朕 = 104,
    スキンカスタマイズカテゴリ兆6��朕 = 105,
    スキンカスタマイズカテゴリ兆7��朕 = 106,
    スキンカスタマイズカテゴリ兆8��朕 = 107,
    スキンカスタマイズカテゴリ兆9��朕 = 108,
    スキンカスタマイズカテゴリ兆10��朕 = 109,

    スキンカスタマイズ��朕兆1��朕 = 110,
    スキンカスタマイズ��朕兆2��朕 = 111,
    スキンカスタマイズ��朕兆3��朕 = 112,
    スキンカスタマイズ��朕兆4��朕 = 113,
    スキンカスタマイズ��朕兆5��朕 = 114,
    スキンカスタマイズ��朕兆6��朕 = 115,
    スキンカスタマイズ��朕兆7��朕 = 116,
    スキンカスタマイズ��朕兆8��朕 = 117,
    スキンカスタマイズ��朕兆9��朕 = 118,
    スキンカスタマイズ��朕兆10��朕 = 119,

    ランキング燕プレイヤ�`兆1繁朕 = 120,
    ランキング燕プレイヤ�`兆2繁朕 = 121,
    ランキング燕プレイヤ�`兆3繁朕 = 122,
    ランキング燕プレイヤ�`兆4繁朕 = 123,
    ランキング燕プレイヤ�`兆5繁朕 = 124,
    ランキング燕プレイヤ�`兆6繁朕 = 125,
    ランキング燕プレイヤ�`兆7繁朕 = 126,
    ランキング燕プレイヤ�`兆8繁朕 = 127,
    ランキング燕プレイヤ�`兆9繁朕 = 128,
    ランキング燕プレイヤ�`兆10繁朕 = 129,

    クリア猟忖双���■�1 = 130,
    クリア猟忖双���■�2 = 131,

    コ�`ス爆タイトル1stage = 150,
    コ�`ス爆タイトル2stage = 151,
    コ�`ス爆タイトル3stage = 152,
    コ�`ス爆タイトル4stage = 153,
    コ�`ス爆タイトル5stage = 154,
    コ�`ス爆タイトル6stage = 155,
    コ�`ス爆タイトル7stage = 156,
    コ�`ス爆タイトル8stage = 157,
    コ�`ス爆タイトル9stage = 158,
    コ�`ス爆タイトル10stage = 159,

    コ�`ス爆サブタイトル1stage = 160,
    コ�`ス爆サブタイトル2stage = 161,
    コ�`ス爆サブタイトル3stage = 162,
    コ�`ス爆サブタイトル4stage = 163,
    コ�`ス爆サブタイトル5stage = 164,
    コ�`ス爆サブタイトル6stage = 165,
    コ�`ス爆サブタイトル7stage = 166,
    コ�`ス爆サブタイトル8stage = 167,
    コ�`ス爆サブタイトル9stage = 168,
    コ�`ス爆サブタイトル10stage = 169,

    コ�`スオプション�､�モ�`ドstage1��2 = 171,
    コ�`スオプション�､�モ�`ドstage2��3 = 172,
    コ�`スオプション�､�モ�`ドstage3��4 = 173,
    コ�`スオプション�､�モ�`ドstage4��5 = 174,
    コ�`スオプション�､�モ�`ドstage5��6 = 175,
    コ�`スオプション�､�モ�`ドstage6��7 = 176,
    コ�`スオプション�､�モ�`ドstage7��8 = 177,
    コ�`スオプション�､�モ�`ドstage8��9 = 178,
    コ�`スオプション�､�モ�`ドstage9��10 = 179,



    コ�`スオプションソフラン = 180,
    コ�`スオプションゲ�`ジタイプ = 181,
    コ�`スオプションオプション鋤峭 = 182,
    コ�`スオプションIR = 183,


    ランダムコ�`スオプション恷�mレベル = 190,

    ランダムコ�`スオプションレベル貧�� = 191,

    ランダムコ�`スオプションレベル和�� = 192,

    ランダムコ�`スオプションbpm���啖� = 193,

    ランダムコ�`スオプションbpm貧�� = 194,

    ランダムコ�`スオプションbpm和�� = 195,

    ランダムコ�`スオプションステ�`ジ方 = 196,

    畠悶コ�`スオプションデフォルトつなぎタイプ = 198,

    畠悶コ�`スオプションデフォルトゲ�`ジ = 199,


    TEXT_COUNT
};

inline buffered_global<eText, std::string, (size_t)eText::TEXT_COUNT> gTexts;