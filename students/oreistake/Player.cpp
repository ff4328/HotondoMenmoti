#include "Player.h"
#include "Literal.h"

#include <DxLib.h>
#include"../students/bamboojr36/Collision.h"
#include"../students/bamboojr36/Vector2.h"
#include"../Utility/Input.h"
#include"../students/FIREBAR/PlayerStatus.h"
#include"../students/Yama596/Enemy/EnemyYama.h"
#include<math.h>
#include"../mcd6752Tuyoshi/Map/Map.h"
namespace {

	const char* const kIdlePath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png";

	const char* const kRunPath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Run.png";

	const char* const kDeadPath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Death.png";

}
PlayerMove::PlayerMove() :
	m_graphHandle{},
	m_playerSpeed(0),
	m_sizeX(150),
	m_sizeY(150),
	m_motionCounter(0),
	m_motionFrame(0),
	m_isAttackCheck(false),
	m_isdeadCheck(false),
	m_hp(0.0f),
	m_hpMax(0.0f),
	m_moveX(0.0f),
	m_moveY(0.0f),
	m_isMove(false),
	m_pWeponMgr(nullptr),
	m_pPlayerStatus(nullptr),
	m_map(nullptr),
	m_status(Status::STATUS_IDLE),
	m_currentPos(Vector2(400.0f,300.0f)),
	m_prevPos(m_currentPos),
	m_direction(Direction::DIRECTION_RIGHT)
{
	m_pPlayerStatus = new PlayerStatus();
	m_playerSpeed = m_pPlayerStatus->GetMoveSpeed();
	m_hp = m_pPlayerStatus->GetCurrentHP();
	m_hpMax = m_pPlayerStatus->GetMaxHP();

}

PlayerMove::PlayerMove(PlayerStatus* playerstatus) :
	m_graphHandle{},
	m_playerSpeed(0),
	m_sizeX(150),
	m_sizeY(150),
	m_motionCounter(0),
	m_motionFrame(0),
	m_isAttackCheck(false),
	m_isdeadCheck(false),
	m_hp(0.0f),
	m_hpMax(0.0f),
	m_moveX(0.0f),
	m_moveY(0.0f),
	m_isMove(false),
	m_pWeponMgr(nullptr),
	m_pPlayerStatus(playerstatus),
	m_map(nullptr),
	m_status(Status::STATUS_IDLE),
	m_currentPos(Vector2(400.0f, 300.0f)),
	m_prevPos(m_currentPos),
	m_direction(Direction::DIRECTION_RIGHT)
{
	m_pPlayerStatus = playerstatus;
	m_playerSpeed = m_pPlayerStatus->GetMoveSpeed();
	m_hp = m_pPlayerStatus->GetCurrentHP();
	m_hpMax = m_pPlayerStatus->GetMaxHP();
}

void PlayerMove::Init()
{
	InitAnimation();
}

void PlayerMove::End()
{}


void PlayerMove::InitAnimation()
{

	for (int i = 0; i < CHARA_STATUS_NUM; i++)
	{
		for (int j = 0; j < CHARA_MOTION_NUM; j++)
		{
			m_graphHandle[i][j] = 0;

		}
	}

	// プレイヤーの待機アニメーション読み込み
	LoadDivGraph(kIdlePath,
		8, 8,1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_IDLE]);

	// プレイヤーの移動アニメーション読み込み
	LoadDivGraph(kRunPath,
		8, 8,1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_RUN]);

	// プレイヤーの死亡アニメーション読み込み
	LoadDivGraph(kDeadPath,
		6, 6, 1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_DEAD]);
}

void PlayerMove::Update()
{
	if (Dead())return;
	m_hp = m_pPlayerStatus->GetCurrentHP();

	//////////////////　追加	//////////////////
	m_playerSpeed = m_pPlayerStatus->GetMoveSpeed();
	m_hp = m_pPlayerStatus->GetCurrentHP();
	m_hpMax = m_pPlayerStatus->GetMaxHP();
	//////////////////
	Edge();

	Move();

	Attack();
	Hp();


	if (m_motionCounter >= 10)
	{
		m_motionCounter = 0;
		m_motionFrame++;
		if (m_motionFrame >= 8)
		{
			m_motionFrame = 0;
		}
	}
	
}

void PlayerMove::Update(PlayerStatus* playerstatus)
{
	if (Dead()) {
		m_motionCounter++;
		if (m_motionCounter >= 10)
		{
			m_motionCounter = 0;
			m_motionFrame++;
			if (m_motionFrame >= 8)
			{
				m_motionFrame = 0;
			}
		}
		return;
	}
		
	m_hp = playerstatus->GetCurrentHP();

	//////////////////　追加	//////////////////
	m_playerSpeed = playerstatus->GetMoveSpeed();
	m_hp = playerstatus->GetCurrentHP();
	m_hpMax = playerstatus->GetMaxHP();
	//////////////////
	Edge();

	Move();

	Attack();
	Hp();
	m_motionCounter++;
	if (m_motionCounter >= 10)
	{
		m_motionCounter = 0;
		m_motionFrame++;
		if (m_motionFrame >= 8)
		{
			m_motionFrame = 0;
		}
	}

}

bool PlayerMove::Attack()
{
#ifdef _DEBUG

	if (CheckHitKey(KEY_INPUT_P))
	{
		m_isAttackCheck = true;
		return true;
	}
#endif
	return false;
}

bool PlayerMove::Hp()
{
#ifdef _DEBUG

	if (CheckHitKey(KEY_INPUT_O))
	{
		m_isdeadCheck = true;
		return true;
	}
#endif
	return false;
}

bool PlayerMove::Dead()
{
	if (m_motionCounter >= 10)
	{
		m_motionCounter = 0;
		m_motionFrame++;
		if (m_motionFrame >= 8)
		{
			m_motionFrame = 8;
		}
	}
	// hpの値が0以下ならtrueを返す
	if (m_hp <= 0) return true;

	// そうじゃなければfalseを返す
	return false;

}

void PlayerMove::Damage(float value)
{

	m_pPlayerStatus->SetCurrentHP(value);
	
	if (m_hp <= 0)
	{
		Dead();
	}

}

void PlayerMove::Heal(int value)
{

	m_pPlayerStatus->HealHP();

	// 最大HPを超えていないかチェック
	if (m_hp > m_hpMax) m_hp = m_hpMax;
}

void PlayerMove::Draw()
{
	
	// プレイヤー描画
	DrawRotaGraph((int)m_currentPos.x,(int)m_currentPos.y,
		1.0f,0,m_graphHandle[m_status][m_motionFrame],TRUE,m_direction);

#ifdef _DEBUG

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

#endif
	
}

void PlayerMove::Move()
{
	
	m_isMove = false;

	m_moveX = 0.0f;
	m_moveY = 0.0f;

	// 右
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		m_moveX += 1.0f;
		m_direction = Direction::DIRECTION_RIGHT;
		m_isMove = true;
	}

	// 左
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		m_moveX -= 1.0f;
		m_direction = Direction::DIRECTION_LEFT;
		m_isMove = true;
	}

	// 下
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		m_moveY += 1.0f;
		m_isMove = true;
	}

	// 上
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		m_moveY -= 1.0f;
		m_isMove = true;
	}

	// 斜め移動補正
	if (m_moveX != 0.0f && m_moveY != 0.0f)
	{
		float length = sqrtf(m_moveX * m_moveX + m_moveY * m_moveY);

		m_moveX /= length;
		m_moveY /= length;
	}

	// 移動
	m_currentPos.x += m_moveX * m_playerSpeed;
	m_currentPos.y += m_moveY * m_playerSpeed;

	// アニメーション状態
	if (m_isMove)
	{
		m_status = Status::STATUS_RUN;
	}
	else
	{
		m_status = Status::STATUS_IDLE;
	}
	if (Dead())
	{
		m_status = Status::STATUS_DEAD;
	}
}

void PlayerMove::RestorePos()
{
	m_currentPos = m_prevPos;
}

void PlayerMove::UpdatePrevPos()
{
	m_prevPos = m_currentPos;
}

Rect PlayerMove::GetCheckRect() {
	Rect myRect = {
		(m_currentPos.x-10),
		(m_currentPos.y-20),
		(m_currentPos.x+10),
		(m_currentPos.y+20),
	};

	return myRect;
}

void PlayerMove::Edge()
{
	if (m_currentPos.x <= 10) { m_currentPos.x = 10; }
	if (m_currentPos.x >= m_map->GetMapSizeX()) { m_currentPos.x = m_map->GetMapSizeX(); }
	if (m_currentPos.y < 10) { m_currentPos.y = 10; }
	if (m_currentPos.y >= m_map->GetMapSizeY()) { m_currentPos.y = m_map->GetMapSizeY(); }
}