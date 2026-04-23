#pragma once
#include "../students/oreistake/Player.h"
#include "../students/oreistake/Camera.h"
#include "../students/bamboojr36/Vector2.h"

#include <vector>

class EnemyBase;
class PlayerMove;
class Camera;

class EnemyManagerBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// メンバ変数の初期設定
	/// </summary>
	EnemyManagerBase();

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~EnemyManagerBase() {}

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
	virtual EnemyManagerBase* Update() { return this; }

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/*
	/// <summary>
	/// 生成処理を行う
	/// </summary>
	virtual void Spawn(const Vector2& pos) = 0;

	/// <summary>
	/// ランダムな位置に生成する
	/// </summary>
	/// <returns></returns>
	virtual Vector2 GetRandomSpawnPos() = 0;
	*/

	/// <summary>
	///	プレイヤーを渡す処理を行う
	/// </summary>
	/// <param name="player"></param>
	virtual void SetPlayer(PlayerMove* player) = 0;

	/// <summary>
	/// カメラを渡す処理を行う
	/// </summary>
	/// <param name="camera"></param>
	virtual void SetCamera(Camera* camera) = 0;

	/// <summary>
	/// 生成する敵を決める
	/// </summary>
	/// <returns></returns>
	virtual EnemyBase* CreateEnemy() = 0;

	/// <summary>
	/// 敵を取得する
	/// </summary>
	/// <param name="outEnemies"></param>
	virtual void GetEnemies(std::vector<EnemyBase*>& outEnemies) = 0;

private:

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// カメラのポインタ
	/// </summary>
	Camera* m_pCamera;

protected:

	/// <summary>
	/// 敵ベース構造体のテーブル
	/// 増減させるから可変長配列で作った
	/// </summary>
	std::vector<EnemyBase*> m_enemies;

};

