#pragma once

/*
* !!! WARNING !!!
* These indices are currently DIRECTLY casted to LR2skin indices.
* When adding new value, do not modify existing values.
*/
enum class IndexNumber: unsigned
{
    ZERO = 0,           // should be initialized with 0

	HS_1P = 10,
	HS_2P,

	TIMING_ADJUST_VISUAL = 12,
	DEFAULT_TARGET_RATE,

	LANECOVER100_1P = 14,
	LANECOVER100_2P,

    FPS = 20,
	DATE_YEAR,
	DATE_MON,
	DATE_DAY,
	DATE_HOUR,
	DATE_MIN,
	DATE_SEC,

	PROFILE_PLAY_COUNT = 30,
	PROFILE_CLEAR_COUNT,
	PROFILE_FAIL_COUNT,
	PROFILE_PERFECT,
	PROFILE_GREAT,
	PROFILE_GOOD,
	PROFILE_BAD,
	PROFILE_POOR,
	PROFILE_RUNNING_COMBO,
	PROFILE_RUNNING_COMBO_MAX,
	PROFILE_TRIAL_LEVEL,
	PROFILE_TRIAL_LEVEL_PREV,

	MUSIC_BEGINNER_LEVEL = 45,
	MUSIC_NORMAL_LEVEL,
	MUSIC_HYPER_LEVEL,
	MUSIC_ANOTHER_LEVEL,
	MUSIC_INSANE_LEVEL,

	EQ0 = 50,
	EQ1,
	EQ2,
	EQ3,
	EQ4,
	EQ5,
	EQ6,
	VOLUME_MASTER,
	VOLUME_KEY,
	VOLUME_BGM,

	FX0_P1 = 60,
	FX0_P2,
	FX1_P1,
	FX1_P2,
	FX2_P1,
	FX2_P2,
	PITCH,

	INFO_SCORE = 70,
	INFO_EXSCORE,
	INFO_EXSCORE_MAX,
	INFO_RATE,
	INFO_TOTALNOTE,
	INFO_MAXCOMBO,
	INFO_BP,
	INFO_PLAYCOUNT,
	INFO_CLEARCOUNT,
	INFO_FAILCOUNT,
	INFO_PERFECT_COUNT,
	INFO_GREAT_COUNT,
	INFO_GOOD_COUNT,
	INFO_BAD_COUNT,
	INFO_POOR_COUNT,
	INFO_PERFECT_RATE,
	INFO_GREAT_RATE,
	INFO_GOOD_RATE,
	INFO_BAD_RATE,
	INFO_POOR_RATE,
	INFO_BPM_MAX,
	INFO_BPM_MIN,
	INFO_LR2IR_RANK,
	INFO_LR2IR_TOTALPLAYER,
	INFO_LR2IR_CLEARRATE,
	INFO_LR2IR_SCORE_TO_RIVAL,

	PLAY_1P_SCORE = 100,
	PLAY_1P_EXSCORE,
	PLAY_1P_RATE,
	PLAY_1P_RATEDECIMAL,
	PLAY_1P_NOWCOMBO,
	PLAY_1P_MAXCOMBO,
    PLAY_1P_TOTALNOTES,
    PLAY_1P_GROOVEGAUGE,
    PLAY_1P_EXSCORE_DIFF,
	PLAY_1P_NEXT_RANK_EX_DIFF = 109,	// undocumented from LR2

    PLAY_1P_PERFECT = 110,
    PLAY_1P_GREAT,
    PLAY_1P_GOOD,
    PLAY_1P_BAD,
    PLAY_1P_POOR,
    PLAY_1P_TOTAL_RATE,
    PLAY_1P_TOTAL_RATE_DECIMAL2,

	PLAY_2P_SCORE = 120,
	PLAY_2P_EXSCORE,
	PLAY_2P_RATE,
	PLAY_2P_RATEDECIMAL,
	PLAY_2P_NOWCOMBO,
	PLAY_2P_MAXCOMBO,
    PLAY_2P_TOTALNOTES,
    PLAY_2P_GROOVEGAUGE,
    PLAY_2P_EXSCORE_DIFF,
	PLAY_2P_NEXT_RANK_EX_DIFF = 129,	// undocumented from LR2

    PLAY_2P_PERFECT = 130,
    PLAY_2P_GREAT,
    PLAY_2P_GOOD,
    PLAY_2P_BAD,
    PLAY_2P_POOR,
    PLAY_2P_TOTAL_RATE,
    PLAY_2P_TOTAL_RATE_DECIMAL2,

	RESULT_MYBEST_EX = 150,
	RESULT_TARGET_EX,
	RESULT_MYBEST_DIFF,			// exscore - mybest
	RESULT_TARGET_DIFF,			// exscore - target
	RESULT_NEXT_RANK_EX_DIFF,	// = 109
	RESULT_MYBEST_RATE,
	RESULT_MYBEST_RATE_DECIMAL2,
	RESULT_TARGET_RATE,
	RESULT_TARGET_RATE_DECIMAL2,


    PLAY_BPM = 160,
    PLAY_MIN,
    PLAY_SEC,
    PLAY_REMAIN_MIN,
    PLAY_REMAIN_SEC,
    PLAY_LOAD_PROGRESS_PERCENT,

    PLAY_LOAD_PROGRESS_SYS = 166,
    PLAY_LOAD_PROGRESS_WAV,
    PLAY_LOAD_PROGRESS_BGA,

    RESULT_RECORD_EX_BEFORE = 170,
    RESULT_RECORD_EX_NOW,
    RESULT_RECORD_EX_DIFF,
    RESULT_RECORD_MAXCOMBO_BEFORE,
    RESULT_RECORD_MAXCOMBO_NOW,
    RESULT_RECORD_MAXCOMBO_DIFF,
    RESULT_RECORD_BP_BEFORE,
    RESULT_RECORD_BP_NOW,
    RESULT_RECORD_BP_DIFF,
    RESULT_RECORD_IRRANK_BEFORE,
    RESULT_RECORD_IRRANK_NOW,
    RESULT_RECORD_IRRANK_DIFF,
    RESULT_RECORD_IR_RANK,
    RESULT_RECORD_IR_TOTALPLAYER,
    RESULT_RECORD_IR_CLEARRATE,
    RESULT_RECORD_IR_RANK_BEFORE,
    RESULT_RECORD_MYBEST_RATE,
    RESULT_RECORD_MYBEST_RATE_DECIMAL2,

		// 200-201, 210-220 are LR2IR definitions
		// some are taken by LR2Helper/LR2FS
		LR2IR_REPLACE_PLAY_1P_JUDGE_TIME_ERROR_MS = 201,
		LR2IR_REPLACE_PLAY_1P_FAST_SLOW = 210,	// 1:FAST 2:SLOW
		LR2IR_REPLACE_PLAY_2P_FAST_SLOW = 211,	// 1:FAST 2:SLOW
		LR2IR_REPLACE_PLAY_1P_FAST_COUNT = 212,
		LR2IR_REPLACE_PLAY_2P_JUDGE_TIME_ERROR_MS = 213,
		LR2IR_REPLACE_PLAY_1P_SLOW_COUNT = 214,
		LR2IR_REPLACE_PLAY_1P_COMBOBREAK = 216,
		LR2IR_REPLACE_PLAY_REMAIN_NOTES = 217,	// ?
		LR2IR_REPLACE_PLAY_RUNNING_NOTES = 218,	// ?

		COURSE_STAGE1_LEVEL = 250,
		COURSE_STAGE2_LEVEL,
		COURSE_STAGE3_LEVEL,
		COURSE_STAGE4_LEVEL,
		COURSE_STAGE5_LEVEL,

		INFO_RIVAL_SCORE = 270,
		INFO_RIVAL_EXSCORE,
		INFO_RIVAL_EXSCORE_MAX,
		INFO_RIVAL_RATE,
		INFO_RIVAL_TOTALNOTE,
		INFO_RIVAL_MAXCOMBO,
		INFO_RIVAL_BP,
		INFO_RIVAL_PLAYCOUNT,
		INFO_RIVAL_CLEARCOUNT,
		INFO_RIVAL_FAILCOUNT,
		INFO_RIVAL_PERFECT_COUNT,
		INFO_RIVAL_GREAT_COUNT,
		INFO_RIVAL_GOOD_COUNT,
		INFO_RIVAL_BAD_COUNT,
		INFO_RIVAL_POOR_COUNT,
		INFO_RIVAL_PERFECT_RATE,
		INFO_RIVAL_GREAT_RATE,
		INFO_RIVAL_GOOD_RATE,
		INFO_RIVAL_BAD_RATE,
		INFO_RIVAL_POOR_RATE,

		// LR2HelperG new definitions
		INFO_BMS_TOTAL = 301,

		GREEN_NUMBER_1P = 302,
		LANECOVER_TOP_1P,
		GREEN_NUMBER_MINBPM_1P,
		GREEN_NUMBER_MAXBPM_1P,
		LANECOVER_BOTTOM_1P,

		PLAY_3COL_JUDGE_COMBO_LEFT = 310,
		PLAY_3COL_JUDGE_COMBO_MID,
		PLAY_3COL_JUDGE_COMBO_RIGHT,
		PLAY_3COL_JUDGE_FAST_SLOW_LEFT,	// 1:FAST 2:SLOW
		PLAY_3COL_JUDGE_FAST_SLOW_MID,
		PLAY_3COL_JUDGE_FAST_SLOW_RIGHT,

		HS_FIX_BPM = 316,
		HS_FIX_MINBPM,
		HS_FIX_MAXBPM,
		HS_FIX_AVERAGE_BPM = 319,

		KEY_INDIVIDUAL_JUDGE_1P_SCR = 320,	// How these works are unknown
		KEY_INDIVIDUAL_JUDGE_1P_K1,
		KEY_INDIVIDUAL_JUDGE_1P_K2,
		KEY_INDIVIDUAL_JUDGE_1P_K3,
		KEY_INDIVIDUAL_JUDGE_1P_K4,
		KEY_INDIVIDUAL_JUDGE_1P_K5,
		KEY_INDIVIDUAL_JUDGE_1P_K6,
		KEY_INDIVIDUAL_JUDGE_1P_K7,
		KEY_INDIVIDUAL_JUDGE_1P_K8,
		KEY_INDIVIDUAL_JUDGE_1P_K9,

		KEY_INDIVIDUAL_JUDGE_2P_SCR = 330,
		KEY_INDIVIDUAL_JUDGE_2P_K1,
		KEY_INDIVIDUAL_JUDGE_2P_K2,
		KEY_INDIVIDUAL_JUDGE_2P_K3,
		KEY_INDIVIDUAL_JUDGE_2P_K4,
		KEY_INDIVIDUAL_JUDGE_2P_K5,
		KEY_INDIVIDUAL_JUDGE_2P_K6,
		KEY_INDIVIDUAL_JUDGE_2P_K7,
		KEY_INDIVIDUAL_JUDGE_2P_K8,
		KEY_INDIVIDUAL_JUDGE_2P_K9,

		// definitions added by banshao
		GREEN_NUMBER_2P = 342,
		LANECOVER_TOP_2P,
		GREEN_NUMBER_MINBPM_2P,
		GREEN_NUMBER_MAXBPM_2P,
		LANECOVER_BOTTOM_2P,

		FOLDER_TOTALSONGS = 340,	// not yet implemented

		INFO_TOTALNOTE_NORMAL = 350,
		INFO_TOTALNOTE_LN = 351,
		INFO_TOTALNOTE_SCRATCH = 352,
		INFO_TOTALNOTE_BSS = 353,
		INFO_TOTALNOTE_MINE = 354,

		PLAY_1P_MISS = 360,
		PLAY_1P_FAST_COUNT,
		PLAY_1P_SLOW_COUNT,
		PLAY_1P_BPOOR,
		PLAY_1P_COMBOBREAK,
		PLAY_1P_BP,
		PLAY_1P_JUDGE_TIME_ERROR_MS,

		PLAY_2P_MISS = 370,
		PLAY_2P_FAST_COUNT,
		PLAY_2P_SLOW_COUNT,
		PLAY_2P_BPOOR,
		PLAY_2P_COMBOBREAK,
		PLAY_2P_BP,
		PLAY_2P_JUDGE_TIME_ERROR_MS,

		SCRATCH_AXIS_1P_ANGLE = 380,
		SCRATCH_AXIS_2P_ANGLE,

		//  LR2HelperA A.0.39 - GITADORA風 JUDGE BARの追加 - Endless Circulation SE FS5のリザルトに適用されています
		GITADORA_STYLE_JUDGE_BAR_0 = 400,	// (0:残り,1:ノーミス,2:ミス)
		GITADORA_STYLE_JUDGE_BAR_MAX = 449,	// not implemented; I assume these were imititating the completion bar to the right of score results in GITADORA.

		// internal numbers
		_TEST1 = 500,
		_TEST2,
		_TEST3,
		_TEST4,
		_TEST5,
		_TEST6,
		_TEST7,
		_TEST8,
		_TEST9,

		_PPS1 = 511,
		_PPS2,
		_PPS3,
		_PPS4,
		_PPS5,
		_PPS6,
		_PPS7,
		_PPS8,
		_PPS9,

		_DISP_NOWCOMBO_1P,
		_DISP_NOWCOMBO_2P,
		_ANGLE_TT_1P,
		_ANGLE_TT_2P,

		_SELECT_BAR_LEVEL_0 = 550,
		_SELECT_BAR_LEVEL_MAX = 581,

	RANDOM = 999,

	SCENE_UPDATE_FPS = 1000,
	INPUT_DETECT_FPS,
	NEW_ENTRY_SECONDS,


    NUMBER_COUNT = 1199
};
