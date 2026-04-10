#pragma once

#include "Literal.h"


class Player
{

	

public:

	/// <summary>
	/// Playerのコンストラクタ
	/// </summary>
	Player() ;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

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

private:

	//=========================================
	// メンバ変数
	//=========================================


	/// <summary>
	/// プレイヤーの画像ハンドル
	/// </summary>
	int m_graphHandle[CHARA_STATUS_NUM ][CHARA_MOTION_NUM];

	/// <summary>
	/// プレイヤーのX座標
	/// </summary>
	float m_posX;

	/// <summary>
	/// プレイヤーのY座標
	/// </summary>
	float m_posY;

	/// <summary>
	/// 画像の横幅
	/// </summary>
	int m_sizeX;

	/// <summary>
	/// 画像の縦幅
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

	/*/// <summary>
	/// Literal.hのポインタ
	/// </summary>
	Literal* m_pLiteral;*/

};

