#pragma once
<<<<<<< HEAD

#include "Literal.h"

class Vector2;

=======
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced
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
<<<<<<< HEAD
	/// プレイヤーの水平移動
	/// </summary>
	void MoveHorizontal();

	/// <summary>
	/// プレイヤーの縦移動
	/// </summary>
	void MoveVertical();

=======
	/// 
	/// </summary>
	void Finalize();
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced
private:

	//=========================================
	// メンバ変数
	//=========================================

	int m_graphHandle;

	int m_idle[8];

<<<<<<< HEAD
	/// <summary>
	/// プレイヤーの移動速度
	/// </summary>
	float m_playerSpeed;

	/// <summary>
	/// プレイヤーのX座標
	/// </summary>
=======
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced
	float m_posX;
	float m_posY;
	int m_sizeX;
	int m_sizeY;

<<<<<<< HEAD
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


	
=======
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced
};

