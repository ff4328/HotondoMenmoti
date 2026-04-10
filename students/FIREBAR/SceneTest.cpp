
#include "SceneTest.h"
#include "SceneBase.h"
#include <DxLib.h>
#include "../Utility/Input.h"
#include "../Utility/Color.h"
#include "../Utility/GameSetting.h"
#include "../System/SoundManager.h"
#include "../FIREBAR/WeaponManager.h"
#include <math.h>

namespace
{

}

SceneTest::SceneTest():
	pWeaponMrg(nullptr)
{}
SceneTest::~SceneTest() {}

void SceneTest::Init()
{

	pWeaponMrg = new WeaponManager;

}

void SceneTest::End() {

	delete pWeaponMrg;

	pWeaponMrg = nullptr;
}

SceneBase* SceneTest::Update()
{

	
	return this;
}

void SceneTest::Draw()
{

	pWeaponMrg->Draw();
}