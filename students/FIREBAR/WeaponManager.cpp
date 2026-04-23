#include "WeaponManager.h"
#include "../Utility/Input.h"

#include "../students/mcd6752Tuyoshi/Katana/Katana.h"
#include "../students/oreistake/Player.h"
#include "../students/oreistake/Weapon/Axe.h"

#include <string>
#include <vector>
#include <iostream>
#include "DxLib.h"

//武器の初期化;名前、ダメージ、射程距離、攻撃範囲、攻撃速度
WeaponStatus::WeaponStatus():
	WeaponNum{},
	m_pKatana(nullptr),
	m_pAxe(nullptr),
	m_pPlayerMove(nullptr)
{
	//武器の初期化
	Weapons WeaponNum[] =
	{
		{ "弓", 8.0f, 400.0f ,1.0f,180},
		 { "刀", 10.0f, 100.0f,2.0f,150 },
		 { "斧", 15.0f, 100.0f ,2.0f, 200},
		  { "魔法", 4.0f, 450.0f ,3.0f, 390}
	};

	//Weapon bow = { "弓", 8.0f, 15.0f ,2.0f,1.0f};
	//Weapon katana = { "刀", 10.0f, 5.0f,2.0f,0.5f };
	//Weapon axe = { "斧", 15.0f, 10.0f ,4.0f,1.5f };
	//Weapon magic = { "魔法", 4.0f, 20.0f ,4.0f,2.0f };

	for (auto i = 0; i < 4; i++)
	{
		weapons.push_back(WeaponNum[i]);
	}
	//　oo   ttttt  i   n  n  ppp  　oo 
	// o  o    t    i   nn n  p  p  o  o
	// o  o    t    i   n nn  ppp   o  o
	//  oo     t    i   n  n  p	     oo 

	m_pPlayerMove = new PlayerMove();

	m_pKatana = new Katana(weapons[1].name, weapons[1].damage, weapons[1].range, weapons[1].attackRange, weapons[1].coolDown,1, m_pPlayerMove->GetModelPos());
	m_pAxe = new Axe(weapons[2].name, weapons[2].damage, weapons[2].range, weapons[2].attackRange, weapons[2].coolDown, 2, m_pPlayerMove->GetModelPos());
}

WeaponStatus::WeaponStatus(PlayerMove* pPlayerMove) :
	WeaponNum{},
	m_pKatana(nullptr),
	m_pAxe(nullptr),
	m_pPlayerMove(pPlayerMove)
{
	//武器の初期化
	Weapons WeaponNum[] =
	{
		{ "弓", 8.0f, 400.0f ,1.0f,180},
		 { "刀", 10.0f, 100.0f,2.0f,150 },
		 { "斧", 15.0f, 100.0f ,2.0f, 200},
		  { "魔法", 4.0f, 450.0f ,3.0f, 390}
	};

	//Weapon bow = { "弓", 8.0f, 15.0f ,2.0f,1.0f};
	//Weapon katana = { "刀", 10.0f, 5.0f,2.0f,0.5f };
	//Weapon axe = { "斧", 15.0f, 10.0f ,4.0f,1.5f };
	//Weapon magic = { "魔法", 4.0f, 20.0f ,4.0f,2.0f };

	for (auto i = 0; i < 4; i++)
	{
		weapons.push_back(WeaponNum[i]);
	}
	//　oo   ttttt  i   n  n  ppp  　oo 
	// o  o    t    i   nn n  p  p  o  o
	// o  o    t    i   n nn  ppp   o  o
	//  oo     t    i   n  n  p	     oo 


	m_pKatana = new Katana(weapons[1].name, weapons[1].damage, weapons[1].range, weapons[1].attackRange, weapons[1].coolDown, 1, m_pPlayerMove->GetModelPos());
	m_pAxe = new Axe(weapons[2].name, weapons[2].damage, weapons[2].range, weapons[2].attackRange, weapons[2].coolDown, 2, m_pPlayerMove->GetModelPos());
}

void WeaponStatus::Init()
{
	m_pKatana->Init();
	m_pAxe->Init();
}

void WeaponStatus::End()
{
	m_pKatana->End();
	m_pAxe->End();
}

void WeaponStatus::Draw() const
{
	//DisplayWeapons();
	m_pKatana->Draw();
	m_pAxe->Draw();
}

void WeaponStatus::Update()
{
	m_pKatana->SetPlayerPos(m_pPlayerMove->GetModelPos());
	m_pKatana->Update();
	m_pAxe->Update();
}

void WeaponStatus::DisplayWeapons() const
{
	printfDx("\n=== 武器リスト ===\n");
	for ( auto& weapon : weapons)
	{
		printfDx("武器名:%s", weapon.name.c_str());
		printfDx("| ダメージ:%f", weapon.damage);
		printfDx("| 射程距離:%f", weapon.range);
		printfDx("| 攻撃範囲:%f", weapon.attackRange);
		printfDx("| 攻撃速度:%f\n", weapon.coolDown);
	}
}

void WeaponStatus::SetWeaponStatus()
{
	weapons.clear();
	//武器の初期化
	Weapons WeaponNum[] =
	{
		{ "弓", 8.0f, 400.0f ,1.0f,180},
		 { "刀", 10.0f, 100.0f,2.0f,150 },
		 { "斧", 15.0f, 100.0f ,2.0f, 200},
		  { "魔法", 4.0f, 450.0f ,3.0f, 390}
	};

	for (auto i = 0; i < 4; i++)
	{
		weapons.push_back(WeaponNum[i]);
	}
}

void WeaponStatus::AddAttackSpeed()
{
	for (auto& weapon : weapons)
	{
		weapon.coolDown -= 30;
		if (weapon.coolDown < 0)
			weapon.coolDown = 0;
	}
	m_pKatana->SetCoolTime(weapons[1].coolDown);
}

void WeaponStatus::AddAttackRange()
{
	for (auto& weapon : weapons)
	{
		weapon.attackRange += 0.2f;
		if (weapon.attackRange < 0)
			weapon.attackRange = 0;
	}
	m_pKatana->SetAttackRange(weapons[1].attackRange);
}