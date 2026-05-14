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
	/// 攻撃したかチェック(デバック用)
	/// </summary>
	bool Attack();

	/// <summary>
	/// HPがなくなったかどうかチェック(デバック用)
	/// </summary>
	bool Hp();

	/// <summary>
	/// 死んだかどうかチェック
	/// </summary>
	bool Dead();

	/// <summary>
	/// プレイヤーがダメージを食らった時の関数
	/// </summary>
	/// <param name="value">食らった時のダメージの値</param>
	void Damage(float value);

	/// <summary>
	/// プレイヤーが回復した時の関数
	/// </summary>
	/// <param name="value">回復したときの値</param>
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
	/// プレイヤーの座標を取得
	/// </summary>
	/// <returns>プレイヤーの座標</returns>
	Vector2 GetModelPos() const { return m_currentPos; }

	/// <summary>
	/// 座標を1F前に戻す
	/// </summary>
	void RestorePos();

	/// <summary>
	/// プレイヤーの当たり判定の矩形
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// プレイヤーの向いている方向
	/// </summary>
	/// <returns>向いている方向</returns>
	Direction GetDirection() { return m_direction; }

	/// <summary>
	/// プレイヤーがマップ外に行かないようにするための関数
	/// </summary>
	void Edge();

	/// <summary>
	/// マップにプレイヤーをセットする
	/// </summary>
	/// <param name="m_pmap">Mapをセットする</param>
	void SetMap(Map* m_pmap) { m_map = m_pmap; }

	/// <summary>
	/// プレイヤーのHPの最大値を取得する
	/// </summary>
	/// <returns>プレイヤーの最大HP</returns>
	float GetPlayerHpMax() { return m_hpMax; }

	/// <summary>
	/// プレイヤーのHPを取得する
	/// </summary>
	/// <returns>プレイヤーのHP</returns>
	float GetPlayerHp() { return m_hp; }

private:
	
	/// <summary>
	/// 1F前の座標を更新
	/// </summary>
	void UpdatePrevPos();


private:

	/// <summary>
	/// プレイヤーの画像ハンドル
	/// </summary>
	int m_graphHandle[CHARA_STATUS_NUM][CHARA_MOTION_NUM];


	/// <summary>
	/// プレイヤーの移動速度
	/// </summary>
	float m_playerSpeed;

	/// <summary>
	/// 画像のサイズ
	/// </summary>
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
	/// α版の際の攻撃しているかのフラグ
	/// </summary>
	bool m_isAttackCheck;

	/// <summary>
	/// α版の際の死んだかのフラグ
	/// </summary>
	bool m_isdeadCheck;

	/// <summary>
	/// プレイヤーの現在のHP
	/// </summary>
	float m_hp;

	/// <summary>
	/// プレイヤーのHPの最大値
	/// </summary>
	float m_hpMax;

	/// <summary>
	/// プレイヤーの移動する際の移動する方向
	/// </summary>
	float m_moveX;
	float m_moveY;

	/// <summary>
	/// プレイヤーが移動しているかどうか
	/// </summary>
	bool m_isMove;

	/// <summary>
	/// WeaponManagerのポインタ
	/// </summary>
	WeaponStatus* m_pWeponMgr;

	/// <summary>
	/// PlayerStatusのポインタ
	/// </summary>
	PlayerStatus* m_pPlayerStatus;

	/// <summary>
	/// Mapのポインタ
	/// </summary>
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

