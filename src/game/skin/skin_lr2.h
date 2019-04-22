#pragma once
#include <array>
#include <variant>
#include <filesystem>
#include <bitset>
#include <map>
#include <functional>
#include "types.h"
#include "skin.h"
#include "game/graphics/sprite_lane.h"
#include "game/input/input_mgr.h"
#include "game/data/switch.h"

namespace LR2
{
	enum gr_
	{
        NOTFOUND = -1,
		STAGEFILE = 101,
		BACKBMP,
		BANNER,
		SKIN_THUMBNAIL = 106,
		BLACK_DOT = 111,
		WHITE_DOT
	};

	enum blend
	{
		TRANSCOLOR = 0,

		ALPHA = 1,
		ADD,
		SUBTRACT,
		MULTIPLY,

		XOR = 6,

		MULTIPLY_ANTI_BACKGROUND = 9,
		ANTI_COLOR = 10,
		MULTIPLY_WITH_ALPHA = 11

	};

	// unsigned
	enum timer
	{
		SCENE_START = 0,
		INPUT_START,
		FADEOUT,
		STAGE_FAILED,
		//INPUT_END,

		LIST_MOVING = 10,
		SONG_CHANGE,
		LIST_MOVING_UP,
		LIST_MOVING_DOWN,
		LIST_STOP,
		README_START,
		README_STOP,
		COURSE_SELECT_START,
		COURSE_SELECT_STOP,

		// Option menu panels
		PANEL1_ON = 21,
		PANEL2_ON,
		PANEL3_ON,
		PANEL4_ON,
		PANEL5_ON,
		PANEL6_ON,
		PANEL7_ON,
		PANEL8_ON,
		PANEL9_ON,

		PANEL1_OFF = 31,
		PANEL2_OFF,
		PANEL3_OFF,
		PANEL4_OFF,
		PANEL5_OFF,
		PANEL6_OFF,
		PANEL7_OFF,
		PANEL8_OFF,
		PANEL9_OFF,

		LOAD_FINISH = 40,
		PLAY_START,
		HP_UP_1P,
		HP_UP_2P,
		HP_MAX_1P,
		HP_MAX_2P,
		JUDGE_1P,
		JUDGE_2P,
		FULLCOMBO_1P,
		FULLCOMBO_2P,

		// bomb
		HITEFFECT_SCR_1P = 50,
		HITEFFECT_1_1P,
		HITEFFECT_2_1P,
		HITEFFECT_3_1P,
		HITEFFECT_4_1P,
		HITEFFECT_5_1P,
		HITEFFECT_6_1P,
		HITEFFECT_7_1P,
		HITEFFECT_8_1P,
		HITEFFECT_9_1P,

		HITEFFECT_SCR_2P = 60,
		HITEFFECT_1_2P,
		HITEFFECT_2_2P,
		HITEFFECT_3_2P,
		HITEFFECT_4_2P,
		HITEFFECT_5_2P,
		HITEFFECT_6_2P,
		HITEFFECT_7_2P,
		HITEFFECT_8_2P,
		HITEFFECT_9_2P,

		LONGEFFECT_SCR_1P = 70,
		LONGEFFECT_1_1P,
		LONGEFFECT_2_1P,
		LONGEFFECT_3_1P,
		LONGEFFECT_4_1P,
		LONGEFFECT_5_1P,
		LONGEFFECT_6_1P,
		LONGEFFECT_7_1P,
		LONGEFFECT_8_1P,
		LONGEFFECT_9_1P,

		LONGEFFECT_SCR_2P = 80,
		LONGEFFECT_1_2P,
		LONGEFFECT_2_2P,
		LONGEFFECT_3_2P,
		LONGEFFECT_4_2P,
		LONGEFFECT_5_2P,
		LONGEFFECT_6_2P,
		LONGEFFECT_7_2P,
		LONGEFFECT_8_2P,
		LONGEFFECT_9_2P,

		KEY_ON_SCR_1P = 100,
		KEY_ON_1_1P,
		KEY_ON_2_1P,
		KEY_ON_3_1P,
		KEY_ON_4_1P,
		KEY_ON_5_1P,
		KEY_ON_6_1P,
		KEY_ON_7_1P,
		KEY_ON_8_1P,
		KEY_ON_9_1P,

		KEY_ON_SCR_2P = 110,
		KEY_ON_1_2P,
		KEY_ON_2_2P,
		KEY_ON_3_2P,
		KEY_ON_4_2P,
		KEY_ON_5_2P,
		KEY_ON_6_2P,
		KEY_ON_7_2P,
		KEY_ON_8_2P,
		KEY_ON_9_2P,

		KEY_OFF_SCR_1P = 120,
		KEY_OFF_1_1P,
		KEY_OFF_2_1P,
		KEY_OFF_3_1P,
		KEY_OFF_4_1P,
		KEY_OFF_5_1P,
		KEY_OFF_6_1P,
		KEY_OFF_7_1P,
		KEY_OFF_8_1P,
		KEY_OFF_9_1P,

		KEY_OFF_SCR_2P = 130,
		KEY_OFF_1_2P,
		KEY_OFF_2_2P,
		KEY_OFF_3_2P,
		KEY_OFF_4_2P,
		KEY_OFF_5_2P,
		KEY_OFF_6_2P,
		KEY_OFF_7_2P,
		KEY_OFF_8_2P,
		KEY_OFF_9_2P,

		BEAT_PROGRESS = 140,

		LAST_NOTE_JUDGE_1P = 143,
		LAST_NOTE_JUDGE_2P,

		RESULT_START = 150,
		RESULT_RANK,
		RESULT_HIGHSCORE,

		DATABASE_LOADING = 170,
		DATABASE_LOAD_END,

		IR_CONNECT = 172,
		IR_SUCCESS,
		IR_FAILED_TIMER,

		COURSE_EDITOR_START = 180,
		COURSE_EDITOR_END,

		TIMER_COUNT
	};
	
	// bool
	enum dst_option
	{
		DST_TRUE = 0,

		// song select
		SELECT_SELECTING_FOLDER = 1,
		SELECT_SELECTING_SONG,
		SELECT_SELECTING_COURSE,
		SELECT_SELECTING_NEW_COURSE,
		SELECT_SELECTING_PLAYABLE,

		// mode
		PLAY_DOUBLE = 10,
		PLAY_BATTLE,
		DOUBLE_OR_BATTLE,
		GHOST_OR_BATTLE,

		NO_PANEL = 20,
		PANEL1,
		PANEL2,
		PANEL3,
		PANEL4,
		PANEL5,
		PANEL6,
		PANEL7,
		PANEL8,
		PANEL9,

		// system settings
		SYSTEM_BGA_NORMAL = 30,
		SYSTEM_BGA_EXTEND,
		SYSTEM_AUTOPLAY_OFF,
		SYSTEM_AUTOPLAY_ON,
		SYSTEM_GHOST_OFF,
		SYSTEM_GHOST_TYPE_A,
		SYSTEM_GHOST_TYPE_B,
		SYSTEM_GHOST_TYPE_C,
		SYSTEM_SCOREGRAPH_OFF,
		SYSTEM_SCOREGRAPH_ON,
		SYSTEM_BGA_OFF,
		SYSTEM_BGA_ON,

		NORMAL_GAUGE_1P,
		HARD_GAUGE_1P,
		NORMAL_GAUGE_2P,
		HARD_GAUGE_2P,

		DIFF_FILTER_ON,
		DIFF_FILTER_OFF,

		// infos
		OFFLINE = 50,
		ONLINE,

		EXTRA_MODE_OFF,
		EXTRA_MODE_ON,

		AUTO_SCRATCH_1P_OFF,
		AUTO_SCRATCH_1P_ON,
		AUTO_SCRATCH_2P_OFF,
		AUTO_SCRATCH_2P_ON,

		SCORE_NOSAVE = 60,
		SCORE_SAVE,
		CLEAR_NOSAVE,
		CLEAR_SAVE_EASY,
		CLEAR_SAVE_NORMAL,
		CLEAR_SAVE_HARD,
		CLEAR_FULLCOMBO_ONLY,

		LEVEL_INRANGE_BEGINNER = 70,
		LEVEL_INRANGE_NORMAL,
		LEVEL_INRANGE_HYPER,
		LEVEL_INRANGE_ANOTHER,
		LEVEL_INRANGE_INSANE,
		LEVEL_OVERFLOW_BEGINNER,
		LEVEL_OVERFLOW_NORMAL,
		LEVEL_OVERFLOW_HYPER,
		LEVEL_OVERFLOW_ANOTHER,
		LEVEL_OVERFLOW_INSANE,

		LOADING = 80,
		LOAD_FINISHED,

		REPLAY_OFF = 82,
		REPLAY_RECORDING,
		REPLAY_PLAYING,

		RESULT_CLEAR = 90,
		RESULT_FAILED,

		// song list status
		CHART_NOPLAY = 100,
		CHART_FAILED,
		CHART_EASY,
		CHART_NORMAL,
		CHART_HARD,
		CHART_FULLCOMBO,

		CHART_AAA = 110,
		CHART_AA,
		CHART_A,
		CHART_B,
		CHART_C,
		CHART_D,
		CHART_E,
		CHART_F,

		// Clear option flag
		CHART_CLEARED_GAUGE_NORMAL = 118,
		CHART_CLEARED_GAUGE_HARD,
		CHART_CLEARED_GAUGE_DEATH,
		CHART_CLEARED_GAUGE_EASY,
		CHART_CLEARED_GAUGE_PATTACK,
		CHART_CLEARED_GAUGE_GATTACK,

		CHART_CLEARED_SHUFFLE_OFF = 126,
		CHART_CLEARED_SHUFFLE_MIRROR,
		CHART_CLEARED_SHUFFLE_RANDOM,
		CHART_CLEARED_SHUFFLE_SRANDOM,
		CHART_CLEARED_SHUFFLE_HRANDOM,
		CHART_CLEARED_SHUFFLE_ALLSCR,

		CHART_CLEARED_EFFECT_OFF = 134,
		CHART_CLEARED_EFFECT_HIDDEN,
		CHART_CLEARED_EFFECT_SUDDEN,
		CHART_CLEARED_EFFECT_HIDSUD,

		CHART_CLEARED_ETC_AUTOSCR = 142,
		CHART_CLEARED_ETC_EXTRAMODE,
		CHART_CLEARED_ETC_DOUBLEBATTLE,
		CHART_CLEARED_ETC_SPTODP,

		// metadata
		CHART_DIFF_NONSET = 150,
		CHART_DIFF_EASY,
		CHART_DIFF_NORMAL,
		CHART_DIFF_HYPER,
		CHART_DIFF_ANOTHER,
		CHART_DIFF_INSANE,

		CHART_MODE_7KEYS = 160,
		CHART_MODE_5KEYS,
		CHART_MODE_14KEYS,
		CHART_MODE_10KEYS,
		CHART_MODE_9KEYS,

		// play mode after applying mods
		CHART_PLAYMODE_7KEYS = 165,
		CHART_PLAYMODE_5KEYS,
		CHART_PLAYMODE_14KEYS,
		CHART_PLAYMODE_10KEYS,
		CHART_PLAYMODE_9KEYS,

		CHART_NO_BGA = 170,
		CHART_HAVE_BGA,
		CHART_NO_LN,
		CHART_HAVE_LN,
		CHART_NO_README,
		CHART_HAVE_README,
		CHART_NO_BPMCHANGE,
		CHART_HAVE_BPMCHANGE,
		CHART_NO_RANDOM,
		CHART_HAVE_RANDOM,

		CHART_JUDGE_VHARD = 180,
		CHART_JUDGE_HARD,
		CHART_JUDGE_NORMAL,
		CHART_JUDGE_EASY,

		CHART_LEVEL_INRANGE = 185,
		CHART_LEVEL_OVERFLOW,

		CHART_NO_STAGEFILE = 190,
		CHART_HAVE_STAGEFILE,
		CHART_NO_BANNER,
		CHART_HAVE_BANNER,
		CHART_NO_BACKBMP,
		CHART_HAVE_BACKBMP,

		CHART_NO_REPLAY,
		CHART_HAVE_REPLAY,

		// Playing
		PLAY_AAA_1P = 200,
		PLAY_AA_1P,
		PLAY_A_1P,
		PLAY_B_1P,
		PLAY_C_1P,
		PLAY_D_1P,
		PLAY_E_1P,
		PLAY_F_1P,

		PLAY_AAA_2P = 210,
		PLAY_AA_2P,
		PLAY_A_2P,
		PLAY_B_2P,
		PLAY_C_2P,
		PLAY_D_2P,
		PLAY_E_2P,
		PLAY_F_2P,

		PLAY_ABOVE_AAA = 220,
		PLAY_ABOVE_AA,
		PLAY_ABOVE_A,
		PLAY_ABOVE_B,
		PLAY_ABOVE_C,
		PLAY_ABOVE_D,
		PLAY_ABOVE_E,
		PLAY_ABOVE_F,

		PLAY_0p_TO_10p_1P = 230,
		PLAY_10p_TO_19p_1P,
		PLAY_20p_TO_29p_1P,
		PLAY_30p_TO_39p_1P,
		PLAY_40p_TO_49p_1P,
		PLAY_50p_TO_59p_1P,
		PLAY_60p_TO_69p_1P,
		PLAY_70p_TO_79p_1P,
		PLAY_80p_TO_89p_1P,
		PLAY_90p_TO_99p_1P,
		PLAY_100p_1P,

		PLAY_PERFECT_1P = 241,
		PLAY_GREAT_1P,
		PLAY_GOOD_1P,
		PLAY_BAD_1P,
		PLAY_POOR_1P,
		PLAY_BPOOR_1P,

		//公式ハーフスキンの左右のネオン用です 2P側も
		PLAY_POORBGA_NOT_INTIME_1P = 247,
		PLAY_POORBGA_INTIME_1P,

		PLAY_0p_TO_10p_2P = 250,
		PLAY_10p_TO_19p_2P,
		PLAY_20p_TO_29p_2P,
		PLAY_30p_TO_39p_2P,
		PLAY_40p_TO_49p_2P,
		PLAY_50p_TO_59p_2P,
		PLAY_60p_TO_69p_2P,
		PLAY_70p_TO_79p_2P,
		PLAY_80p_TO_89p_2P,
		PLAY_90p_TO_99p_2P,
		PLAY_100p_2P,

		PLAY_PERFECT_2P = 261,
		PLAY_GREAT_2P,
		PLAY_GOOD_2P,
		PLAY_BAD_2P,
		PLAY_POOR_2P,
		PLAY_BPOOR_2P,

		PLAY_POORBGA_NOT_INTIME_2P = 267,
		PLAY_POORBGA_INTIME_2P,

		PLAY_CHANGING_LANECOVER_1P = 270,
		PLAY_CHANGING_LANECOVER_2P,

		PLAY_STAGE1 = 280,
		PLAY_STAGE2,
		PLAY_STAGE3,
		PLAY_STAGE4,
		//PLAY_STAGE5,
		//PLAY_STAGE6,
		//PLAY_STAGE7,
		//PLAY_STAGE8,
		//PLAY_STAGE9,
		PLAY_STAGEFINAL = 289,

		PLAY_MODE_COURSE = 290,
		PLAY_MODE_NONSTOP,
		PLAY_MODE_EXHARD,
		PLAY_MODE_SKILLANALYSIS,

		// Result
		RESULT_AAA_1P = 300,
		RESULT_AA_1P,
		RESULT_A_1P,
		RESULT_B_1P,
		RESULT_C_1P,
		RESULT_D_1P,
		RESULT_E_1P,
		RESULT_F_1P,
		RESULT_0_1P,

		RESULT_AAA_2P = 310,
		RESULT_AA_2P,
		RESULT_A_2P,
		RESULT_B_2P,
		RESULT_C_2P,
		RESULT_D_2P,
		RESULT_E_2P,
		RESULT_F_2P,
		RESULT_0_2P,

		RESULT_MYBEST_AAA = 320,
		RESULT_MYBEST_AA,
		RESULT_MYBEST_A,
		RESULT_MYBEST_B,
		RESULT_MYBEST_C,
		RESULT_MYBEST_D,
		RESULT_MYBEST_E,
		RESULT_MYBEST_F,

		RESULT_スコアが更新された = 330,
		RESULT_MAXCOMBOが更新された,
		RESULT_最小BPが更新された,
		RESULT_トライアルが更新された,
		RESULT_IRの順位が更新された,
		RESULT_スコアランクが更新された,

		RESULT_UPDATE_AAA = 340,
		RESULT_UPDATE_AA,
		RESULT_UPDATE_A,
		RESULT_UPDATE_B,
		RESULT_UPDATE_C,
		RESULT_UPDATE_D,
		RESULT_UPDATE_E,
		RESULT_UPDATE_F,

		RESULT_リザルトフリップ無効 = 350,
		RESULT_リザルトフリップ有効,

		RESULT_1PWIN_2PLOSE = 352,
		RESULT_1PLOSE_2PWIN,
		RESULT_DRAW,

		// Key config
		KEYCONFIG_7KEYS = 400,
		KEYCONFIG_9KEYS,
		KEYCONFIG_5KEYS,

		// Others
		SELECT_NO_BEGINNER_IN_SAME_FOLDER = 500,
		SELECT_NO_NORMAL_IN_SAME_FOLDER,
		SELECT_NO_HYPER_IN_SAME_FOLDER,
		SELECT_NO_ANOTHER_IN_SAME_FOLDER,
		SELECT_NO_INSANE_IN_SAME_FOLDER,

		SELECT_HAVE_BEGINNER_IN_SAME_FOLDER = 505,
		SELECT_HAVE_NORMAL_IN_SAME_FOLDER,
		SELECT_HAVE_HYPER_IN_SAME_FOLDER,
		SELECT_HAVE_ANOTHER_IN_SAME_FOLDER,
		SELECT_HAVE_INSANE_IN_SAME_FOLDER,

		SELECT_HAVE_ONE_BEGINNER_IN_SAME_FOLDER = 510,
		SELECT_HAVE_ONE_NORMAL_IN_SAME_FOLDER,
		SELECT_HAVE_ONE_HYPER_IN_SAME_FOLDER,
		SELECT_HAVE_ONE_ANOTHER_IN_SAME_FOLDER,
		SELECT_HAVE_ONE_NSANE_IN_SAME_FOLDER,

		SELECT_HAVE_COUPLE_BEGINNER_IN_SAME_FOLDER = 515,
		SELECT_HAVE_COUPLE_NORMAL_IN_SAME_FOLDER,
		SELECT_HAVE_COUPLE_HYPER_IN_SAME_FOLDER,
		SELECT_HAVE_COUPLE_ANOTHER_IN_SAME_FOLDER,
		SELECT_HAVE_COUPLE_NSANE_IN_SAME_FOLDER,

		SELECT_SCOREBAR_BEGINNER_NO_PLAY = 520,
		SELECT_SCOREBAR_BEGINNER_FAILED,
		SELECT_SCOREBAR_BEGINNER_EASY,
		SELECT_SCOREBAR_BEGINNER_CLEAR,
		SELECT_SCOREBAR_BEGINNER_HARDCLEAR,
		SELECT_SCOREBAR_BEGINNER_FULLCOMBO,

		SELECT_SCOREBAR_NORMAL_NO_PLAY = 530,
		SELECT_SCOREBAR_NORMAL_FAILED,
		SELECT_SCOREBAR_NORMAL_EASY,
		SELECT_SCOREBAR_NORMAL_CLEAR,
		SELECT_SCOREBAR_NORMAL_HARDCLEAR,
		SELECT_SCOREBAR_NORMAL_FULLCOMBO,

		SELECT_SCOREBAR_HYPER_NO_PLAY = 540,
		SELECT_SCOREBAR_HYPER_FAILED,
		SELECT_SCOREBAR_HYPER_EASY,
		SELECT_SCOREBAR_HYPER_CLEAR,
		SELECT_SCOREBAR_HYPER_HARDCLEAR,
		SELECT_SCOREBAR_HYPER_FULLCOMBO,

		SELECT_SCOREBAR_ANOTHER_NO_PLAY = 550,
		SELECT_SCOREBAR_ANOTHER_FAILED,
		SELECT_SCOREBAR_ANOTHER_EASY,
		SELECT_SCOREBAR_ANOTHER_CLEAR,
		SELECT_SCOREBAR_ANOTHER_HARDCLEAR,
		SELECT_SCOREBAR_ANOTHER_FULLCOMBO,

		SELECT_SCOREBAR_INSANE_NO_PLAY = 560,
		SELECT_SCOREBAR_INSANE_FAILED,
		SELECT_SCOREBAR_INSANE_EASY,
		SELECT_SCOREBAR_INSANE_CLEAR,
		SELECT_SCOREBAR_INSANE_HARDCLEAR,
		SELECT_SCOREBAR_INSANE_FULLCOMBO,


		/////////////////////////////////////
		//　コースセレクト関連

		MODE_COURSESELECT = 571,
		MODE_NOT_COURSESELECT,

		COURSE_STAGE_MORE_THAN_1 = 580,
		COURSE_STAGE_MORE_THAN_2,
		COURSE_STAGE_MORE_THAN_3,
		COURSE_STAGE_MORE_THAN_4,
		COURSE_STAGE_MORE_THAN_5,
		COURSE_STAGE_MORE_THAN_6,
		COURSE_STAGE_MORE_THAN_7,
		COURSE_STAGE_MORE_THAN_8,
		COURSE_STAGE_MORE_THAN_9,
		COURSE_STAGE_MORE_THAN_10,

		COURSESELECT_SELECTING_STAGE1 = 590,
		COURSESELECT_SELECTING_STAGE2,
		COURSESELECT_SELECTING_STAGE3,
		COURSESELECT_SELECTING_STAGE4,
		COURSESELECT_SELECTING_STAGE5,
		COURSESELECT_SELECTING_STAGE6,
		COURSESELECT_SELECTING_STAGE7,
		COURSESELECT_SELECTING_STAGE8,
		COURSESELECT_SELECTING_STAGE9,
		COURSESELECT_SELECTING_STAGE10,

		//LR2IR
		IR_対象ではない = 600,  //???
		IR_LOADING,
		IR_LOAD_COMPLETE,
		IR_NO_PLAYER,
		IR_FAILED,
		IR_BANNED_CHART,
		IR_WAITING_FOR_UPDATE,
		IR_ACCESS,
		IR_BUSY,

		IR_NOT_SHOWING_RANKING = 620,
		IR_SHOWING_RANKING,

		IR_NOT_IN_GHOSTBATTLE = 622,
		IR_IN_GHOSTBATTLE,

		IR_自分と相手のスコアを比較する状況ではない = 624,	//現状では、ランキング表示中とライバルフォルダ
		IR_自分と相手のスコアを比較するべき状況である,

		IR_RIVAL_NOPLAY = 640,
		IR_RIVAL_FAILED,
		IR_RIVAL_EASY_CLEARED,
		IR_RIVAL_NORMAL_CLEARED,
		IR_RIVAL_HARD_CLEARED,
		IR_RIVAL_FULL_COMBO,

		IR_RIVAL_AAA = 650,
		IR_RIVAL_AA,
		IR_RIVAL_A,
		IR_RIVAL_B,
		IR_RIVAL_C,
		IR_RIVAL_D,
		IR_RIVAL_E,
		IR_RIVAL_F,


		//COURSE_STAGE1
		COURSE_STAGE1_DIFF_NONSET = 700,
		COURSE_STAGE1_DIFF_BEGINNER,
		COURSE_STAGE1_DIFF_NORMAL,
		COURSE_STAGE1_DIFF_HYPER,
		COURSE_STAGE1_DIFF_ANOTHER,
		COURSE_STAGE1_DIFF_INSANE,

		//COURSE_STAGE2
		COURSE_STAGE2_DIFF_NONSET = 710,
		COURSE_STAGE2_DIFF_BEGINNER,
		COURSE_STAGE2_DIFF_NORMAL,
		COURSE_STAGE2_DIFF_HYPER,
		COURSE_STAGE2_DIFF_ANOTHER,
		COURSE_STAGE2_DIFF_INSANE,

		//COURSE_STAGE3
		COURSE_STAGE3_DIFF_NONSET = 720,
		COURSE_STAGE3_DIFF_BEGINNER,
		COURSE_STAGE3_DIFF_NORMAL,
		COURSE_STAGE3_DIFF_HYPER,
		COURSE_STAGE3_DIFF_ANOTHER,
		COURSE_STAGE3_DIFF_INSANE,

		//COURSE_STAGE4
		COURSE_STAGE4_DIFF_NONSET = 730,
		COURSE_STAGE4_DIFF_BEGINNER,
		COURSE_STAGE4_DIFF_NORMAL,
		COURSE_STAGE4_DIFF_HYPER,
		COURSE_STAGE4_DIFF_ANOTHER,
		COURSE_STAGE4_DIFF_INSANE,

		//COURSE_STAGE5
		COURSE_STAGE5_DIFF_NONSET = 740,
		COURSE_STAGE5_DIFF_BEGINNER,
		COURSE_STAGE5_DIFF_NORMAL,
		COURSE_STAGE5_DIFF_HYPER,
		COURSE_STAGE5_DIFF_ANOTHER,
		COURSE_STAGE5_DIFF_INSANE,
		DST_FALSE = 999,

		DST_OPTION_COUNT
	};
	
	// int
	enum num
	{

		// play options
		HISPEED_1P = 10,
		HISPEED_2P = 11,

		JUDGE_TIMING = 12,
		DEFAULT_TARGET_RATE = 13,

		LANECOVER_1P = 14,
		LANECOVER_2P = 15,

		// random stuff
		FPS = 20,

		YEAR = 21,
		MONTH = 22,
		DAY = 23,
		HOUR = 24,
		MIN = 25,
		SEC = 26,

		// Player Status

		TOTAL_PLAY_COUNT = 30,
		TOTAL_CLEAR_COUNT,
		TOTAL_FAIL_COUNT,

		TOTAL_PERFECT,
		TOTAL_GREAT,
		TOTAL_GOOD,
		TOTAL_BAD,
		TOTAL_POOR,

		RUNNING_COMBO,
		RUNNING_COMBO_MAX,

		TRIAL_LEVEL,
		TRIAL_LEVEL_MINUS_1,

		LEVEL_OF_BEGINNER_CHART_FROM_SAME_FOLDER = 45,
		LEVEL_OF_NORMAL_CHART_FROM_SAME_FOLDER,
		LEVEL_OF_HYPER_CHART_FROM_SAME_FOLDER,
		LEVEL_OF_ANOTHER_CHART_FROM_SAME_FOLDER,
		LEVEL_OF_INSANE_CHART_FROM_SAME_FOLDER,

		// Effector
		EQ0 = 50,
		EQ1,
		EQ2,
		EQ3,
		EQ4,
		EQ5,
		EQ6,

		MASTER_VOLUME,
		KEY_VOLUME,
		BGM_VOLUME,

		FX0_P1,
		FX0_P2,
		FX1_P1,
		FX1_P2,
		FX2_P1,
		FX2_P2,

		PITCH,

		//選曲時,
		SELECT_SCORE = 70,
		SELECT_EXSCORE,
		SELECT_MAX_EXSCORE,
		SELECT_RATE,
		SELECT_TOTALNOTES,
		SELECT_MAXCOMBO,
		SELECT_MIN_BP,
		SELECT_PLAYCOUNT,
		SELECT_CLEAR,
		SELECT_FAIL,

		SELECT_PERFECT,
		SELECT_GREAT,
		SELECT_GOOD,
		SELECT_BAD,
		SELECT_POOR,
		SELECT_PERFECT_PERCENT,
		SELECT_GREAT_PERCENT,
		SELECT_GOOD_PERCENT,
		SELECT_BAD_PERCENT,
		SELECT_POOR_PERCENT,

		SELECT_BPM_MAX,
		SELECT_BPM_MIN,

		SELECT_IR_RANK,
		SELECT_IR_TOTALPLAYER,
		SELECT_IR_CLEARRATE,

		SELECT_IR_RIVAL_DELTA,

		//BMSプレイ時,

		//1P,
		SCORE = 100,
		EXSCORE,
		RATE,
		RATE_DECIMAL2,
		NOWCOMBO,
		MAXCOMBO,
		TOTALNOTES,
		GROOVEGAUGE,
		EXSCORE_DELTA,
		PERFECT,
		GREAT,
		GOOD,
		BAD,
		POOR,
		TOTAL_RATE,
		TOTAL_RATE_DECIMAL2,

		//対戦相手ORゴースト,
		RIVAL_SCORE = 120,
		RIVAL_EXSCORE,
		RIVAL_RATE,
		RIVAL_RATE_DECIMAL2,
		RIVAL_NOWCOMBO,
		RIVAL_MAXCOMBO,
		RIVAL_TOTALNOTES,
		RIVAL_GROOVEGAUGE,
		RIVAL_EXSCORE_DELTA,
		RIVAL_PERFECT,
		RIVAL_GREAT,
		RIVAL_GOOD,
		RIVAL_BAD,
		RIVAL_POOR,
		RIVAL_TOTAL_RATE,
		RIVAL_TOTAL_RATE_DECIMAL2,

		//120-139は設定によってハイスコアかゴーストか不定なので、スコアグラフ上で指定して表示する場合,
		//リザルトで使用する場合は#DISABLEFLIP必須,
		ハイスコア現在値 = 150,
		ターゲット現在値,
		ハイスコアと1Pスコアの差,
		ターゲットと1Pスコアの差,
		次のランクとの差,
		ハイスコアRATE,
		ハイスコアRATE小数点2桁,
		ターゲットRATE,
		ターゲットRATE小数点2桁,

		//BMSの状態,
		BMS_BPM = 160,
		BMS_MIN,
		BMS_SEC,
		BMS_REMAIN_MIN,
		BMS_REMAIN_SEC,
		LOAD_PROGRESS,

		//リザのハイスコア表示用,
		RESULT_EXSCORE_MYBEST = 170,
		RESULT_EXSCORE,
		RESULT_EXSCORE_DELTA,
		
		RESULT_MAXCOMBO_MYBEST,
		RESULT_MAXCOMBO,
		RESULT_MAXCOMBO_DELTA,
		
		RESULT_BP_MYBEST,
		RESULT_BP,
		RESULT_BP_DELTA,
		
		RESULT_IR_RANK,
		RESULT_IR_TOTALPLAYER,
		RESULT_IR_CLEARRATE,
		RESULT_IR_RANK__MYBEST,
		
		RESULT_RATE_MYBEST,
		RESULT_RATE_MYBEST_DECIMAL2,

		//IR(BETA3以降用),

		IR_TOTALPLAYER = 200,
		IR_TOTALPLAYS__FASTSLOW_JUDGE_DELTA,

		FAILED_PLAYER_COUNT__FASTSLOW = 210,
		FAILED_PROPORTION,
		EASY_PLAYER_COUNT__FAST_COUNT,
		EASY_PROPORTION,
		CLEAR_PLAYER_COUNT__SLOW_COUNT,
		CLEAR_PROPORTION,
		HARD_PLAYER_COUNT,
		HARD_PROPORTION,
		FULLCOMBO_PLAYER_COUNT,
		FULLCOMBO_PROPORTION,

		IR自動更新までの残り時間 = 220,

		COURSE_STAGE1 = 250,
		COURSE_STAGE2,
		COURSE_STAGE3,
		COURSE_STAGE4,
		COURSE_STAGE5,


		//選曲時ライバル,
		SELECT_RIVAL_SCORE = 270,
		SELECT_RIVAL_EXSCORE,
		SELECT_RIVAL_MAX_EXSCORE,
		SELECT_RIVAL_RATE,
		SELECT_RIVAL_TOTALNOTES,
		SELECT_RIVAL_MAXCOMBO,
		SELECT_RIVAL_MIN_BP,
		SELECT_RIVAL_PLAYCOUNT,
		SELECT_RIVAL_CLEAR,
		SELECT_RIVAL_FAIL,
		SELECT_RIVAL_PERFECT,
		SELECT_RIVAL_GREAT,
		SELECT_RIVAL_GOOD,
		SELECT_RIVAL_BAD,
		SELECT_RIVAL_POOR,
		SELECT_RIVAL_PERFECT_PERCENT,
		SELECT_RIVAL_GREAT_PERCENT,
		SELECT_RIVAL_GOOD_PERCENT,
		SELECT_RIVAL_BAD_PERCENT,
		SELECT_RIVAL_POOR_PERCENT,

		SELECT_RIVAL_BPM_MAX,
		SELECT_RIVAL_BPM_MIN,

		SELECT_RIVAL_IR_RANK,
		SELECT_RIVAL_IR_TOTALPLAYER,
		SELECT_RIVAL_IR_CLEARRATE,

		NUM_COUNT
	};

	// unsigned
	enum slider
	{
		SELECT_POSITION = 1,

		SLIDER_HISPEED_1P = 2,
		SLIDER_HISPEED_2P,

		SLIDER_LANECOVER_1P = 4,
		SLIDER_LANECOVER_2P,

		SONG_PROGRESS = 6,

		SKINSELECT_CUSTOMIZE = 7,

		IR_POSITION = 8,

		SLIDER_EQ0 = 10,
		SLIDER_EQ1,
		SLIDER_EQ2,
		SLIDER_EQ3,
		SLIDER_EQ4,
		SLIDER_EQ5,
		SLIDER_EQ6,

		VOLUME_MASTER = 17,
		VOLUME_KEY,
		VOLUME_BGM,

		FX_MASTER_P1 = 20,
		FX_MASTER_P2,
		FX_KEY_P1,
		FX_KEY_P2,
		FX_BGM_P1,
		FX_BGM_P2,
		FX_PITCH,

		SLIDER_COUNT
	};

	enum bargraph
	{
		BAR_SONG_PROGRESS = 1,
		SONG_LOAD_PROGRESS = 2,

		CHART_PLAYLEVEL = 3,

		LEVEL_BEGINNER_IN_SAME_FOLDER = 5,
		LEVEL_NORMAL_IN_SAME_FOLDER,
		LEVEL_HYPER_IN_SAME_FOLDER,
		LEVEL_ANOTHER_IN_SAME_FOLDER,
		LEVEL_INSANE_IN_SAME_FOLDER,

		PLAY_EXSCORE = 10,
		PLAY_EXSCORE_PREDICT,
		PLAY_MYBEST_CURRENT,
		PLAY_MYBEST,
		PLAY_TARGET_EXSCORE_CURRENT,
		PLAY_TARGET_EXSCORE,

		RESULT_PERFECT_PROP = 20,
		RESULT_GREAT_PROP,
		RESULT_GOOD_PROP,
		RESULT_BAD_PROP,
		RESULT_POOR_PROP,
		RESULT_MAXCOMBO_PROP,
		RESULT_SCORE_PROP,
		RESULT_EXSCORE_PROP,

		RESULT_TARGET_PERFECT_PROP = 30,
		RESULT_TARGET_GREAT_PROP,
		RESULT_TARGET_GOOD_PROP,
		RESULT_TARGET_BAD_PROP,
		RESULT_TARGET_POOR_PROP,
		RESULT_TARGET_MAXCOMBO_PROP,
		RESULT_TARGET_SCORE_PROP,
		RESULT_TARGET_EXSCORE_PROP,

		MYBEST_PERFECT_PROP = 40,
		MYBEST_GREAT_PROP,
		MYBEST_GOOD_PROP,
		MYBEST_BAD_PROP,
		MYBEST_POOR_PROP,
		MYBEST_MAXCOMBO_PROP,
		MYBEST_SCORE_PROP,
		MYBEST_EXSCORE_PROP,

		BARGRAPH_COUNT
	};

	enum button
	{
		//パネル起動ボタン
		//クリックするとパネルを起動します。
		//パネル上で右クリックor同じボタンをクリックで、パネルを終了します。

		BUTTON_PANEL1 = 1,	// off/on
		BUTTON_PANEL2,	// off/on
		BUTTON_PANEL3,	// off/on
		BUTTON_PANEL4,	// off/on
		BUTTON_PANEL5,	// off/on
		BUTTON_PANEL6,	// off/on
		BUTTON_PANEL7,	// off/on
		BUTTON_PANEL8,	// off/on
		BUTTON_PANEL9,	// off/on

		/////////////////////////////////
		//曲リスト表示オプション

		CURRENT_DIFFICULTY_FILTER = 10,	// off/easy/normal/hard/expert/hakkyou
		CURRENT_KEY_FILTER,	// off/5keys/7keys/10keys/14keys/9keys
		CURRENT_SORT,	// off/レベル/タイトル/クリア

		/////////////////////////////////

		KEYCONFIG = 13,
		SKINSELECT,
		PLAY,
		AUTOPLAY,
		TEXTVIEW,
		RESETTAG,
		REPLAY,


		/////////////////////////////////
		//FXオプション

		FX0_TYPE = 20,	// OFF/REVERB/DELAY/LOWPASS/HIGHPASS/FLANGER/CHORUS/DISTORTION/PITCH
		FX1_TYPE,	// OFF/REVERB/DELAY/LOWPASS/HIGHPASS/FLANGER/CHORUS/DISTORTION/PITCH
		FX2_TYPE,	// OFF/REVERB/DELAY/LOWPASS/HIGHPASS/FLANGER/CHORUS/DISTORTION/PITCH

		FX0 = 23,	// off/on
		FX1,	// off/on
		FX2,	// off/on

		FX0_TARGET = 26,	// MASTER/KEY/BGM
		FX1_TARGET,	// MASTER/KEY/BGM
		FX2_TARGET,	// MASTER/KEY/BGM

		//EQボタンはまだ保留中
		EQ = 29,	// OFF/ON
		EQ_PRESET,	// USER/FLAT/ROCK/TECHNO/DANCE/JAZZ/CLASSIC

		VOLUME_CONTROL,	// OFF/ON
		BTN_PITCH,	// OFF/ON
		PITCH_TYPE,	// FREQENCY/PITCH/SPEED


		/////////////////////////////////
		//プレイオプション

		GAUGE_1P = 40,	// GROOVE/SURVIVAL/DEATH/EASY
		GAUGE_2P,	// GROOVE/SURVIVAL/DEATH/EASY

		RANDOM_1P,	// OFF/MIRROR/RANDOM/S-RANDOM/SCATTER
		RANDOM_2P,	// OFF/MIRROR/RANDOM/S-RANDOM/SCATTER

		ASSIST_1P,	// OFF/AUTOSCRATCH
		ASSIST_2P,	// OFF/AUTOSCRATCH

		SHUTTER, // シャッター (??)



		EFFECT_1P = 50,	// OFF/HIDDEN/SUDDEN/HID+SUD
		EFFECT_2P,	// OFF/HIDDEN/SUDDEN/HID+SUD

		//52 reserved
		//53 reserved


		DP_FLIP = 54,	// off/on
		HSFIX,	// OFF/MAXBPM/MINBPM/AVERAGE/CONSTANT
		BATTLE,	// OFF/BATTLE(VS_HUMAN)/BATTLE(VS_GHOST)/DOUBLE_BATTLE/ONLINE_BATTLE
		HS1P,
		HS2P,

		SCOREGRAPH = 70,	// off/on
		GHOST_POSITION,	// off/a/b/c
		BGA,	// off/on/autoplay_only
		BGA_SIZE,	// normal/extend
		BTN_JUDGE_TIMING,
		JUDGE_TIMING_AUTO_ADJUST,	// off/on
		BTN_DEFAULT_TARGET_RATE,
		TARGET_TYPE,


		/////////////////////////////////
		//その他のオプション

		SCREEN_MODE = 80,	// full/window
		COLOR_MODE,	// 32bit/16bit
		VSYNC,	// off/on
		SAVE_REPLAY,	// off/always_save/highscore_only
		FAVORITE = 90,	//off/favorite/ignore

		
		////////////////////////////////////
		//選曲難度別
		//difficultyを直接指定する

		SELECT_ALL_DIFFICULTY = 91,
		SELECT_BEGINNER,
		SELECT_NORMAL,
		SELECT_HYPER,
		SELECT_ANOTHER,
		SELECT_INSANE,

		/////////////////////////////////
		//キーコンフィグ用

		KEYCONFIG_1P_1 = 101,	// off/on
		KEYCONFIG_1P_2,	// off/on
		KEYCONFIG_1P_3,	// off/on
		KEYCONFIG_1P_4,	// off/on
		KEYCONFIG_1P_5,	// off/on
		KEYCONFIG_1P_6,	// off/on
		KEYCONFIG_1P_7,	// off/on
		KEYCONFIG_1P_8,	// off/on
		KEYCONFIG_1P_9,	// off/on

		KEYCONFIG_1P_SC_LEFT = 110,	// off/on
		KEYCONFIG_1P_SC_RIGHT,	// off/on
		KEYCONFIG_1P_START,	// off/on
		KEYCONFIG_1P_SELECT,	// off/on

		KEYCONFIG_2P_1 = 121,	// off/on
		KEYCONFIG_2P_2,	// off/on
		KEYCONFIG_2P_3,	// off/on
		KEYCONFIG_2P_4,	// off/on
		KEYCONFIG_2P_5,	// off/on
		KEYCONFIG_2P_6,	// off/on
		KEYCONFIG_2P_7,	// off/on
		KEYCONFIG_2P_8,	// off/on
		KEYCONFIG_2P_9,	// off/on

		KEYCONFIG_2P_SC_LEFT = 130,	// off/on
		KEYCONFIG_2P_SC_RIGHT,	// off/on
		KEYCONFIG_2P_START,	// off/on
		KEYCONFIG_2P_SELECT,	// off/on

		KEYCONFIG7_TITLE = 140,	// none/1P1/1P2/1P3/1P4/1P5/1P6/1P7/1PLEFT/1PRIGHT/1PSTART/1PSELECT/2P1/2P2/2P3/2P4/2P5/2P6/2P7/2PLEFT/2PRIGHT/2PSTART/2PSELECT
		KEYCONFIG9_TITLE,	// none/1/2/3/4/5/6/7/8/9/START/SELECT
		KEYCONFIG5_TITLE,	// none/1P1/1P2/1P3/1P4/1P5/1PLEFT/1PRIGHT/1PSTART/1PSELECT/2P1/2P2/2P3/2P4/2P5/2PLEFT/2PRIGHT/2PSTART/2PSELECT
		KEYCONFIG_TYPE = 143,	// 7keys/9keys/5keys


		KEYCONFIG_SLOT_0 = 150,	// off/on
		KEYCONFIG_SLOT_1,	// off/on
		KEYCONFIG_SLOT_2,	// off/on
		KEYCONFIG_SLOT_3,	// off/on
		KEYCONFIG_SLOT_4,	// off/on
		KEYCONFIG_SLOT_5,	// off/on
		KEYCONFIG_SLOT_6,	// off/on
		KEYCONFIG_SLOT_7,	// off/on


		SKINSELECT_7KEYS = 170,	// off/on
		SKINSELECT_5KEYS,	// off/on
		SKINSELECT_14KEYS,	// off/on
		SKINSELECT_10KEYS,	// off/on
		SKINSELECT_9KEYS,	// off/on
		SKINSELECT_SELECT,	// off/on
		SKINSELECT_DECIDE,	// off/on
		SKINSELECT_RESULT,	// off/on
		SKINSELECT_KEYCONFIG,	// off/on
		SKINSELECT_SKINSELECT,	// off/on
		SKINSELECT_SOUNDSET,	// off/on
		SKINSELECT_THEME,	// off/on
		SKINSELECT_BATTLE7,	// off/on
		SKINSELECT_BATTLE5,	// off/on
		SKINSELECT_BATTLE9,	// off/on

		SKINSELECT_SKIN = 190,

		//ヘルプファイル表示ボタン
		//ヘルプ本体はあらかじめ#HELPFILEで定義しておく必要があります。
		HELP_1 = 200,
		HELP_2,
		HELP_3,
		HELP_4,
		HELP_5,
		HELP_6,
		HELP_7,
		HELP_8,
		HELP_9,
		HELP_10,

		//IRページ接続ボタン
		//ブラウザでIRのページを開きます。フルスクリーンの場合はウインドウモードに変化します。
		IR_PAGE = 210,

		//220-229
		//スキンカスタマイズ切り替えボタン
		SKINCUSTOMIZE_1 = 220,
		SKINCUSTOMIZE_2,
		SKINCUSTOMIZE_3,
		SKINCUSTOMIZE_4,
		SKINCUSTOMIZE_5,
		SKINCUSTOMIZE_6,
		SKINCUSTOMIZE_7,
		SKINCUSTOMIZE_8,
		SKINCUSTOMIZE_9,
		SKINCUSTOMIZE_10,

		COURSESELECT_DECIDE = 230,
		COURSESELECT_CANCEL,
		COURSEVIEW_EDIT,
		COURSEVIEW_DELETE,

		COURSEOPTION_STAGECONNECT_1_TO_2 = 240,
		COURSEOPTION_STAGECONNECT_2_TO_3,
		COURSEOPTION_STAGECONNECT_3_TO_4,
		COURSEOPTION_STAGECONNECT_4_TO_5,
		COURSEOPTION_STAGECONNECT_5_TO_6,
		COURSEOPTION_STAGECONNECT_6_TO_7,
		COURSEOPTION_STAGECONNECT_7_TO_8,
		COURSEOPTION_STAGECONNECT_8_TO_9,
		COURSEOPTION_STAGECONNECT_9_TO_10,
		COURSEOPTION_STAGECONNECT_10_TO_11,
		COURSEOPTION_BPMCHANGE,
		COURSEOPTION_GAUGE,
		COURSEOPTION_PLAYOPTION,
		COURSEOPTION_IR,

		RANDOM_COURSEOPTION_LEVEL = 260,
		RANDOM_COURSEOPTION_LEVEL_MAX,
		RANDOM_COURSEOPTION_LEVEL_MIN,
		RANDOM_COURSEOPTION_BPM_RANGE,
		RANDOM_COURSEOPTION_BPM_MAX,
		RANDOM_COURSEOPTION_BPM_MIN,
		RANDOM_COURSEOPTION_STAGE_COUNT,

		COURSEOPTION_DEFAULT_STAGECONNECT = 268,
		COURSEOPTION_DEFAULT_GAUGE,

		BUTTON_COUNT
	};

	enum class type
	{
		GENERAL,
		NUMBER,
		SLIDER,
		BARGRAPH,
		BUTTON,
		ONMOUSE,
		TEXT
	};
}

using namespace LR2;

struct setDst { dst_option dst; bool set; };
//typedef std::function<int(SkinLR2*, const Tokens&, pTexture)> LoadLR2SrcFunc;

class SkinLR2: public vSkin
{
protected:
    static bool customizeDst[100];  // temporary workaround

private:
    struct Customize
    {
        unsigned dst_op;
        StringContent title;
        std::vector<StringContent> label;
        size_t value;
    };
    std::vector<Customize> customize;

    struct CustomFile
    {
        StringContent title;
        StringContent filepath;
        std::vector<Path> pathList;
        size_t defIdx;
        size_t value;
    };
    std::vector<CustomFile> customFile;

protected:
    size_t imageCount = 0;
    struct { unsigned r, g, b; } transColor = { 0, 255, 0 };
    timeMS timeStartInputTimeRank = 0;	    	// Result / Course Result Only
    timeMS timeStartInputTimeUpdate = 0;	    // Result / Course Result Only
    timeMS timeFadeoutLength = 0;
    bool flipSide = false;
    bool flipResult = false;					// Result / Course Result Only
    bool reloadBanner = false;
    bool disableFlipResult = false;
    unsigned scratchSide1P = 0;					// Play Skins Only; 0: left, 1: right
    unsigned scratchSide2P = 0;					// Play Skins Only; 0: left, 1: right

public:
    SkinLR2() = delete;
    SkinLR2(Path p);
    void loadCSV(Path p);

protected:
    typedef std::shared_ptr<SpriteLaneVertical> pSpriteLane;
    std::vector<pSpriteLane> _laneSprites;

private:
    unsigned line = 0;          // line parsing index
    Tokens csvNextLineTokenize(std::istream& file);

    int loadLR2image        (const Tokens &t);
    int loadLR2include      (const Tokens &t);
    int loadLR2font         (const Tokens &t);
    int loadLR2systemfont   (const Tokens &t);
    int loadLR2header       (const Tokens &t);
    int loadLR2timeoption   (const Tokens &t);
    int loadLR2others       (const Tokens &t);
    int loadLR2SkinLine     (const Tokens &t);

public:
    int loadLR2src(const Tokens &t);
    int loadLR2_SRC_IMAGE(const Tokens &t, pTexture tex);
    int loadLR2_SRC_NUMBER(const Tokens &t, pTexture tex);
    int loadLR2_SRC_SLIDER(const Tokens &t, pTexture tex);
    int loadLR2_SRC_BARGRAPH(const Tokens &t, pTexture tex);
    int loadLR2_SRC_BUTTON(const Tokens &t, pTexture tex);
    int loadLR2_SRC_TEXT(const Tokens &t, pTexture dummy = nullptr);
    int loadLR2_SRC_NOTE(const Tokens &t);
    int loadLR2dst(const Tokens &t);
    int loadLR2_DST_NOTE(const Tokens &t);

protected:
	bool noshiftJudge1P;
	bool noshiftJudge2P;
	int  alignJudge1P;
	int  alignJudge2P;
	unsigned *pDigits1P;
	unsigned *pDigits2P;
	unsigned totalDigits1P;
	unsigned totalDigits2P;
	Rect *pRectNowJudge1P = nullptr;
	Rect *pRectNowJudge2P = nullptr;
	Rect *pRectNowCombo1P = nullptr;
	Rect *pRectNowCombo2P = nullptr;
public:
    int loadLR2_SRC_NOWJUDGE1(const Tokens &t, pTexture tex);
    int loadLR2_SRC_NOWJUDGE2(const Tokens &t, pTexture tex);
    int loadLR2_SRC_NOWCOMBO1(const Tokens &t, pTexture tex);
    int loadLR2_SRC_NOWCOMBO2(const Tokens &t, pTexture tex);

    void loadLR2IF(const Tokens &t, std::ifstream&);

    //std::vector<SkinLR2> _csvIncluded;


////////////////////////////////////////////////////////////////////////////////

private:
    struct element
    {
        std::shared_ptr<vSprite> ps;
        bool draw;
        dst_option op1;
        dst_option op2;
        dst_option op3;
        dst_option op4;
    };
    std::vector<element> drawQueue;
public:
    virtual void update();
    virtual void draw() const;

};

typedef std::function<int(SkinLR2*, const Tokens&, pTexture)> LoadLR2SrcFunc;

// adapt helper
void updateDstOpt();
void setCustomDstOpt(unsigned base, unsigned offset, bool val);
void clearCustomDstOpt();
bool getDstOpt(dst_option d);
