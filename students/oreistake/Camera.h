#pragma once


class PlayerMove;

class Camera
{

public:

	//=========================================
	// メンバ関数
	//=========================================

	Camera();
	~Camera() = default;

	void Init(PlayerMove* playermove);
	void Update();
	void Draw();
	void Finalize();

	void DebugShow();

	// worldScreenを生成する
	void GenerateWorldScreen();

	// worldScreenを取得する関数
	int GetWorldScreen() { return m_worldScreen; }


private:
	//=========================================
	// メンバ変数
	//=========================================

	// ワールドスクリーン
	int m_worldScreen;

	// カメラの注視点の座標
	float m_targetX;
	float m_targetY;

	// 構造体のポインタ
	PlayerMove* m_pPlayermove;

};

