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
	float attackRamge;

	//武器の攻撃速度
	float attackSpeed;

	/// <summary>
	/// 名前、ダメージ、射程距離を表示
	/// </summary>
	void Display() const
	{
		std::cout << "武器名: " << name 
			<< "| ダメージ: " << damage
			<< "| 射程距離: " << range
			<< "| 攻撃範囲: " << attackRamge
			<< "| 攻撃速度: " << attackSpeed << std::endl;
	}
};

class WeaponManager
{
public:
	WeaponManager();

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