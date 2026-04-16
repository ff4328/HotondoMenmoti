#include "WeaponManager.h"
#include "../Utility/Input.h"
#include <string>
#include <vector>
#include <iostream>
#include "DxLib.h"

//武器の初期化;名前、ダメージ、射程距離、攻撃範囲、攻撃速度
WeaponManager::WeaponManager()
{
	//武器の初期化
	Weapons WeaponNum[] =
	{
		{ "弓", 8.0f, 15.0f ,2.0f,180},
		 { "刀", 10.0f, 5.0f,2.0f,150 },
		 { "斧", 15.0f, 10.0f ,4.0f, 200},
		  { "魔法", 4.0f, 20.0f ,4.0f, 390}
	};

	//Weapon bow = { "弓", 8.0f, 15.0f ,2.0f,1.0f};
	//Weapon katana = { "刀", 10.0f, 5.0f,2.0f,0.5f };
	//Weapon axe = { "斧", 15.0f, 10.0f ,4.0f,1.5f };
	//Weapon magic = { "魔法", 4.0f, 20.0f ,4.0f,2.0f };

	for (auto i = 0; i < WEAPON_NUM; i++)
	{
		weapons.push_back(WeaponNum[i]);
	}
}

void WeaponManager::End()
{}

void WeaponManager::Draw() const
{
	DisplayWeapons();
}

void WeaponManager::DisplayWeapons() const
{
	printfDx("\n=== 武器リスト ===\n");
	for ( auto& weapon : weapons)
	{
		printfDx("武器名:%s", weapon.name.c_str());
		printfDx("| ダメージ:%f", weapon.damage);
		printfDx("| 射程距離:%f", weapon.range);
		printfDx("| 攻撃範囲:%f", weapon.attackRange);
		printfDx("| 攻撃速度:%f\n", weapon.attackSpeed);
	}
}

void WeaponManager::SetWeaponStatus()
{
	weapons.clear();

	Weapons bow = { "弓", 8.0f, 15.0f ,2.0f,1.0f };
	Weapons katana = { "刀", 10.0f, 5.0f,2.0f,0.5f };
	Weapons axe = { "斧", 15.0f, 10.0f ,4.0f,1.5f };
	Weapons magic = { "魔法", 4.0f, 20.0f ,4.0f,2.0f };

	weapons.push_back(bow);
	weapons.push_back(katana);
	weapons.push_back(axe);
	weapons.push_back(magic);
}

void WeaponManager::AddAttackSpeed()
{
	for (auto& weapon : weapons)
	{
		weapon.attackSpeed -= 30;
		if (weapon.attackSpeed < 0)
			weapon.attackSpeed = 0;
	}
}

void WeaponManager::AddAttackRange()
{
	for (auto& weapon : weapons)
	{
		printfDx("\nf\nf\nf\nf\nf\nf");
		weapon.attackRange += 0.2f;
		if (weapon.attackRange < 0)
			weapon.attackRange = 0;
	}
}