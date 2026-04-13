#include "FIREBAR_Scene.h"
#include "WeaponManager.h"

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
	return nullptr;
}

void FIREBAR_Scene::Draw()
{
	pWeaponMrg->Draw();
	
}
