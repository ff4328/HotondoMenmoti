#include "FIREBAR_Scene.h"
#include "../Utility/Input.h"
#include "../students/Yama596/Scene/SceneMain.h"

#include "LotteryPusive.h"
#include "WeaponManager.h"
#include "PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"

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
	pLotteryPassive(nullptr),
	pWeaponMgr(nullptr),
	pPlayerStatus(nullptr),
	m_pExpBar(nullptr)
{
}

void FIREBAR_Scene::Init()
{
	// pWeaponMgrÇ∆pPlayerStatusÇÃÉCÉìÉXÉ^ÉìÉXÇê∂ê¨
	pWeaponMgr = new WeaponManager();
	pPlayerStatus = new PlayerStatus();
	m_pExpBar = new EXPBar(pPlayerStatus);

	pLotteryPassive = std::make_unique<LotteryPusive>(pWeaponMgr, pPlayerStatus, m_pExpBar);

	pPlayerStatus->Init();
	m_pExpBar->Init();
	pLotteryPassive->Init();
}

void FIREBAR_Scene::End()
{
	pLotteryPassive->End();

	pWeaponMgr->End();
	delete pWeaponMgr;
	pWeaponMgr = nullptr;

	pPlayerStatus->End();
	delete pPlayerStatus;
	pPlayerStatus = nullptr;

	m_pExpBar->End();
	delete m_pExpBar;
	m_pExpBar = nullptr;
}

SceneBase* FIREBAR_Scene::Update()
{
	m_pExpBar->Update(kget,5);

	pPlayerStatus->Update();

	pLotteryPassive->Update();

	//pLotteryPassive->ShowSlot(kget_2);

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

	pWeaponMgr->Draw();

	printfDx("\n");

	pPlayerStatus->Draw();

	printfDx("\n");

	if (pLotteryPassive->ShowSlot())
	{
		pLotteryPassive->Draw();
	}
}