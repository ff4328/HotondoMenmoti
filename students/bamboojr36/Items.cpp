#include "Items.h"
#include "Heal.h"
#include "Random.h"
#include "DxLib.h"
#include <memory>
#include "Magnet.h"
#include "Bomb.h"
#include "Collision.h"
#include "EXPItem.h"
#include "../oreistake/Player.h"
#include "../FIREBAR/PlayerStatus.h"
#include "../System/SoundManager.h"
namespace {
	// アイテムの最大数
	constexpr int kMaxItems = 4;	
	
	//ファイルパス
	const char* const kItemHeal = ".\\Resource\\Item\\Heal.png";
	const char* const kItemGet = ".\\Resource\\Item\\Magnet.png";
	const char* const kItembomb = ".\\Resource\\Item\\Bomb.png";
	const char* const kItemEXP = ".\\Resource\\Item\\EXP.png";
	const char* const kIdlePath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png";
}

Items::Items():
	m_graphHandleHeal(-1),
	m_graphHandleMagnet(-1),
	m_graphHandleBomb(-1),
	m_graphHandleEXPItem(-1),
	m_graphHandlePlayer(-1),
	m_getexp(false),
	m_Player(false),
	Get(false),
	Count(0),
	m_bombTrigger(false),
	m_heal(nullptr),
	m_magnet(nullptr),
	m_bomb(nullptr),
	m_EXPItem(nullptr),
	m_player(nullptr),
	m_pPlayerStatus(nullptr),
	m_collision(nullptr)
{
}

Items::Items(PlayerMove* _player) :
	m_graphHandleHeal(-1),
	m_graphHandleMagnet(-1),
	m_graphHandleBomb(-1),
	m_graphHandleEXPItem(-1),
	m_graphHandlePlayer(-1),
	m_getexp(false),
	m_Player(false),
	Get(false),
	Count(0),
	m_bombTrigger(false),
	m_heal(nullptr),
	m_magnet(nullptr),
	m_bomb(nullptr),
	m_EXPItem(nullptr),
	m_player(_player),
	m_pPlayerStatus(nullptr),
	m_collision(nullptr)
{
}

Items::Items(PlayerMove* _player, PlayerStatus* playerstatus) :
	m_graphHandleHeal(-1),
	m_graphHandleMagnet(-1),
	m_graphHandleBomb(-1),
	m_graphHandleEXPItem(-1),
	m_graphHandlePlayer(-1),
	m_getexp(false),
	m_Player(false),
	Get(false),
	Count(0),
	m_bombTrigger(false),
	m_heal(nullptr),
	m_magnet(nullptr),
	m_bomb(nullptr),
	m_EXPItem(nullptr),
	m_player(_player),
	m_pPlayerStatus(playerstatus),
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
	m_graphHandlePlayer = LoadGraph(kIdlePath);
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
	// 全EXPにプレイヤーをセット
	for (auto& exp : m_expItems) {
		exp->SetPlayer(m_player);
	}

	// マグネット取得
	if (m_collision->CheckRectCommon(m_player->GetCheckRect(), m_magnet->GetCheckRrect())
		&& m_magnet->GetIsDown())
	{
		SoundManager::GetInstance().PlaySe(Sound::SE::ItemGet);
		m_magnet->Destroy();
		Get = true;
	}

	// 回復アイテム
	if (m_collision->CheckRectCommon(m_player->GetCheckRect(), m_heal->GetRect())
		&& m_heal->GetIsDown())
	{
		SoundManager::GetInstance().PlaySe(Sound::SE::ItemGet);
		m_heal->Destroy();
		m_pPlayerStatus->HealHP();
	}

	// EXP処理（削除を含むので index ループ）
	for (int i = 0; i < m_expItems.size(); )
	{
		auto& exp = m_expItems[i];

		// プレイヤーがEXPに触れたら取得 → 削除
		if (m_collision->CheckRectCommon(m_player->GetCheckRect(), exp->GetRect())
			&& exp->GetIsDown())
		{
			SoundManager::GetInstance().PlaySe(Sound::SE::ExpGet);
			exp->Destroy();
			m_expItems.erase(m_expItems.begin() + i);
			m_getexp = true;
			continue;
		}
		if (Get) {
			exp->GoPlayer();
		}
		i++;
	}
	if (m_expItems.size() == 0) {
		Get = false;
	}

	// ボム取得
	if (m_collision->CheckRectCommon(m_player->GetCheckRect(), m_bomb->GetCheckRect())
		&& m_bomb->GetIsDown())
	{
		SoundManager::GetInstance().PlaySe(Sound::SE::ItemGet);
		m_bomb->Destroy();
		m_bombTrigger = true;
	}
}



void Items::Draw()
{
	DebugDraw();

	m_heal->Draw();

	m_magnet->Draw();

	m_bomb->Draw();

	for (auto& exp : m_expItems)
	{

		exp->Draw();

	}

#ifdef _DEBUG

	printfDx("EXP数: %d\n", m_expItems.size());

#endif

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

	m_expItems.push_back(std::move(EXP));

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

bool Items::BombTrigger()
{

	if (m_bombTrigger)
	{

		m_bombTrigger = false;

		return true;

	}

	return false;

}


