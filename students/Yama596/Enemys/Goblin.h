#pragma once
#include "../students/Yama596/Enemys/EnemyBase.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

class PlayerMove;
class HitPointYama;

const int kGoblinMotionNum = 8;

class Goblin : public EnemyBase
{

public:

	Goblin();

	~Goblin() = default;

	/// <summary>
	/// 初期設定を行う
	/// </summary>
	void Init() override;

	/// <summary>
	/// 後処理を行う
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理を行う
	/// </summary>
	EnemyBase* Update() override;

	/// <summary>
	/// 表示を行う
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ダメージ処理を行う
	/// </summary>
	/// <param name="value"></param>
	void Damege(int value) override;

	/// <summary>
	/// 死亡処理を行う
	/// </summary>
	bool Dead() override;

	/// <summary>
	/// ゴブリンのレクト
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect() override;

	/// <summary>
	/// プレイヤーのポインタをセットする
	/// </summary>
	void SetPlayer(PlayerMove* pPlayer) override { m_pPlayer = pPlayer; }

	/// <summary>
	/// 初期座標をセットする
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(const Vector2& pos) override { m_currentPos = pos; }

	/// <summary>
	/// 画像をセットする
	/// </summary>
	/// <param name="graphHandle"></param>
	void SetGraphHandle(int* graphHandle) override;

	/// <summary>
	/// 移動前の座標を登録する
	/// </summary>
	void RecordPosition() override;

	/// <summary>
	/// 座標を移動前に戻す
	/// </summary>
	void RevertPosition() override;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Vector2 GetPos() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="v"></param>
	void AddPos(const Vector2& vector) override;

private:

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
	int m_graphHandle[kGoblinMotionNum];

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 m_currentPos;

	/// <summary>
	/// 移動前の座標
	/// </summary>
	Vector2 m_prevPos;

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

