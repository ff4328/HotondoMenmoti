#include "Items.h"
#include "Collision.h"
#include "Heal.h"
<<<<<<< HEAD
#include "Random.h"
#include "DxLib.h"
#include <memory>
=======
>>>>>>> a05bffaedc62b094ff594c0154714b7370b0c939
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
<<<<<<< HEAD

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
=======
	for (auto& item : m_itemPos) {
		item->Draw(m_graphHandleHeal);
	}
>>>>>>> a05bffaedc62b094ff594c0154714b7370b0c939
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
<<<<<<< HEAD
	position.x = MyRandom::Int(0,Length);
	position.y = MyRandom::Int(0,Length);
=======
	position.x = static_cast<float>(rand() % static_cast<int>(Length));
	position.y = static_cast<float>(rand() % static_cast<int>(Length));
>>>>>>> a05bffaedc62b094ff594c0154714b7370b0c939

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
<<<<<<< HEAD
	printfDx("%d\n", m_itemPos.size());
}
=======
	m_collision->DebugDraw();
}
>>>>>>> a05bffaedc62b094ff594c0154714b7370b0c939
