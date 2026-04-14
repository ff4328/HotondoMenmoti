#pragma once

#include "Literal.h"
#include "../students/bamboojr36/Vector2.h"


class Enemy
{

public:

	Enemy();

	~Enemy() = default;

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

private:

	/// <summary>
	/// 1F前の座標を更新
	/// </summary>
	void UpdatePrevPos();

private:

	int m_graphHandle[CHARA_MOTION_NUM][CHARA_MOB_NUM];

	float m_enemySpeed;

	/// <summary>
	/// プレイヤーモデルの座標
	/// </summary>
	Vector2 m_currentPos;

	/// <summary>
	/// プレイヤーの1F前の座標
	/// </summary>
	Vector2 m_prevPos;

	int m_sizeX;
	int m_sizeY;

	// モーション制御用のカウンタ
	int m_motionCounter;
	// 描画するモーションのフレーム
	int m_motionFrame;

	EnemyType m_enmeyType;

};

