#pragma once
#include "../Utility/Game.h"


class PlayerMove;
class Map;

class Camera
{

public:

	//=========================================
	// メンバ関数
	//=========================================

	Camera();
	~Camera() = default;

	void Init(PlayerMove* playermove,Map* map);
	void Update();
	void Draw();
	void End();

	// worldScreenを生成する
	void GenerateWorldScreen();

	// worldScreenを取得する関数
	int GetWorldScreen() { return m_worldScreen; }

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
	
	// ワールドスクリーン
	int m_worldScreen;

	float m_targetX;
	float m_targetY;

	// カメラの注視点の座標

	// 構造体のポインタ
	PlayerMove* m_pPlayermove;

	Map* m_pMap;
};

