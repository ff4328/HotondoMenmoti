#pragma once
#include <string>
#include <vector>
#include <iostream>

/// <summary>
/// 武器構造体
/// </summary>
struct Weapons
{
	//武器の名前
	std::string name;

	//武器のダメージ
	float damage;

	//武器の射程距離
	float range;

	//武器の攻撃範囲
	float attackRange;

	//武器の攻撃速度
	float attackSpeed;
};
const int WEAPON_NUM=4;

class WeaponManager
{
public:
	/// <summary>
	/// WeaponManagerのコンストラクタ
	/// </summary>
	WeaponManager();

	/// <summary>
	/// WeaponManagerのデストラクタ
	/// </summary>
	~WeaponManager() = default;

	//////////////いつのもセット
	void Init();
	void End();
	void Draw() const;
	void Update();
	//////////////

	/// <summary>
	/// 武器詳細表示
	/// </summary>
	void DisplayWeapons() const;

	/// <summary>
	/// 武器の初期ステータス設定
	/// </summary>
	void SetWeaponStatus();

	/// <summary>
	///	攻撃力増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	void AddAttackSpeed();

	/// <summary>
	/// 攻撃範囲増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	void AddAttackRange();

	Weapons WeaponNum[WEAPON_NUM];

private:

	std::vector<Weapons> weapons;
};