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
	Weapon bow = { "弓", 8.0f, 15.0f ,2.0f,1.0f };
	Weapon katana = { "刀", 10.0f, 5.0f,2.0f,0.5f };
	Weapon axe = { "斧", 15.0f, 10.0f ,4.0f,1.5f };
	Weapon magic = { "魔法", 4.0f, 20.0f ,4.0f,2.0f };

	weapons.push_back(bow);
	weapons.push_back(katana);
	weapons.push_back(axe);
	weapons.push_back(magic);
}

void WeaponManager::Draw() const
{
	if(Input::IsDown(KEY_INPUT_1))
	{
		std::cout << "1が押されました。" << std::endl;
		DisplayWeapons();
	}
}

void WeaponManager::DisplayWeapons() const
{
	std::cout << "=== 武器リスト ===" << std::endl;
	for (const auto& weapon : weapons)
	{
		weapon.Display();
	}
}