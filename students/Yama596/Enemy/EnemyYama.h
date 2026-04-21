#pragma once

#include "../students/bamboojr36/Vector2.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/FIREBAR/EnemyStatus.h"

class Map;

/// <summary>
/// 敵のタイプ
/// </summary>
enum EnemyTypeYama {

	ENEMY_TYPE_BAT_YAMA,
	ENEMY_TYPE_GOBLIN_YAMA,
	ENEMY_TYPE_SKELETON_YAMA,
	ENEMY_TYPE_MUSH_YAMA,
	ENEMY_TYPE_MAX_YAMA

};

/// <summary>
/// 敵の1モーションの画像の数
/// </summary>
const int ENEMY_MOTION_NUM_YAMA = 8;

/// <summary>
/// 敵の最大数
/// </summary>
const int ENEMY_NUM_YAMA = 64;

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
	/// 更新処理を行う
	/// </summary>
	void Update();

	/// <summary>
	/// 表示を行う
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
	/// プレイヤーのポインタをセットする
	/// </summary>
	void SetPlayer(PlayerMove* pPlayer) { m_pPlayer = pPlayer; };

	/// <summary>
	/// マップのポインタをセットする
	/// </summary>
	/// <param name="_map"></param>
	void SetMap(Map* map) { m_pMap = map; }

	/// <summary>
	/// 敵のポインタをセットする
	/// </summary>
	/// <param name="enemytype"></param>
	void SetEnemyType(EnemyTypeYama enemytype) { m_enmeyType = enemytype; }

	/// <summary>
	/// 画像をセットする
	/// </summary>
	/// <param name="enemyMgr"></param>
	void SetGraphHandle(int enemyMgr[ENEMY_TYPE_MAX_YAMA][ENEMY_MOTION_NUM_YAMA]);

	/// <summary>
	/// 敵のパラメーターをセットする
	/// </summary>
	/// <param name="currentPos"></param>
	/// <param name="moveDir"></param>
	void SetParam(Vector2 currentPos, Vector2 moveDir);

	/// <summary>
	/// 初期座標をセットする
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(const Vector2& pos) { m_currentPos = pos; }

	/// <summary>
	/// ステータスをセットする
	/// </summary>
	/// <param name="status"></param>
	void SetEnemyStatus(EnemyStatus* status) { m_pEnemyStatus = status; }

private:

	/// <summary>
	/// アニメーションの初期設定行う
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// ステータスの初期設定を行う
	/// </summary>
	void InitStatus();

	/// <summary>
	/// 移動更新処理行う
	/// </summary>
	void UpdateMove();

	/// <summary>
	/// 敵を描画する
	/// </summary>
	void DrawEnemy();

private:

	/// <summary>
	/// 敵のグラフィックハンドル
	/// </summary>
	int m_graphHandle[ENEMY_TYPE_MAX_YAMA][ENEMY_MOTION_NUM_YAMA];

	/// <summary>
	/// 敵のスピード
	/// </summary>
	float m_enemySpeed;

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 m_currentPos;

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
	/// 移動方向ベクトル
	/// </summary>
	Vector2 m_moveDir;

	/// <summary>
	/// バットの移動方向ベクトル
	/// </summary>
	Vector2 m_batMoveDir;

	/// <summary>
	/// ゴブリンの移動方向ベクトル
	/// </summary>
	Vector2 m_goblinMoveDir;

	/// <summary>
	/// スケルトンの移動方向ベクトル
	/// </summary>
	Vector2 m_skeletonMoveDir;

	/// <summary>
	/// マッシュの移動方向ベクトル
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

	float m_hp;
	float m_maxHp;
	float m_attack;
	float m_speed;

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

	/// <summary>
	/// マップのポインタ
	/// </summary>
	Map* m_pMap;
};