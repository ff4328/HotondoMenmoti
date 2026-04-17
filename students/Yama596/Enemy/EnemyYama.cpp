#include<DxLib.h>
#include<math.h>
#include "../students/Yama596/Enemy/EnemyYama.h"
#include "../students/oreistake/Player.h"
#include "../students/FIREBAR/EnemyStatus.h"

namespace {

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Walk.png";

	const char* const kMushPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

	const int kBatHitPoint = 10;

	const int kGoblinHitPoint = 10;

	const int kSkeletonHitPoint = 10;

	const int kMushHitPoint = 10;

};

EnemyYama::EnemyYama() :
	m_graphHandle{},
	m_enemySpeed(1.0f),
	m_batCurrentPos(Vector2(300.0f, 200.0f)),
	m_goblinCurrentPos(Vector2(400.0f, 100.0f)),
	m_skeletonCurrentPos(Vector2(400.0f, 200.0f)),
	m_mushCurrentPos(Vector2(500.0f, 200.0f)),
	m_batMoveDir(Vector2()),
	m_goblinMoveDir(Vector2()),
	m_skeletonMoveDir(Vector2()),
	m_mushMoveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_enmeyType(EnemyTypeYama::ENEMY_TYPE_BAT_Yama),
	m_pPlayer(nullptr),
	m_pEnemyStatus(nullptr),
	m_pHp(nullptr)
{

	m_pEnemyStatus = new EnemyStatus;

}

EnemyYama::EnemyYama(EnemyStatus* enemystatus):
	m_graphHandle{},
	m_enemySpeed(1.0f),
	m_batCurrentPos(Vector2(300.0f, 200.0f)),
	m_goblinCurrentPos(Vector2(400.0f, 100.0f)),
	m_skeletonCurrentPos(Vector2(400.0f, 200.0f)),
	m_mushCurrentPos(Vector2(500.0f, 200.0f)),
	m_batMoveDir(Vector2()),
	m_goblinMoveDir(Vector2()),
	m_skeletonMoveDir(Vector2()),
	m_mushMoveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_enmeyType(EnemyTypeYama::ENEMY_TYPE_BAT_Yama),
	m_pPlayer(nullptr),
	m_pEnemyStatus(nullptr),
	m_pHp(nullptr)
{
}

void EnemyYama::Init()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < ENEMY_TYPE_MAX_Yama; i++) {

		for (int j = 0; j < ENEMY_MOTION_NUM_Yama; j++) {

			m_graphHandle[i][j] = 0;

		}

	}

	// m_pEnemyStatus.

	m_pHp = new HitPointYama;
	m_pHp->Init();
	m_pHp->SetHPMax(kSkeletonHitPoint);

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
	EnemyDraw();

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

		(m_batCurrentPos.x - 15),
		(m_batCurrentPos.y - 30),
		(m_batCurrentPos.x + 15),
		(m_batCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectGoblin()
{

	Rect myRect = {

		(m_goblinCurrentPos.x - 15),
		(m_goblinCurrentPos.y - 30),
		(m_goblinCurrentPos.x + 15),
		(m_goblinCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectSkeleton() {

	Rect myRect = {

		(m_skeletonCurrentPos.x - 15),
		(m_skeletonCurrentPos.y - 30),
		(m_skeletonCurrentPos.x + 15),
		(m_skeletonCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectMush()
{

	Rect myRect = {

		(m_mushCurrentPos.x - 15),
		(m_mushCurrentPos.y - 30),
		(m_mushCurrentPos.x + 15),
		(m_mushCurrentPos.y + 30),

	};

	return myRect;

}

void EnemyYama::SetPlayer(PlayerMove* pPlayer)
{

	m_pPlayer = pPlayer;

}

void EnemyYama::UpdateMove()
{

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_batCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_batMoveDir = dir.GetNormalize();

		}

	}

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_skeletonCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_skeletonMoveDir = dir.GetNormalize();

		}

	}

	// バットの移動処理
	m_batCurrentPos += m_batMoveDir * m_enemySpeed;

	// スケルトンの移動処理
	m_skeletonCurrentPos += m_skeletonMoveDir * m_enemySpeed;

}

void EnemyYama::SetGraphHandle(int enemyMgr[ENEMY_MOTION_NUM_Yama][ENEMY_TYPE_MAX_Yama])
{

	// エネミーマネージャーから受け取ったグラフィックハンドルを設定
	for (int i = 0; i < CHARA_MOB_NUM; i++) {

		for (int j = 0; j < CHARA_MOTION_NUM; j++) {

			m_graphHandle[i][j] = enemyMgr[i][m_enmeyType];

		}

	}

}

void EnemyYama::EnemyDraw()
{

	// バットの描画
	DrawRotaGraph((int)m_batCurrentPos.x, (int)m_batCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_BAT_Yama][m_motionFrame], TRUE);

	// バットの当たり判定の描画
	DrawBox(GetCheckRectBat().left, GetCheckRectBat().top, GetCheckRectBat().right, GetCheckRectBat().bottom, GetColor(255, 255, 255), false);

	// ゴブリンの描画
	DrawRotaGraph((int)m_goblinCurrentPos.x, (int)m_goblinCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_GOBLIN_Yama][m_motionFrame], TRUE);

	// ゴブリンの当たり判定の描画
	DrawBox(GetCheckRectGoblin().left, GetCheckRectGoblin().top, GetCheckRectGoblin().right, GetCheckRectGoblin().bottom, GetColor(255, 255, 255), false);

	// スケルトンを描画
	DrawRotaGraph((int)m_skeletonCurrentPos.x, (int)m_skeletonCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_SKELETON_Yama][m_motionFrame], TRUE);

	// スケルトンの当たり判定の描画
	DrawBox(GetCheckRectSkeleton().left, GetCheckRectSkeleton().top, GetCheckRectSkeleton().right, GetCheckRectSkeleton().bottom, GetColor(255, 255, 255), false);

	// マッシュルームの描画
	DrawRotaGraph((int)m_mushCurrentPos.x, (int)m_mushCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_MUSH_Yama][m_motionFrame], TRUE);

	// マッシュルームの当たり判定の描画
	DrawBox(GetCheckRectMush().left, GetCheckRectMush().top, GetCheckRectMush().right, GetCheckRectMush().bottom, GetColor(255, 255, 255), false);

}
