#pragma once

class PlayerStatus
{
public:
	// コンストラクタ
	PlayerStatus();

	// デストラクタ
	~PlayerStatus() = default;

	/// <summary>
	/// ゲーム開始時にプレイヤーのステータスを初期化する
	/// </summary>
	void SetPlayerStatus();

public:
	// プレイヤーの体力
	float hp;
	// プレイヤーのスピード
	float speed;
};