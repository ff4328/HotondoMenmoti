#pragma once




	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	enum Status {

		STATUS_IDLE = 0,
		STATUS_WALK,
		STATUS_MAX
	};

	/// <summary>
	/// 1モーションの画像の数
	/// </summary>
	const int CHARA_MOTION_NUM = 8;

	/// <summary>
	/// 1キャラのモーションの数
	/// </summary>
	const int CHARA_STATUS_NUM = STATUS_MAX;