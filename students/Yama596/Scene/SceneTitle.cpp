#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	return nullptr;
}

void SceneTitle::Draw()
{

#ifdef _DEBUG

	printfDx("ここはタイトルシーンです");

#endif

}
