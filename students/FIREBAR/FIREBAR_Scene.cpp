#include "FIREBAR_Scene.h"
#include "../Utility/Input.h"
#include "../students/Yama596/Scene/SceneMain.h"

#include "LotteryPusive.h"
#include "WeaponManager.h"

#include <string>
#include <vector>
#include <iostream>

#include "DxLib.h"

FIREBAR_Scene::FIREBAR_Scene()
{
}

void FIREBAR_Scene::Init()
{
	pLotteryPassive = std::make_unique<LotteryPusive>();
	pLotteryPassive->Init();

	pWeaponMgr = std::make_unique<WeaponManager>();
}

void FIREBAR_Scene::End()
{
	pLotteryPassive->End();
	pWeaponMgr->End();
}

SceneBase* FIREBAR_Scene::Update()
{
	pLotteryPassive->Update();

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
	else if (nowP && !prevP)
	{

		// ˜A‘±‘JˆÚ–hŽ~
		prevP = true;

		pLotteryPassive->RandomLottery();

	}

	prevF = nowF;
	prevP = nowP;

	return this;
}

void FIREBAR_Scene::Draw()
{
	printfDx("Z‚ð‰Ÿ‚·‚Æ•ŠíƒXƒe[ƒ^ƒX•\Ž¦");

	pLotteryPassive->Draw();

	pWeaponMgr->Draw();
}
