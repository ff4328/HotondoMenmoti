#include "Items.h"
#include "Heal.h"
#include "Random.h"
#include "DxLib.h"
#include <memory>
#include "Magnet.h"
#include "Bomb.h"
#include "Collision.h"
namespace {
	// アイテムの最大数
	constexpr int kMaxItems = 4;	
	
	//ファイルパス
	const char* const kItemHeal = ".\\Resource\\Item\\Heal.png";
	const char* const kItemGet = ".\\Resource\\Item\\Magnet.png";
	const char* const kItembomb = ".\\Resource\\Item\\Bomb.png";
	const char* const kItemEXP = ".\\Resource\\Item\\EXP.png";
}

Items::Items():
	m_graphHandleHeal(-1),
	m_graphHandleMagnet(-1),
	m_graphHandleBomb(-1),
	m_graphHandleEXPItem(-1),
	m_heal(nullptr),
	m_magnet(nullptr),
	m_bomb(nullptr),
	m_EXPItem(nullptr),
	m_collision(nullptr)
{
}

void Items::Init()
{	m_heal = std::make_unique<Heal>();
	m_heal->Init();

	m_magnet = std::make_unique<Magnet>();
	m_magnet->Init();

	m_bomb = std::make_unique<Bomb>();
	m_bomb->Init();

	m_EXPItem = std::make_unique<EXPItem>();
	m_EXPItem->Init();

	m_collision = std::make_unique<Collision>();

	m_graphHandleHeal = LoadGraph(kItemHeal);
	m_graphHandleMagnet = LoadGraph(kItemGet);
	m_graphHandleBomb = LoadGraph(kItembomb);
	m_graphHandleEXPItem = LoadGraph(kItemEXP);
}

void Items::End()
{
	m_heal->End();
	m_heal.reset();

	m_magnet->End();
	m_magnet.reset();

	m_bomb->End();
	m_bomb.reset();

	m_EXPItem->End();
	m_EXPItem.reset();
}


void Items::Update()
{
	m_heal->Update();
	m_magnet->Update();
	m_bomb->Update();
	if (!(m_collision->CheckRectCommon(m_EXPItem->GetRect(), m_heal->GetRect()) ||
		m_collision->CheckRectCommon(m_EXPItem->GetRect(), m_magnet->GetCheckRrect()) ||
		m_collision->CheckRectCommon(m_EXPItem->GetRect(), m_bomb->GetCheckRect()))) {
		m_EXPItem->Update();
	}
}

void Items::Draw()
{
	DebugDraw();

	m_heal->Draw();

	m_magnet->Draw();

	m_bomb->Draw();

	//今当たってたら移すのを辞めるだから今度書き換える
	//当たったら消える＆経験値の増加
	if (!(m_collision->CheckRectCommon(m_EXPItem->GetRect(), m_heal->GetRect()) ||
		m_collision->CheckRectCommon(m_EXPItem->GetRect(), m_magnet->GetCheckRrect()) ||
		m_collision->CheckRectCommon(m_EXPItem->GetRect(), m_bomb->GetCheckRect()))) {
		m_EXPItem->Draw();
	}
}

bool Items::Create(const Vector2& position)
{
	auto heal = std::make_unique<Heal>(position);
	heal->Init();
	auto magnet = std::make_unique<Magnet>(position);
	magnet->Init();
	auto bomb = std::make_unique<Bomb>(position);
	bomb->Init();
	auto EXP = std::make_unique<EXPItem>(position);
	EXP->Init();
	return true;
}

bool Items::RamdumCreate(float Length)
{
	Vector2 position;
	position.x = MyRandom::Int(0,Length);
	position.y = MyRandom::Int(0,Length);

	return Create(position);
}

void Items::Remove(int index)
{
}

void Items::DebugDraw(){
}