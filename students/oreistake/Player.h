#pragma once

#include "Literal.h"

class Vector2;

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

	/// <summary>

	/// プレイヤーの水平移動
	/// </summary>
	void MoveHorizontal();

	/// <summary>
	/// プレイヤーの縦移動
	/// </summary>
	void MoveVertical();

	/// <summary>
	/// 
	/// </summary>
	void Finalize();
 
private:

	//======
	// メンバ変数
	//======

	int m_graphHandle[CHARA_MOTION_NUM][CHARA_STATUS_NUM];


	/// <summary>
	/// プレイヤーの移動速度
	/// </summary>
	float m_playerSpeed;

	/// <summary>
	/// プレイヤーのX座標
	/// </summary>

 
	float m_posX;
	float m_posY;
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
	/// statusの参照
	///</summary>
	Status m_status;

	/// <summary>
	/// Vector2のポインタ
	/// </summary>
	Vector2* m_pVector2;


	

 
};

