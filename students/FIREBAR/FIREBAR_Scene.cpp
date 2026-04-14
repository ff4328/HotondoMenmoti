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

FIREBAR_Scene::FIREBAR_Scene():
	pWeaponMgr(nullptr),
	pPlayerStatus(nullptr),
	m_pExpBar(nullptr)
{
}

void FIREBAR_Scene::Init()
{
	// pWeaponMgrとpPlayerStatusのインスタンスを生成
	pWeaponMgr = new WeaponManager();
	pPlayerStatus = new PlayerStatus();
	m_pExpBar = new EXPBar(pPlayerStatus);

	pLotteryPassive = std::make_unique<LotteryPusive>(pWeaponMgr, pPlayerStatus);

	pLotteryPassive->Init();
	pPlayerStatus->Init();
	m_pExpBar->Init();
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
	//m_pExpBar->Update();

	pPlayerStatus->Update();

	pLotteryPassive->Update();

	static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);
	static bool prevP = (CheckHitKey(KEY_INPUT_P) == 1);

	bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);
	bool nowP = (CheckHitKey(KEY_INPUT_P) == 1);

	if (nowF && !prevF)
	{

		// 連続遷移防止
		prevF = true;

		// シーン遷移
		return new SceneMain;

	}
	else if (nowP && !prevP)
	{

		// 連続遷移防止
		prevP = true;

		pLotteryPassive->RandomLottery();

	}

	prevF = nowF;
	prevP = nowP;

	return this;
}

void FIREBAR_Scene::Draw()
{
	m_pExpBar->Draw();


	printfDx("Zを押すと武器ステータス表示");

	pWeaponMgr->Draw();

	printfDx("\n");

	pPlayerStatus->Draw();

	printfDx("\n");

	pLotteryPassive->Draw();
}
