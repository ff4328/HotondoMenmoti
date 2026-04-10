#include "Items.h"
namespace {
	// アイテムの最大数
	constexpr int kMaxItems = 3;	
	
	//ファイルパス
	//const char* const kItemHeal = "Resources/ItemHeal.png";
	//const char* const kItemGet = "Resources/ItemGet.png";
	//const char* const kItembomb = "Resources/Itembomb.png";
}

void Items::Init()
{
	//m_graphHandle = LoadGraph(kGraphPath);
}

void Items::End()
{
}

void Items::Update()
{
}

void Items::Draw()
{
}

bool Items::Create(const Vector2& position)
{
	return true;
}

bool Items::RamdumCreate(float Length)
{
	return true;
}

void Items::Remove(int index)
{
}


void Items::CheckCollision(const Vector2& playerPos, float playerSize)
{
}

void DebugDraw() {

}

