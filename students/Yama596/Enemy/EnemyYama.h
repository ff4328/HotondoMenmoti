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
	/// ダメージ処理
	/// </summary>
	/// <param name="value"></param>
	void Damege(int value);

	/// <summary>
	/// 死亡処理
	/// </summary>
	bool Dead();

	/// <summary>
	/// バットのレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRectBat();

	/// <summary>
	/// ゴブリンのレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRectGoblin();

	/// <summary>
	/// スケルトンのレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRectSkeleton();

	/// <summary>
	/// マッシュルームのレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRectMush();

	/// <summary>
	/// プレイヤーをセットする
	/// </summary>
	void SetPlayer(PlayerMove* pPlayer);

private:

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

	/// <summary>
	/// バットを描画する
	/// </summary>
	void BatDraw();

	/// <summary>
	/// ゴブリンを描画する
	/// </summary>
	void GoblinDraw();

	/// <summary>
	/// スケルトンを描画する
	/// </summary>
	void SkeletonDraw();

	/// <summary>
	/// マッシュルームを描画する
	/// </summary>
	void MushDraw();

private:

	int m_graphHandle[CHARA_MOTION_NUM_Yama][CHARA_MOB_NUM_Yama];

	float m_enemySpeed;

	/// <summary>
	/// バットの座標
	/// </summary>
	Vector2 m_BatCurrentPos;

	/// <summary>
	/// ゴブリンの座標
	/// </summary>
	Vector2 m_GoblinCurrentPos;

	/// <summary>
	/// スケルトンの座標
	/// </summary>
	Vector2 m_SkeletonCurrentPos;

	/// <summary>
	/// マッシュルームの座標
	/// </summary>
	Vector2 m_MushCurrentPos;

	/// <summary>
	/// 移動方向ベクトル
	/// </summary>
	Vector2 m_moveDir;

	int m_sizeX;
	int m_sizeY;

	/// <summary>
	/// モーション制御用のカウンタ
	/// </summary>
	int m_motionCounter;
	
	/// <summary>
	/// 描画するモーションのフレーム
	/// </summary>
	int m_motionFrame;

	/// <summary>
	/// 敵列挙体のテーブル
	/// </summary>
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