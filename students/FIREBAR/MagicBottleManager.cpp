#include "MagicBottleManager.h"
#include "MagicBottle.h"

#include "../students/oreistake/Player.h"

#include <DxLib.h>
#include <vector>
#include <memory>

namespace {

	// 画像のファイルパス
	const char* const kGraphPath = "Resource\\image\\MagicBottle.png";
}

MagicBottleManager::MagicBottleManager() :
	m_graphHandle(-1),
	m_pPlayer(nullptr)
{
	//m_pPlayer = new PlayerMove();
}

MagicBottleManager::MagicBottleManager(PlayerMove* pPlayer) :
	m_graphHandle(-1),
	m_pPlayer(pPlayer)
{
}

MagicBottleManager::~MagicBottleManager()
{
}

void MagicBottleManager::Init()
{
	m_graphHandle = LoadGraph(kGraphPath);
}

void MagicBottleManager::End()
{

	// 範囲for文
	for (auto& grass : m_MagicBottle) {

		grass->End();

	}

	// vectorの可変長配列を綺麗にする
	m_MagicBottle.clear();

	DeleteGraph(m_graphHandle);

}

void MagicBottleManager::Update()
{

	for (auto& grass : m_MagicBottle) {

		grass->SetPlayerPos(m_pPlayer->GetModelPos());

		grass->Update();

	}

}

void MagicBottleManager::Draw()
{

	//DebugDraw();

	for (auto& grass : m_MagicBottle) {

		grass->Draw(m_graphHandle);

	}

}

bool MagicBottleManager::Create(
	std::string name,
	float damage,
	float range,
	float attackRange,
	int coolTime,
	int weaponNum,
	Vector2 playerPos)
{

	// 草の生成
	auto grass = std::make_unique<MagicBottle>(name, damage, range, attackRange, coolTime, weaponNum, playerPos);
	grass->Init();

	grass->StartFall();

	// 生成した草を配列に登録
	// vector可変長配列はpush_backで配列の末尾に要素数を追加できる
	// m_grasses.push_back(grass);

	// unique_ptrを使って配列の要素に格納するときはmoveを使う
	// unique_ptrは一つしか所有権を持てないのでコピーできない
	m_MagicBottle.push_back(std::move(grass));

	return true;

}