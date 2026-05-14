#pragma once

	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	enum Status {

		STATUS_IDLE = 0,
		STATUS_RUN,
		STATUS_DEAD,
		STATUS_MAX
	};

	/// <summary>
	/// 敵のタイプ
	/// </summary>
	enum EnemyType {

		ENEMY_TYPE_GOBLIN,
		ENEMY_TYPE_MASH,
		ENEMY_TYPE_BAT,
		ENEMY_TYPE_SKELETON,
		ENEMY_TYPE_MAX
	};

	/// <summary>
	/// 向き
	/// </summary>
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

	/// <summary>
	/// 敵の最大数
	/// </summary>
	const int CHARA_MOB_NUM = ENEMY_TYPE_MAX;

	/// <summary>
	/// カメラ補正の距離
	/// </summary>
	const float CAMERA_LATENCY = 10.0f;

	/// <summary>
	/// 水平方向のカメラの最低値
	/// </summary>
	const float CAMERA_HORIZONTAL_MARGIN = 0.0f;

	/// <summary>
	/// 垂直方向のカメラの最低値
	/// </summary>
	const float CAMERA_VERTICAL_MARGIN = 0.0f;

	
