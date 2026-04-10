#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Weapon
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

	void Draw() const;

	/// <summary>
	/// 武器詳細表示
	/// </summary>
	void DisplayWeapons() const;

	/// <summary>
	/// 武器の初期ステータス設定
	/// </summary>
	void SetWeaponStatus();

private:
	std::vector<Weapon> weapons;
};