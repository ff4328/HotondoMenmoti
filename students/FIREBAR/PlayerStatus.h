#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "../bamboojr36/Collision.h"
#include "../bamboojr36/Heal.h"

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

	/// <summary>
	/// プレイヤースピードのゲッター
	/// </summary>
	/// <returns>moveSpeed</returns>
	float GetMoveSpeed() const;

	/// <summary>
	/// 最大HPのゲッター
	/// </summary>
	/// <returns></returns>
	float GetMaxHP()const;

	/// <summary>
	/// HPの増減処理に使うセッター関数
	/// </summary>
	/// <param name="value"></param>
	void SetCurrentHP(float value);

	/// <summary>
	/// 現在のHPを取得するときに使うゲッター関数
	/// </summary>
	/// <returns></returns>
	float GetCuurentHP()const;

public:
	std::vector<Player> players;
	std::unique_ptr<Collision>m_pCollision;
	std::unique_ptr<Heal>m_pHeal;
};