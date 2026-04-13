#include "FIREBAR_Scene.h"
#include "WeaponManager.h"
#include "LotteryPusive.h"
#include "../students/Yama596/Scene/SceneMain.h"

#include <string>
#include <vector>
#include <iostream>

#include "DxLib.h"

FIREBAR_Scene::FIREBAR_Scene():
	pWeaponMrg(nullptr),
	pLotteryPusive(nullptr)
{
}

void FIREBAR_Scene::Init()
{
	pWeaponMrg = new WeaponManager();
	pLotteryPusive = new LotteryPusive();

	pLotteryPusive->Init();
}

void FIREBAR_Scene::End()
{
	pWeaponMrg->End();
	delete pWeaponMrg;
	pWeaponMrg = nullptr;

	pLotteryPusive->End();
	delete pLotteryPusive;
	pLotteryPusive = nullptr;
}

SceneBase* FIREBAR_Scene::Update()
{
	static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);
	static bool prevP = (CheckHitKey(KEY_INPUT_P) == 1);

	bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);
	bool nowP = (CheckHitKey(KEY_INPUT_P) == 1);

	if (nowF && !prevF)
	{

		// ˜A‘±‘JˆÚ–hŽ~
		prevF = true;

		// ƒV[ƒ“‘JˆÚ
		return new SceneMain;

	}
	else if ( nowP&& !prevP)
	{
		// ˜A‘±‘JˆÚ–hŽ~
		prevP = true;

		pLotteryPusive->RandomLottery();
	}

	prevF = nowF;
	prevP = nowP;

	return this;
}

void FIREBAR_Scene::Draw()
{
	printfDx("Z‚ð‰Ÿ‚·‚Æ•ŠíƒXƒe[ƒ^ƒX•\Ž¦");

	pWeaponMrg->Draw();

	pLotteryPusive->Draw();
	
}
