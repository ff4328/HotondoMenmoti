#include "WeaponManager.h"
#include "../Utility/Input.h"

#include "../students/mcd6752Tuyoshi/Katana/Katana.h"
#include "../students/oreistake/Player.h"
#include "../students/oreistake/Weapon/AxeManager.h"
#include "../students/oreistake/Weapon/ArrowManager.h"
#include "MagicBottleManager.h"
#include "../students/bamboojr36/Collision.h"

#include <string>
#include <vector>
#include <iostream>
#include "DxLib.h"

namespace
{
	int kmagicFrameCount = 0;
	int karrowFrameCount = 0;
}

//武器の初期化;名前、ダメージ、射程距離、攻撃範囲、攻撃速度, 初期攻撃範囲
WeaponStatus::WeaponStatus() :
	WeaponNums{},
	m_addWeapons{ false },
	m_pKatana(nullptr),
	m_pAxe(nullptr),
	m_pArrow(nullptr),
	m_pMagicBottle(nullptr),
	m_pPlayerMove(nullptr)
{
	//武器の初期化
	Weapons WeaponNum[4] =
	{
		{ "弓", 8.0f, 400.0f ,1.0f,180,1.0f},
		{ "刀", 5.0f, 30.0f,2.0f,150 ,2.0f},
		{ "斧", 10.0f, 100.0f ,1.0f, 200,1.0f},
		{ "魔法", 4.0f, 450.0f ,50.0f, 390,50.0f}
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

	m_pArrow = new ArrowManager(m_pPlayerMove);
	m_pKatana = new Katana(weapons[1].name, weapons[1].damage, weapons[1].range, weapons[1].attackRange, weapons[1].coolDown, 1, m_pPlayerMove->GetModelPos());
	m_pAxe = new AxeManager();
	m_pMagicBottle = new MagicBottleManager(m_pPlayerMove);
}

WeaponStatus::WeaponStatus(PlayerMove* pPlayerMove) :
	WeaponNums{},
	m_addWeapons{ false },
	m_pKatana(nullptr),
	m_pAxe(nullptr),
	m_pMagicBottle(nullptr),
	m_pPlayerMove(pPlayerMove)
{
	//武器の初期化
	Weapons WeaponNum[4] =
	{
		{ "弓", 8.0f, 400.0f ,1.0f,180,1.0f},
		{ "刀", 5.0f, 30.0f,2.0f,150 ,2.0f},
		{ "斧", 10.0f, 100.0f ,1.0f, 200,1.0f},
		{ "魔法", 4.0f, 450.0f ,50.0f, 390,50.0f}
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

	m_pArrow = new ArrowManager(m_pPlayerMove);
	m_pKatana = new Katana(weapons[1].name, weapons[1].damage, weapons[1].range, weapons[1].attackRange, weapons[1].coolDown, 1, m_pPlayerMove->GetModelPos());
	m_pAxe = new AxeManager();
	m_pMagicBottle = new MagicBottleManager(m_pPlayerMove);
}

void WeaponStatus::Init()
{
	m_pArrow->Init();

	m_pKatana->Init();

	m_pAxe->Init(weapons[2].name, weapons[2].damage, weapons[2].range, weapons[2].attackRange, weapons[2].coolDown, 1, m_pPlayerMove->GetModelPos());

	m_pMagicBottle->Init();
}

void WeaponStatus::End()
{
	m_pArrow->End();

	m_pKatana->End();

	m_pMagicBottle->End();
}

void WeaponStatus::Draw() const
{
	DisplayWeapons();

	if (m_addWeapons[2]) m_pMagicBottle->Draw();

	if (m_addWeapons[0]) m_pArrow->Draw();

	m_pKatana->Draw();

	if (m_addWeapons[1]) m_pAxe->Draw();
}

void WeaponStatus::Update()
{
	if (m_addWeapons[0]) 
	{
		m_pArrow->Update();

		karrowFrameCount++;
		if (karrowFrameCount > weapons[0].coolDown)
		{
			m_pArrow->Create(weapons[0].name, weapons[0].damage, weapons[0].range, weapons[0].attackRange, weapons[0].coolDown, 0, m_pPlayerMove->GetModelPos());
			karrowFrameCount = 0;
		}
	}

	m_pKatana->SetPlayerPos(m_pPlayerMove->GetModelPos());
	m_pKatana->Update();

	if (m_addWeapons[1])
	{
		m_pAxe->Update();

		static int axeFrameCount = 0;
		axeFrameCount++;

		if (axeFrameCount >= weapons[2].coolDown)
		{
			m_pAxe->Create(weapons[2].name, weapons[2].damage, weapons[2].range, weapons[2].attackRange, weapons[2].coolDown, 0, m_pPlayerMove->GetModelPos());
			axeFrameCount = 0;
		}
	}

	if (m_addWeapons[2]) 
	{
		m_pMagicBottle->Update();

		kmagicFrameCount++;
		if (kmagicFrameCount > weapons[3].coolDown)
		{
			m_pMagicBottle->Create(weapons[3].name, weapons[3].damage, weapons[3].range, weapons[3].attackRange, weapons[3].coolDown, 3, m_pPlayerMove->GetModelPos());
			kmagicFrameCount = 0;

		}
	}
}

void WeaponStatus::DisplayWeapons() const
{
	printfDx("\n=== 武器リスト ===\n");
	for (const auto& weapon : weapons)
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
	Weapons WeaponNum[4] =
	{
		{ "弓", 8.0f, 400.0f ,1.0f,180,1.0f},
		{ "刀", 5.0f, 30.0f,2.0f,150 ,2.0f},
		{ "斧", 10.0f, 100.0f ,1.0f, 200,1.0f},
		{ "魔法", 4.0f, 450.0f ,50.0f, 390,50.0f}
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
		weapon.attackRange += (weapon.defaultAttackRange / 10) * 2;
	}
	m_pKatana->SetAttackRange(weapons[1].attackRange);
}

void WeaponStatus::AddAttack(int v)
{
	weapons[v].damage += 2;
}

Rect WeaponStatus::CheckHitEnemy(int value)
{
	switch (value)
	{
	case 0:
		return m_pArrow->GetCheckRect();
		break;
	case 1:
		return m_pKatana->GetCheckRect();
		break;
	//case 2:
	//	return m_pAxe->GetCheckRects();
	//	break;
	case 3:
		return m_pMagicBottle->GetCheckRect();
		break;
	default:
		return Rect{ 0, 0, 0, 0 };
		break;
	}
};

bool WeaponStatus::CheckHitEnemy(int value, Rect enemyRect)
{
	Collision collision;

	switch (value)
	{
	case 0:
		return collision.CheckRectCommon(
			enemyRect,
			m_pArrow->GetCheckRect());

	case 1:
		return collision.CheckRectCommon(
			enemyRect,
			m_pKatana->GetCheckRect());
	//case 2:
	//	return collision.CheckRectCommon(enemyRect, m_pAxe->GetCheckRects());

	case 3:
		return m_pMagicBottle->CheckHit(enemyRect);
	}

	return false;
}

std::vector<Rect> WeaponStatus::CheckHitEnemies(int value)
{
	switch (value)
	{
	case 0:
		return { m_pArrow->GetCheckRects() };
	case 2:
		return{ m_pAxe->GetCheckRects() };
	case 3:
		return { m_pMagicBottle->GetCheckRects() };

	default:
		return {};
	}
}

void WeaponStatus::SetCamera(Camera* pCamera)
{
	if (m_pAxe) {
		m_pAxe->SetCamera(pCamera);
	}
}