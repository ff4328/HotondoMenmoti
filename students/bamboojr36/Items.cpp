#include "Items.h"
#include "Collision.h"
#include "Heal.h"
namespace {
	// アイテムの最大数
	constexpr int kMaxItems = 3;	
	
	//ファイルパス
	const char* const kItemHeal = "Resources/Item/Heal.png";
	const char* const kItemGet = "Resources/Item/Magnet.png";
	const char* const kItembomb = "Resources/Item/Bomb.png";
}

void Items::Init()
{
	m_graphHandleHeal = LoadGraph(kItemHeal);
	m_graphHandleMagnet = LoadGraph(kItemGet);
	m_graphHandleBomb = LoadGraph(kItembomb);
}

void Items::End()
{
	for(auto& item : m_itemPos) {
		item->End();
	}

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
	for (auto& item : m_itemPos) {
		item->Draw(m_graphHandleHeal);
	}
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
	position.x = static_cast<float>(rand() % static_cast<int>(Length));
	position.y = static_cast<float>(rand() % static_cast<int>(Length));

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
	m_collision->DebugDraw();
}