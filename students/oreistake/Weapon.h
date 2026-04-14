#pragma once

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

	int swordPosX;
	int swordPosY;

	Player* m_pPlayer;

};

