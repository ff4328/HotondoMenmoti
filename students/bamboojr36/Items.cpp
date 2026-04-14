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
	constexpr int kMaxItems = 3;	
	
	//ファイルパス
	const char* const kItemHeal = ".\\Resource\\Item\\Heal.png";
	const char* const kItemGet = ".\\Resource\\Item\\Magnet.png";
	const char* const kItembomb = ".\\Resource\\Item\\Bomb.png";
}

Items::Items():
	m_graphHandleHeal(-1),
	m_graphHandleMagnet(-1),
	m_graphHandleBomb(-1),
	m_heal(nullptr),
	m_magnet(nullptr),
	m_bomb(nullptr),
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

	m_collision = std::make_unique<Collision>();

	m_graphHandleHeal = LoadGraph(kItemHeal);
	m_graphHandleMagnet = LoadGraph(kItemGet);
	m_graphHandleBomb = LoadGraph(kItembomb);
}

void Items::End()
{
	m_heal->End();
	m_heal.reset();

	m_magnet->End();
	m_magnet.reset();

	m_bomb->End();
	m_bomb.reset();
}


void Items::Update()
{
	m_heal->Update();
	m_magnet->Update();
	m_bomb->Update();

	m_collision->CheckRectCommon(m_heal->GetRect(), m_magnet->GetCheckRrect());
	m_collision->CheckRectCommon(m_heal->GetRect(), m_bomb->GetCheckRect());
	m_collision->CheckRectCommon(m_magnet->GetCheckRrect(), m_bomb->GetCheckRect());
}

void Items::Draw()
{
	DebugDraw();

	m_heal->Draw();

	m_magnet->Draw();

	m_bomb->Draw();
}

bool Items::Create(const Vector2& position)
{
	auto heal = std::make_unique<Heal>(position);
	heal->Init();
	auto magnet = std::make_unique<Magnet>(position);
	magnet->Init();
	auto bomb = std::make_unique<Bomb>(position);
	bomb->Init();
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
