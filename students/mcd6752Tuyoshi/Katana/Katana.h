#pragma once

#include <string>
#include <memory>

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

/// <summary>
/// 刀(武器)のクラス
/// </summary>
class Katana
{
public:

	Katana();

	Katana(
		std::string name,
		float damage,
		float range,
		float attackRange,
		int coolTime,
		int weaponNum,
		Vector2 playerPos);

	~Katana() = default;

	void Init();

	void Init(Vector2 playerPos);

	void End();

	void Update();

	void Draw();

	const std::string GetWeaponName()const { return m_name; }

	const int& GetWeaponNum()const { return m_weaponNum; }

	/// <summary>
	/// レクト取得
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// 当たり判定取得
	/// </summary>
	/// <returns></returns>
	Collision* GetCollision() const { return m_pCollision.get(); }

	void SetDamage(float damage) { m_damage = damage; }

	void SetAttackRange(float attackRange) { m_attackRange = attackRange; }

	void SetCoolTime(int coolTime) { m_coolTime = coolTime; }

	void SetPlayerPos(Vector2 playerPos) { m_playerPosX = playerPos.x; m_playerPosY = playerPos.y; }

private:

	void UpdateKatana();

	void DrawKatana();

	void DebugUpdate();

	void DebugDraw();

private:

	int m_graphHandle;

	std::string m_name;

	float m_damage;

	float m_range;

	float m_attackRange;

	int m_coolTime;

	int m_weaponNum;

	int m_appearTime;

	int m_frameCount;

	int m_appearCount;

	bool m_isAppear;

	float m_playerPosX;

	float m_playerPosY;

	float m_rotateAngle;

	float m_angle;

	float m_katanaTerminalPosX;

	float m_katanaTerminalPosY;

	double m_scale;

	/// <summary>
	/// 当たり判定ユニークポインタ
	/// </summary>
	std::unique_ptr<Collision>m_pCollision;

};

