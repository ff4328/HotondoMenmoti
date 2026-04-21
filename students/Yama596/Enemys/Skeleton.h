#pragma once
#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

class PlayerMove;
class HitPointYama;

const int kMotionNum = 8;

class Skeleton
{

	Skeleton();

	~Skeleton() = default;

	/// <summary>
	/// 初期設定を行う
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
	/// ダメージ処理を行う
	/// </summary>
	/// <param name="value"></param>
	void Damege(int value);

	/// <summary>
	/// 死亡処理を行う
	/// </summary>
	bool Dead();

	/// <summary>
	/// バットのレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// プレイヤーのポインタをセットする
	/// </summary>
	void SetPlayer(PlayerMove* pPlayer) { m_pPlayer = pPlayer; };

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
	int m_graphHandle[kMotionNum];

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 m_currentPos;

	/// <summary>
	/// 移動方向ベクトル
	/// </summary>
	Vector2 m_moveDir;

	/// <summary>
	/// モーション制御用のカウンタ
	/// </summary>
	int m_motionCounter;

	/// <summary>
	/// 描画するモーションのフレーム
	/// </summary>
	int m_motionFrame;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// 体力のポインタ
	/// </summary>
	HitPointYama* m_pHp;

};

