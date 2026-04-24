#pragma once
#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

class PlayerMove;

class EnemyBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// メンバ変数の初期設定
	/// </summary>
	EnemyBase();

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~EnemyBase() {}

	/// <summary>
	/// 初期設定
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>自身のポインタを返す</returns>
	virtual EnemyBase* Update() { return this; }

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ダメージ処理を行う
	/// </summary>
	/// <param name="value"></param>
	virtual void Damege(int value) = 0;

	/// <summary>
	/// 死亡処理を行う
	/// </summary>
	virtual bool Dead() = 0;

	/// <summary>
	/// バットのレクト
	/// </summary>
	/// <returns></returns>
	virtual Rect GetCheckRect() = 0;

	/// <summary>
	/// プレイヤーのポインタをセットする
	/// </summary>
	virtual void SetPlayer(PlayerMove* pPlayer) = 0;

	/// <summary>
	/// 初期座標をセットする
	/// </summary>
	/// <param name="pos"></param>
	virtual void SetPos(const Vector2& pos) = 0;

	/// <summary>
	/// 画像をセットする
	/// </summary>
	/// <param name="graphHandle"></param>
	virtual void SetGraphHandle(int* graphHandle) = 0;

	/// <summary>
	/// 敵の座標を返す処理を行う
	/// </summary>
	/// <returns></returns>
	virtual Vector2 GetPos() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="v"></param>
	virtual void AddPos(const Vector2& vector) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool IsCounted() const = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="flag"></param>
	virtual void SetCounted(bool flag) = 0;

private:

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

protected:

	/// <summary>
	/// 死亡したかどうか
	/// </summary>
	bool m_deadCount = false;

	enum Direction {

		DIRECTION_RIGHT = 0,
		DIRECTION_LEFT = 1,

	};

};

