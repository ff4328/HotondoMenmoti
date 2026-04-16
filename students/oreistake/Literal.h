#pragma once

	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	enum Status {

		STATUS_IDLE = 0,
		STATUS_WALK,
		STATUS_MAX
	};

	enum EnemyType {

		ENEMY_TYPE_GOBLIN,
		ENEMY_TYPE_MASH,
		ENEMY_TYPE_BAT,
		ENEMY_TYPE_SKELETON,
		ENEMY_TYPE_MAX
	};

	enum Direction {

		DIRECTION_RIGHT = 0,
		DIRECTION_LEFT = 1,

	};


	/// <summary>
	/// 1モーションの画像の数
	/// </summary>
	const int CHARA_MOTION_NUM = 8;

	/// <summary>
	/// 1キャラのモーションの数
	/// </summary>
	const int CHARA_STATUS_NUM = STATUS_MAX;


	const int CHARA_MOB_NUM = ENEMY_TYPE_MAX;

	const int PLAYER_HP_MAX = 1;


	

