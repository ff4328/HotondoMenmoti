#pragma once
#include "../students/Yama596/Enemy/EnemyYama.h"
#include "../students/FIREBAR/EnemyStatus.h"

#include <array>

class Map;
class PlayerMove;
class EnemyYama;

class EnemyManagerYama
{

public:

	EnemyManagerYama();

	~EnemyManagerYama() = default;

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
	/// 表示処理を行う
	/// </summary>
	void Draw();

	/// <summary>
	/// 敵を生成する
	/// </summary>
	bool Resister(PlayerMove* pPlayer);

	/// <summary>
	/// ゲームカウントを使って敵を生成
	/// </summary>
	void ResisterMapPoint();

	/// <summary>
	/// マップのポインタをセットする
	/// </summary>
	/// <param name="map"></param>
	void SetMap(Map* map) { m_pMap = map; }

private:

	/// <summary>
	/// アニメーションの初期設定
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// 矩形と矩形が当たっているか調べる
	/// </summary>
	/// <param name="rect"></param>
	void CheckHitToRect(Rect rect);

	EnemyTypeYama GetSpawnType();

private:

	/// <summary>
	/// 敵のグラフィックハンドル
	/// </summary>
	int m_graphHandle[ENEMY_TYPE_MAX_YAMA][ENEMY_MOTION_NUM_YAMA];

	/// <summary>
	/// 敵構造体のテーブル
	/// </summary>
	std::array<EnemyYama*, ENEMY_NUM_YAMA> m_EnemyYamas;

	/// <summary>
	/// 時間カウント
	/// </summary>
	unsigned int m_gameCount;

	/// <summary>
	/// バットの数
	/// </summary>
	int m_batCount;

	/// <summary>
	/// ゴブリンの数
	/// </summary>
	int m_goblinCount;

	/// <summary>
	/// スケルトンの数
	/// </summary>
	int m_skeletonCount;

	/// <summary>
	/// マッシュルームの数
	/// </summary>
	int m_mushCount;

	/// <summary>
	/// 配置情報のカウンタ
	/// </summary>
	int m_mapPoint;

	/// <summary>
	/// 敵のテーブル
	/// </summary>
	EnemyYama* enemyTable[ENEMY_NUM_YAMA];

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// マップのポインタ
	/// </summary>
	Map* m_pMap;

	/// <summary>
	/// 敵ステータス
	/// </summary>
	EnemyStatus m_enemyStatus;

};

