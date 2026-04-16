#pragma once

/// <summary>
/// プレイヤーの状態
/// </summary>
enum StatusYama {

	STATUS_IDLE_Yama = 0,
	STATUS_WALK_Yama,
	STATUS_MAX_Yama
};

enum EnemyTypeYama {

	ENEMY_TYPE_GOBLIN_Yama,
	ENEMY_TYPE_MUSH_Yama,
	ENEMY_TYPE_BAT_Yama,
	ENEMY_TYPE_SKELETON_Yama,
	ENEMY_TYPE_MAX_Yama
};

enum Directionyama {

	DIRECTION_RIGHT_Yama = 0,
	DIRECTION_LEFT_Yama = 1,

};

// プレイヤーの最大HP
const int PLAYER_HP_MAX_Yama = 1;

// 敵の最大HP
const int ENEMY_HP_MAX_Yama = 1;

/// <summary>
/// 1モーションの画像の数
/// </summary>
const int CHARA_MOTION_NUM_Yama = 8;

/// <summary>
/// 1キャラのモーションの数
/// </summary>
const int CHARA_STATUS_NUM_Yama = STATUS_MAX_Yama;


const int CHARA_MOB_NUM_Yama = ENEMY_TYPE_MAX_Yama;


