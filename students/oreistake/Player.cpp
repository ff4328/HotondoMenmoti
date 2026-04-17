#include "Player.h"
#include "Literal.h"

#include <DxLib.h>
#include"../students/bamboojr36/Collision.h"
#include"../students/bamboojr36/Vector2.h"
#include"../Utility/Input.h"
#include"../students/FIREBAR/PlayerStatus.h"
#include"../students/Yama596/Enemy/EnemyYama.h"
#include<math.h>
#include "Enemy.h"
namespace {

	const char* const kIdlePath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png";

	const char* const kRunPath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Run.png";

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
	m_angle(0),
	m_radius(100.0f),
	m_pWeponMgr(nullptr),
	m_pPlayerStatus(nullptr),
	m_pEnemyYama(nullptr),
	m_status(Status::STATUS_IDLE),
	m_currentPos(Vector2(400.0f,300.0f)),
	m_prevPos(m_currentPos)
{
	m_pPlayerStatus = new PlayerStatus();
	m_playerSpeed = m_pPlayerStatus->GetMoveSpeed();
	m_hp = m_pPlayerStatus->GetCurrentHP();
	m_hpMax = m_pPlayerStatus->GetMaxHP();

	m_pEnemyYama = new EnemyYama();
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
	m_angle(0),
	m_radius(100.0f),
	m_pWeponMgr(nullptr),
	m_pPlayerStatus(playerstatus),
	m_status(Status::STATUS_IDLE),
	m_currentPos(Vector2(400.0f, 300.0f)),
	m_prevPos(m_currentPos)
{
}

void PlayerMove::Init()
{
	//m_pPlayerStatus = new PlayerStatus();
	//m_playerSpeed = m_pPlayerStatus->GetMoveSpeed();
	InitAnimation();
}

void PlayerMove::End()
{



}


void PlayerMove::InitAnimation()
{
	// プレイヤーの待機アニメーション読み込み
	LoadDivGraph(kIdlePath,
		8, 8,1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_IDLE]);

	//// プレイヤーの移動アニメーション読み込み
	//LoadDivGraph(kRunPath,
	//	8, 8,1, m_sizeX, m_sizeY,
	//	m_graphHandle[STATUS_RUN]);
}

void PlayerMove::Update()
{
	if (m_pEnemyYama->Dead())return;
	//m_playerSpeed = m_pPlayerStatus->GetMoveSpeed();
	m_hp = m_pPlayerStatus->GetCurrentHP();

	MoveHorizontal();
	MoveVertical();
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

	/*//float angle = 0.0f;        // 回転角度（ラジアン）
	//float radius = 80.0f;      // 回転半径
	//float speed = 0.05f;      // 回転速度

	//// 円運動の計算
	//float ox = m_currentPos.x + cosf(angle) * radius;
	//float oy = m_currentPos.y + sinf(angle) * radius;

	//// 回転角度を進める
	//angle += speed;

	//// 回転するオブジェクト描画
	//DrawCircle(ox, oy, 6, GetColor(255, 0, 0), TRUE);*/

	

	
	
	

	printfDx("angle : %f\n", m_angle);
}

bool PlayerMove::Attack()
{
	if (CheckHitKey(KEY_INPUT_P))
	{
		m_isAttackCheck = true;
		return true;
	}
	return false;
}

bool PlayerMove::Hp()
{

	if (CheckHitKey(KEY_INPUT_O))
	{
		m_isdeadCheck = true;
		return true;
	}

	return false;
}

bool PlayerMove::Dead()
{

	// hpの値が0以下ならtrueを返す
	if (m_hp <= 0) return true;

	if (m_hp <= 0)
	{
		m_hp = 0;
	}

	// そうじゃなければfalseを返す
	return false;

	return false;

}

void PlayerMove::Damage(float value)
{

	m_pPlayerStatus->SetCurrentHP(value);
	
	if (m_hp <= 0)
	{
		Dead();
	}

	//m_pHp->Damage(value);
}

void PlayerMove::Heal(int value)
{

	m_pPlayerStatus->SetCurrentHP(value);

	// 最大HPを超えていないかチェック
	if (m_hp > m_hpMax) m_hp = m_hpMax;
}

void PlayerMove::Draw()
{
	if (m_pEnemyYama->Dead())return;

	// プレイヤー描画
	DrawRotaGraph((int)m_currentPos.x,(int)m_currentPos.y,
		1.0f,0,m_graphHandle[m_status][m_motionFrame],TRUE);

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

	m_angle += 0.05f;


	int x = m_currentPos.x + (int)(cosf(m_angle) * m_radius);
	int y = m_currentPos.y + (int)(sinf(m_angle) * m_radius);


	DrawCircle(x, y, 20, GetColor(255, 0, 0), TRUE);

	printfDx("PosX : %f\n", m_currentPos.x);
	printfDx("PosX : %f\n", m_currentPos.y);
	printfDx("speed : %f\n", m_playerSpeed);
	printfDx("attack : %d\n", m_isAttackCheck);
	printfDx("dead : %d\n", m_isdeadCheck);
	printfDx("HP : %f\n", m_hp);

}

void PlayerMove::MoveHorizontal()
{
	// 右移動
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		m_currentPos.x += m_playerSpeed;
	}

	// 左移動
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		m_currentPos.x -= m_playerSpeed;
	}
}

void PlayerMove::MoveVertical()
{
	// 下移動
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		m_currentPos.y += m_playerSpeed;
	}

	// 上移動
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		m_currentPos.y -= m_playerSpeed;
	}
}

void PlayerMove::Finalize()
{

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

