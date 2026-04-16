#pragma once

#include"../students/bamboojr36/Vector2.h"

class Player;

class Weapon
{
public:


	Weapon();


	~Weapon() = default;

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

	void Sword();

	void Bow();

	void Ax();

	void Magic();

private:

	Vector2 m_currentPos;

	float m_angle;
	float m_radius;

	Player* m_pPlayer;

};

