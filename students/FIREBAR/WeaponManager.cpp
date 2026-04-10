#include "WeaponManager.h"
#include <string>
#include <vector>
#include <iostream>
#include "DxLib.h"

//武器の初期化;名前、ダメージ、射程距離、攻撃範囲、攻撃速度
WeaponManager::WeaponManager()
{
	//武器の初期化
	weapons.push_back({ "弓", 8.0f, 15.0f ,2.0f,1.0f });
	weapons.push_back({ "刀", 10.0f, 5.0f,2.0f,0.5f });
	weapons.push_back({ "斧", 15.0f, 10.0f ,4.0f,1.5f });
	weapons.push_back({ "魔法", 4.0f, 20.0f ,4.0f,2.0f });
}

void WeaponManager::DisplayWeapons() const
{
	std::cout << "=== 武器リスト ===" << std::endl;
	for (const auto& weapon : weapons)
	{
		weapon.Display();
	}
}