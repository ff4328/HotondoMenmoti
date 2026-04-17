#include "../students/Yama596/Enemy/EnemyYama.h"
#include<DxLib.h>
#include<math.h>
#include "../students/Yama596/Enemy/LiteralYama.h"
#include "../students/oreistake/Player.h"

namespace {

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Walk.png";

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const char* const kMushPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

};

EnemyYama::EnemyYama() :
	m_graphHandle(),
	m_enemySpeed(1.0f),
	m_BatCurrentPos(Vector2(300.0f, 200.0f)),
	m_GoblinCurrentPos(Vector2(400.0f, 100.0f)),
	m_SkeletonCurrentPos(Vector2(400.0f, 200.0f)),
	m_MushCurrentPos(Vector2(500.0f, 200.0f)),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_enmeyType(EnemyType::ENEMY_TYPE_GOBLIN),
	m_direction(DIRECTION_RIGHT),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{
}

void EnemyYama::Init()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < CHARA_MOB_NUM_Yama; i++) {

		for (int j = 0; j < CHARA_MOTION_NUM_Yama; j++) {

			m_graphHandle[i][j] = 0;

		}

	}

	m_pHp = new HitPointYama;
	m_pHp->Init();
	m_pHp->SetHPMax(ENEMY_HP_MAX_Yama);

	InitAnimation();

}

void EnemyYama::InitAnimation()
{

	LoadDivGraph(kBatPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_BAT_Yama]);

	LoadDivGraph(kGoblinPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_GOBLIN_Yama]);

	LoadDivGraph(kSkeletonPath,
		4, 4, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_SKELETON_Yama]);

	LoadDivGraph(kMushPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_MUSH_Yama]);

}

void EnemyYama::End()
{

}

void EnemyYama::Update()
{

	if (Dead()) return;

	UpdateMove();

}

void EnemyYama::Draw()
{

	if (Dead()) return;

	// モーション制御用のカウンタをカウントアップ
	m_motionCounter++;

	// アニメーションのフレームを1コマ進める
	if (m_motionCounter % 20 == 0) {

		m_motionCounter = 0;

		// 敵のアニメーションは全部で4コマ想定なので
		m_motionFrame++;
		m_motionFrame = m_motionFrame % 4;

	}

	// 敵の描画
	BatDraw();
	GoblinDraw();
	SkeletonDraw();
	MushDraw();

	//printfDx("mobPosX : %f\n", m_SkeletonCurrentPos.x);
	//printfDx("mobPosX : %f\n", m_SkeletonCurrentPos.y);

}

void EnemyYama::Damege(int value)
{

	m_pHp->Damage(value);

}

bool EnemyYama::Dead()
{

	return m_pHp->IsDead();

}

Rect EnemyYama::GetCheckRectBat()
{

	Rect myRect = {

		(m_BatCurrentPos.x - 15),
		(m_BatCurrentPos.y - 30),
		(m_BatCurrentPos.x + 15),
		(m_BatCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectGoblin()
{

	Rect myRect = {

		(m_GoblinCurrentPos.x - 15),
		(m_GoblinCurrentPos.y - 30),
		(m_GoblinCurrentPos.x + 15),
		(m_GoblinCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectSkeleton() {

	Rect myRect = {

		(m_SkeletonCurrentPos.x - 15),
		(m_SkeletonCurrentPos.y - 30),
		(m_SkeletonCurrentPos.x + 15),
		(m_SkeletonCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectMush()
{

	Rect myRect = {

		(m_MushCurrentPos.x - 15),
		(m_MushCurrentPos.y - 30),
		(m_MushCurrentPos.x + 15),
		(m_MushCurrentPos.y + 30),

	};

	return myRect;

}

void EnemyYama::SetPlayer(PlayerMove* pPlayer)
{

	m_pPlayer = pPlayer;

}

void EnemyYama::UpdateMove()
{

	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_SkeletonCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

	}

	m_SkeletonCurrentPos += m_moveDir * m_enemySpeed;

}

void EnemyYama::SetGraphHandle(int enemyMgr[CHARA_MOTION_NUM_Yama][ENEMY_TYPE_MAX_Yama])
{

	// エネミーマネージャーから受け取ったグラフィックハンドルを設定
	for (int i = 0; i < CHARA_MOTION_NUM; i++) {

		for (int j = 0; j < CHARA_MOB_NUM; j++) {

			m_graphHandle[i][j] = enemyMgr[i][m_enmeyType];

		}

	}

}

void EnemyYama::BatDraw()
{

	DrawRotaGraph((int)m_BatCurrentPos.x, (int)m_BatCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_BAT_Yama][m_motionFrame], TRUE);

	DrawBox(GetCheckRectBat().left, GetCheckRectBat().top, GetCheckRectBat().right, GetCheckRectBat().bottom, GetColor(255, 255, 255), false);

}


void EnemyYama::GoblinDraw()
{

	DrawRotaGraph((int)m_GoblinCurrentPos.x, (int)m_GoblinCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_GOBLIN_Yama][m_motionFrame], TRUE);

	DrawBox(GetCheckRectGoblin().left, GetCheckRectGoblin().top, GetCheckRectGoblin().right, GetCheckRectGoblin().bottom, GetColor(255, 255, 255), false);

}

void EnemyYama::SkeletonDraw()
{

	DrawRotaGraph((int)m_SkeletonCurrentPos.x, (int)m_SkeletonCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_SKELETON_Yama][m_motionFrame], TRUE);

	DrawBox(GetCheckRectSkeleton().left, GetCheckRectSkeleton().top, GetCheckRectSkeleton().right, GetCheckRectSkeleton().bottom, GetColor(255, 255, 255), false);

}

void EnemyYama::MushDraw()
{

	DrawRotaGraph((int)m_MushCurrentPos.x, (int)m_MushCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_MUSH_Yama][m_motionFrame], TRUE);

	DrawBox(GetCheckRectMush().left, GetCheckRectMush().top, GetCheckRectMush().right, GetCheckRectMush().bottom, GetColor(255, 255, 255), false);

}
