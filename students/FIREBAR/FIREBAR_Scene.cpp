#include "FIREBAR_Scene.h"
#include "WeaponManager.h"
#include "DxLib.h"

FIREBAR_Scene::FIREBAR_Scene():
	pWeaponMrg(nullptr)
{
}

void FIREBAR_Scene::Init()
{
	pWeaponMrg = new WeaponManager();
}

void FIREBAR_Scene::End()
{
	delete pWeaponMrg;
	pWeaponMrg = nullptr;
}

SceneBase* FIREBAR_Scene::Update()
{
	static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);

	bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);

	if (prevF && !nowF)
	{

		// 連続遷移防止
		nowF = true;

		// シーン遷移
		return new FIREBAR_Scene;

	}

	prevF = nowF;

	return nullptr;
}

void FIREBAR_Scene::Draw()
{
	printfDx("Zを押すと武器ステータス表示");

	pWeaponMrg->Draw();
	
}
