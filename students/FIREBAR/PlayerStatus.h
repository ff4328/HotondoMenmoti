#pragma once
#include <string>
#include <vector>
#include <iostream>

/// <summary>
/// プレイヤー構造体
/// </summary>
struct Player
{
	//キャラの名前
	std::string name;

	//キャラの最大HP
	float maxhp;

	//キャラの現在のHP
	float currenthp;

	//キャラのスピード
	float moveSpeed;

	//キャラの経験値
	int exp;

	//キャラのレベル
	int level;
};

class PlayerStatus
{
public:
	/// <summary>
	/// PlayerStatusのコンストラクタ
	/// </summary>
	PlayerStatus();

	/// <summary>
	/// PlayerStatusのデストラクタ
	/// </summary>
	~PlayerStatus() = default;

	/// <summary>
	/// ゲーム開始時にプレイヤーのステータスを初期化する
	/// </summary>
	void SetPlayerStatus();

	////////////いつのもセット
	void Init();
	void End();
	void Draw();
	void Update();
	////////////

	/// <summary>
	/// 最大HP増加
	/// </summary>
	void AddMaxHP();

	/// <summary>
	/// スピード増加
	/// </summary>
	void AddSpeed();

public:
	std::vector<Player> players;
};