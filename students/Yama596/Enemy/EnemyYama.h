#pragma once

#include "../students/Yama596/Enemy/LiteralYama.h"
#include "../students/bamboojr36/Vector2.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"
#include"../students/bamboojr36/Collision.h"

class EnemyYama
{

public:

	EnemyYama();

	~EnemyYama() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理を行う
	/// </summary>
	void End();

	/// <summary>
	/// アニメーションの初期設定
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 表示
	/// </summary>
	void Draw();

	/// <summary>
	/// 座標を1F前に戻す
	/// </summary>
	void RestorePos();

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="value"></param>
	void Damege(int value);

	/// <summary>
	/// 死亡処理
	/// </summary>
	bool Dead();

	/// <summary>
	/// 敵のレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

private:

	/// <summary>
	/// 1F前の座標を更新
	/// </summary>
	void UpdatePrevPos();

	/// <summary>
	/// 移動更新処理
	/// </summary>
	void UpdateMove();

	/// <summary>
	/// 敵のタイプを設定する関数
	/// </summary>
	/// <param name="enemytype"></param>
	void SetEnemyType(EnemyType enamytype) { m_enmeyType = enamytype; }

	/// <summary>
	/// グラフィックハンドルの初期設定
	/// </summary>
	/// <param name="enemyMgr"></param>
	void SetGraphHandle(int enemyMgr[CHARA_MOTION_NUM_Yama][ENEMY_TYPE_MAX_Yama]);

private:

	int m_graphHandle[CHARA_MOTION_NUM_Yama][CHARA_MOB_NUM_Yama];

	float m_enemySpeed;

	/// <summary>
	/// プレイヤーモデルの座標
	/// </summary>
	Vector2 m_currentPos;

	/// <summary>
	/// プレイヤーの1F前の座標
	/// </summary>
	Vector2 m_prevPos;

	/// <summary>
	/// 移動方向ベクトル
	/// </summary>
	Vector2 m_moveDir;

	int m_sizeX;
	int m_sizeY;

	// モーション制御用のカウンタ
	int m_motionCounter;
	// 描画するモーションのフレーム
	int m_motionFrame;

	EnemyType m_enmeyType;

	/// <summary>
	/// プレイヤーの向き
	/// </summary>
	Direction m_direction;;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// HPのポインタ
	/// </summary>
	HitPointYama* m_pHp;

};