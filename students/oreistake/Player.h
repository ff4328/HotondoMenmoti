#pragma once

#include "Literal.h"
#include"../students/bamboojr36/Vector2.h"
#include"../students/FIREBAR/WeaponManager.h"
#include"../students/FIREBAR/PlayerStatus.h"


class PlayerStatus;
class Vector2;
class WeaponManager;
class PlayerMove
{

public:

	/// <summary>
	/// Playerのコンストラクタ
	/// </summary>
	PlayerMove() ;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerMove() = default;

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
 
	/// <summary>
	/// プレイヤーの座標を取得
	/// </summary>
	/// <returns>プレイヤーの座標</returns>
	Vector2 GetModelPos() const { return m_currentPos; }

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

 
	/*float m_posX;
	float m_posY;*/
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


	WeaponManager* m_pWeponMgr;

	PlayerStatus* m_pPlayerStatus;

	/// <summary>
	/// statusの参照
	///</summary>
	Status m_status;

	/// <summary>
	/// プレイヤーモデルの座標
	/// </summary>
	Vector2 m_currentPos;
	
	/// <summary>
	/// プレイヤーの1F前の座標
	/// </summary>
	Vector2 m_prevPos;
 
	Rect GetCheckRect();

};

