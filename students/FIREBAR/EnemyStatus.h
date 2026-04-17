#pragma once
#include <string>
#include <vector>
#include <iostream>

/// <summary>
/// 敵構造体
/// </summary>
struct Enemys
{
	//敵の名前
	std::string enemyName;

	//敵の最大HP
	float enemyMaxHP;

	//敵の現在のHP
	float enemyCurrentHP;

	//敵の攻撃力
	float enemyAttackPower;

	//敵の移動速度
	float enemySpeed;
};

class EnemyStatus
{
public:

	/// <summary>
	/// 敵のコンストラクタ
	/// </summary>
	EnemyStatus();

	/// <summary>
	/// 敵のデストラクタ
	/// </summary>
	~EnemyStatus() = default;

	/// <summary>
	/// ゲーム開始時に敵のステータスを初期化する
	/// </summary>
	void SetEnemyStatus();

	////////////いつのもセット
	void Init();
	void End();
	void Draw();
	void Update();
	////////////

private:
	/// <summary>
	/// 0=スケルトン、1=キノコ、2=ゴブリン、3=コウモリ
	/// </summary>
	std::vector<Enemys>enemys;
};