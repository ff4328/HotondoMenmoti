#include "Items.h"
#include "Collision.h"
#include "Heal.h"
#include "Random.h"
#include "DxLib.h"
#include <memory>
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
	m_collision(nullptr)
{
}

void Items::Init()
{
	m_collision = std::make_unique<Collision>();
	m_graphHandleHeal = LoadGraph(kItemHeal);
	m_graphHandleMagnet = LoadGraph(kItemGet);
	m_graphHandleBomb = LoadGraph(kItembomb);
}

void Items::End()
{
	for(auto& item : m_itemPos) {
		item->End();
	}

	m_itemPos.clear();

	DeleteGraph(m_graphHandleHeal);
	DeleteGraph(m_graphHandleMagnet);
	DeleteGraph(m_graphHandleBomb);
}


void Items::Update()
{
	for(auto& item : m_itemPos) {
		item->Update();
	}
}

void Items::Draw()
{
	DebugDraw();

	DrawExtendGraph(
		m_itemPos.size(), 0,
		m_itemPos.size() + 50, 50,
		m_graphHandleHeal, TRUE);
	DrawExtendGraph(
		50, m_itemPos.size(),
		100, m_itemPos.size() + 50,
		m_graphHandleMagnet, TRUE);
	DrawExtendGraph(
		m_itemPos.size() + 100, m_itemPos.size(),
		m_itemPos.size() + 150, m_itemPos.size() + 50,
		m_graphHandleBomb, TRUE);
}

bool Items::Create(const Vector2& position)
{
	auto item = std::make_unique<Heal>(position);
	item->Init();

	m_itemPos.push_back(std::move(item));

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
	if(index < 0 || index >= GetItemNum()) {
		return;
	}
	m_itemPos[index]->End();

	m_itemPos.erase(m_itemPos.begin() + index);
}

void Items::DebugDraw(){
	printfDx("%d\n", m_itemPos.size());
}
