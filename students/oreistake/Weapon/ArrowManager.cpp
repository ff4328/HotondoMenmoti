#include "ArrowManager.h"
#include "Arrow.h"
#include<vector>
#include <DxLib.h>
#include "../students/bamboojr36/Vector2.h"
#include"../students/oreistake/Player.h"
namespace
{
	const char* const kGraphPath = ".\\Resource\\image\\Arrow.png";

	const int kMaxArrowNum = 10;

}

ArrowManager::ArrowManager():
	m_graphHandle(-1),
	m_pPlayermove(nullptr)
{

}

ArrowManager::ArrowManager(PlayerMove* pPlayermove):
	m_graphHandle(-1),
	m_pPlayermove(pPlayermove)
{
}

void ArrowManager::Init()
{

	m_graphHandle = LoadGraph(kGraphPath);

}

void ArrowManager::End()
{

	// ”ÍˆÍfor•¶
	for (auto& arrow : m_arrow) {

		arrow->End();

	}

	// vector‚Ì‰Â•Ï’·”z—ñ‚ðãY—í‚É‚·‚é
	m_arrow.clear();

	DeleteGraph(m_graphHandle);
}

void ArrowManager::Update()
{
	for (auto& arrow : m_arrow)
	{
		arrow->SetPlayerPos(m_pPlayermove->GetModelPos());

		arrow.get()->Update();
	}
}

void ArrowManager::Draw()
{
	for (auto& arrow : m_arrow)
	{
		arrow.get()->Draw();
	}
}

bool ArrowManager::Create(
	std::string name,
	float damage,
	float range,
	float attackRange,
	int coolTime,
	int weaponNum,
	Vector2 playerPos)
{
	auto arrow = std::make_unique<Arrow>(
		name,
		damage,
		range,
		attackRange,
		coolTime,
		weaponNum,
		playerPos,
		m_pPlayermove
	);

	arrow->Init();

	arrow->StartShot();

	m_arrow.push_back(std::move(arrow)); 

	return true;
}

Rect ArrowManager::GetCheckRect()
{
	if (m_arrow.empty()) return Rect{ 0,0,0,0 };

	return m_arrow[0]->GetCheckRect();
}