#pragma once
#include "../Utility/Game.h"

/// <summary>
/// 前方宣言
/// </summary>
class PlayerMove;
class Map;

class Camera
{

public:

	/// <summary>
	/// Cameraのコンストラクタ
	/// </summary>
	Camera();

	/// <summary>
	/// Cameraのデストラクタ
	/// </summary>
	~Camera() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="playermove"></param>
	/// <param name="map"></param>
	void Init(PlayerMove* playermove,Map* map);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 表示
	/// </summary>
	void Draw();
	
	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// WorldScreenを生成する
	/// </summary>
	void GenerateWorldScreen();

	/// <summary>
	/// WorldScreenを取得する
	/// </summary>
	/// <returns></returns>
	int GetWorldScreen() { return m_worldScreen; }

	/// <summary>
	/// カメラの端の設定
	/// </summary>
	float GetLeft() const {
		return m_targetX - Game::kScreenWidth / 2;
	}
	float GetRight() const {
		return m_targetX + Game::kScreenWidth / 2;
	}
	float GetTop() const {
		return m_targetY - Game::kScreenHeight / 2;
	}
	float GetBottom() const {
		return m_targetY + Game::kScreenHeight / 2;
	}
private:
	
	/// <summary>
	/// ワールドスクリーン
	/// </summary>
	int m_worldScreen;

	/// <summary>
	/// Cameraの注視対象
	/// </summary>
	float m_targetX;
	float m_targetY;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayermove;

	/// <summary>
	/// マップのポインタ
	/// </summary>
	Map* m_pMap;
};

