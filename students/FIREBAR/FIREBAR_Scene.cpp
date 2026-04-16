#include "FIREBAR_Scene.h"
#include "../Utility/Input.h"
#include "../students/Yama596/Scene/SceneMain.h"

#include "LotteryPusive.h"
#include "WeaponManager.h"
#include "PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/Enemy.h"

#include <string>
#include <vector>
#include <iostream>

#include "DxLib.h"

namespace
{
	bool kget = false;
	bool kget_2 = false;
}

FIREBAR_Scene::FIREBAR_Scene():
	m_pLotteryPassive(nullptr),
	m_pPlayer(nullptr),
	m_pEnemy(nullptr),
	m_pWeaponMgr(nullptr),
	m_pPlayerStatus(nullptr),
	m_pExpBar(nullptr)
{
}

void FIREBAR_Scene::Init()
{
	// pWeaponMgrÇ∆pPlayerStatusÇÃÉCÉìÉXÉ^ÉìÉXÇê∂ê¨
	m_pWeaponMgr = new WeaponManager();
	m_pPlayerStatus = new PlayerStatus();
	m_pExpBar = new EXPBar(m_pPlayerStatus);

	m_pLotteryPassive = std::make_unique<LotteryPusive>(m_pWeaponMgr, m_pPlayerStatus, m_pExpBar);
	m_pPlayer = std::make_unique<PlayerMove>();
	m_pEnemy = std::make_unique<Enemy>();

	m_pPlayerStatus->Init();
	m_pExpBar->Init();
	m_pLotteryPassive->Init();
	m_pPlayer->Init();
	m_pEnemy->Init();
}

void FIREBAR_Scene::End()
{
	m_pLotteryPassive->End();
	m_pPlayer->End();
	m_pEnemy->End();

	m_pWeaponMgr->End();
	delete m_pWeaponMgr;
	m_pWeaponMgr = nullptr;

	m_pPlayerStatus->End();
	delete m_pPlayerStatus;
	m_pPlayerStatus = nullptr;

	m_pExpBar->End();
	delete m_pExpBar;
	m_pExpBar = nullptr;
}

SceneBase* FIREBAR_Scene::Update()
{

	m_pPlayerStatus->Update();

	m_pLotteryPassive->Update();

	m_pPlayer->Update();

	m_pEnemy->Update();

	//pLotteryPassive->ShowSlot(kget_2);

	m_pExpBar->Update(kget,5);
	kget = false;

	static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);
	static bool prevP = (CheckHitKey(KEY_INPUT_P) == 1);
	static bool prevL = (CheckHitKey(KEY_INPUT_L) == 1);

	bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);
	bool nowP = (CheckHitKey(KEY_INPUT_P) == 1);
	bool nowL = (CheckHitKey(KEY_INPUT_L) == 1);

	if (nowF && !prevF)
	{

		// òAë±ëJà⁄ñhé~
		prevF = true;

		// ÉVÅ[ÉìëJà⁄
		return new SceneMain;

	}
	else if (nowP && !prevP)
	{

		// òAë±ëJà⁄ñhé~
		prevP = true;

		kget_2 = true;

	}
	else if (nowL && !prevL)
	{
		// òAë±ëJà⁄ñhé~
		prevL = true;
		kget = true;
	}

	prevF = nowF;
	prevP = nowP;
	prevL = nowL;


	return this;
}

void FIREBAR_Scene::Draw()
{
	m_pExpBar->Draw();


	printfDx("ZÇâüÇ∑Ç∆ïêäÌÉXÉeÅ[É^ÉXï\é¶");

	m_pWeaponMgr->Draw();

	printfDx("\n");

	m_pPlayerStatus->Draw();

	m_pPlayer->Draw();

	m_pEnemy->Draw();

	printfDx("\n");

	if (m_pLotteryPassive->ShowSlot())
	{
		m_pLotteryPassive->Draw();
	}
}