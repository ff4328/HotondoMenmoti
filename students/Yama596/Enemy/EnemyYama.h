#pragma once

#include "../students/bamboojr36/Vector2.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/FIREBAR/EnemyStatus.h"

/// <summary>
/// 敵のタイプ
/// </summary>
enum EnemyTypeYama {

	ENEMY_TYPE_BAT_Yama,
	ENEMY_TYPE_GOBLIN_Yama,
	ENEMY_TYPE_SKELETON_Yama,
	ENEMY_TYPE_MUSH_Yama,
	ENEMY_TYPE_MAX_Yama
};

/// <summary>
/// 敵の1モーションの画像の数
/// </summary>
const int ENEMY_MOTION_NUM_Yama = 8;

class EnemyYama
{

public:

	EnemyYama();

	EnemyYama(EnemyStatus* enemystatus);

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
	void SetEnemyType(EnemyTypeYama enamytype) { m_enmeyType = enamytype; }

	/// <summary>
	/// グラフィックハンドルの初期設定
	/// </summary>
	/// <param name="enemyMgr"></param>
	void SetGraphHandle(int enemyMgr[ENEMY_MOTION_NUM_Yama][ENEMY_TYPE_MAX_Yama]);

	/// <summary>
	/// 敵を描画する
	/// </summary>
	void EnemyDraw();

private:

	/// <summary>
	/// 敵のハンドル
	/// </summary>
	int m_graphHandle[ENEMY_TYPE_MAX_Yama][ENEMY_MOTION_NUM_Yama];

	/// <summary>
	/// 敵のスピード
	/// </summary>
	float m_enemySpeed;

	/// <summary>
	/// バットの座標
	/// </summary>
	Vector2 m_batCurrentPos;

	/// <summary>
	/// ゴブリンの座標
	/// </summary>
	Vector2 m_goblinCurrentPos;

	/// <summary>
	/// スケルトンの座標
	/// </summary>
	Vector2 m_skeletonCurrentPos;

	/// <summary>
	/// マッシュルームの座標
	/// </summary>
	Vector2 m_mushCurrentPos;

	/// <summary>
	/// バット移動方向ベクトル
	/// </summary>
	Vector2 m_batMoveDir;

	/// <summary>
	/// ゴブリン移動方向ベクトル
	/// </summary>
	Vector2 m_goblinMoveDir;

	/// <summary>
	/// スケルトン移動方向ベクトル
	/// </summary>
	Vector2 m_skeletonMoveDir;

	/// <summary>
	/// マッシュ移動方向ベクトル
	/// </summary>
	Vector2 m_mushMoveDir;

	/// <summary>
	/// サイズX
	/// </summary>
	int m_sizeX;

	/// <summary>
	/// サイズY
	/// </summary>
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
	EnemyTypeYama m_enmeyType;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// エネミーステータスのポインタ
	/// </summary>
	EnemyStatus* m_pEnemyStatus;

	/// <summary>
	/// HPのポインタ
	/// </summary>
	HitPointYama* m_pHp;

};