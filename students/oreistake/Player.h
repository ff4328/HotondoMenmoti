#pragma once

#include "Literal.h"
#include"../students/bamboojr36/Vector2.h"
#include"../students/bamboojr36/Collision.h"
#include"../students/FIREBAR/WeaponManager.h"
#include"../students/FIREBAR/PlayerStatus.h"
#include"../students/Yama596/Enemy/EnemyYama.h"
#include"../mcd6752Tuyoshi/Map/Map.h"

//class PlayerStatus;
class Vector2;
class WeaponStatus;
struct Rect;
struct Player;
class EnemyYama;
class PlayerMove
{

public:

	/// <summary>
	/// Playerのコンストラクタ
	/// </summary>
	PlayerMove() ;

	PlayerMove(PlayerStatus* playerstatus) ;

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

	void Update(PlayerStatus* playerstatus);

	/// <summary>
	/// 攻撃したか
	/// </summary>
	/// <returns></returns>
	bool Attack();

	bool Hp();

	bool Dead();
	
	void Damage(float value);

	void Heal(int value);

	/// <summary>
	/// 表示
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの水平移動
	/// </summary>
	void Move();

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

	Rect GetCheckRect();

	Direction GetDirection() { return m_direction; }

	void Edge();

	void SetMap(Map* m_pmap) { m_map = m_pmap; }

	float GetPlayerHpMax() { return m_hpMax; }
	float GetPlayerHp() { return m_hp; }

private:
	
	/// <summary>
	/// 1F前の座標を更新
	/// </summary>
	void UpdatePrevPos();


private:

	//======
	// メンバ変数
	//======

	int m_graphHandle[CHARA_STATUS_NUM][CHARA_MOTION_NUM];


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


	bool m_isAttackCheck;

	bool m_isdeadCheck;


	float m_hp;


	float m_hpMax;


	float m_angle;
	float m_radius;

	bool m_isRun;

	WeaponStatus* m_pWeponMgr;

	PlayerStatus* m_pPlayerStatus;

	EnemyYama* m_pEnemyYama;

	Map* m_map;
	/// <summary>
	/// statusの参照
	///</summary>
	Status m_status;

	/// <summary>
	/// プレイヤーモデルの座標
	/// </summary>ww
	Vector2 m_currentPos;

	/// <summary>
	/// プレイヤーの1F前の座標
	/// </summary>
	Vector2 m_prevPos;
 
	/// <summary>
	/// 向き
	/// </summary>
	Direction m_direction;

};

