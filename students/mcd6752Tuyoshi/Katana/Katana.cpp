#include "Katana.h"

#include <DxLib.h>
#include <iostream>
#include <math.h>
#include <string>
#include <memory>
#include <vector>
#include <array>

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
#include "../Utility/Color.h"
#include "../System/SoundManager.h"

namespace {

	// ファイルパス
	const char* const kGraphPath = ".\\Resource\\image\\Sword.png";

	// 武器名の規定値
	const char* const kInitName = "katana";

	// 与ダメージの規定値
	constexpr float kDamege = 10.0f;

	// 射程の規定値
	constexpr float kRange = 40.0f;

	// 攻撃範囲の規定値
	constexpr float kAttackRange = 2.0f;

	// 武器ナンバーの規定値
	constexpr int kWeaponNumber = 1;

	// クールタイムの規定値
	constexpr int kCoolTime = 150;

	// 出現時間の規定値
	constexpr int kAppearTime = 120;

	// 武器表示座標の回転角度の規定値
	constexpr float kRotateAngle = 0.05f;

	// 武器表示座標が一周するまでの倍率の規定値
	constexpr float kAroundRotateMagnification = 2.0f;

	// 現在攻撃範囲が増減する倍率の規定値
	constexpr double kScaleIncreaseMagnification = 0.1;

	// 画像を回転描画する画面上の中心X座標の規定値
	constexpr int kImageCenterPosX = 8;

	// 画像を回転描画する画面上の中心X座標の規定値
	constexpr int kImageCenterPosY = 49;

	// 刀先端の規定値
	constexpr float kKatanaHeadPos = 50.0f;
}

/////////////////////////////////////////////////////////////////////////////////////////

Katana::Katana():
	m_graphHandle(),
	m_name(kInitName),
	m_damage(kDamege),
	m_range(kRange),
	m_attackRange(kAttackRange),
	m_coolTime(kCoolTime),
	m_weaponNum(kWeaponNumber),
	m_appearTime(kAppearTime),
	m_frameCount(0),
	m_appearCount(m_appearTime),
	m_isAppear(false),
	m_playerPosX(400.0f),
	m_playerPosY(300.0f),
	m_rotateAngle(0),
	m_angle(0),
	m_katanaTerminalPosX(0),
	m_katanaTerminalPosY(0),
	m_scale(0.0)
{

}


Katana::Katana(
	std::string name, 
	float damage,
	float range, 
	float attackRange, 
	int coolTime, 
	int weaponNum, 
	Vector2 playerPos):
	m_graphHandle(),
	m_name(name),
	m_damage(damage),
	m_range(range),
	m_attackRange(attackRange),
	m_coolTime(coolTime),
	m_weaponNum(weaponNum),
	m_appearTime(kAppearTime),
	m_frameCount(0),
	m_appearCount(m_appearTime),
	m_isAppear(false),
	m_playerPosX(playerPos.x),
	m_playerPosY(playerPos.y),
	m_rotateAngle(0),
	m_angle(0),
	m_katanaTerminalPosX(0),
	m_katanaTerminalPosY(0),
	m_scale(0.0)
{

}

void Katana::Init() 
{
	m_graphHandle = LoadGraph(kGraphPath);
}

void Katana::Init(Vector2 playerPos)
{
	m_graphHandle = LoadGraph(kGraphPath);
	m_playerPosX = playerPos.x;
	m_playerPosY = playerPos.y;
}

void Katana::End() 
{
	DeleteGraph(m_graphHandle);
}

void Katana::Update() 
{
	UpdateKatana();

#ifdef _DEBUG
	DebugUpdate();
#endif // _DEBUG
}

void Katana::Draw() 
{
	DrawKatana();
}

Rect Katana::GetCheckRect()
{
	Rect myRect = {
		(m_katanaTerminalPosX)+(cosf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosY)+(sinf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosX),
			m_katanaTerminalPosY
	};

	return myRect;
}

std::vector<Rect> Katana::GetCheckRects()
{
	std::vector<Rect> myRects;

	if (!m_isAppear)return myRects;

	std::array<Rect, 5> bufRect;

	for (int i = 0; i < 5; i++) {

		bufRect[i] = { static_cast<int>(m_katanaTerminalPosX + ((cosf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale - 10),
				static_cast<int>(m_katanaTerminalPosY + ((sinf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale - 10),
				static_cast<int>(m_katanaTerminalPosX + ((cosf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale + 10),
				static_cast<int>(m_katanaTerminalPosY + ((sinf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale + 10)
		};
	}

	myRects.assign(bufRect.begin(), bufRect.end());

	return myRects;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Katana::UpdateKatana()
{
	m_rotateAngle += kRotateAngle;
	if (m_rotateAngle >= (DX_PI_F * kAroundRotateMagnification))
		m_rotateAngle = 0.0f;

	m_angle += (180.0f / DX_PI_F * kRotateAngle);
	if (m_angle >= 360.0f)
		m_angle = 0;

	if (m_coolTime <= m_frameCount) {
		m_isAppear = true;

		if (m_appearCount > 0) {

			if (m_scale < m_attackRange)
				m_scale += kScaleIncreaseMagnification;
			if (m_scale >= m_attackRange)
				m_scale = m_attackRange;
		}

		if (m_coolTime <= 0)return;
		m_appearCount--;
	}
	else
	{
		m_frameCount++;
	}


	if (m_appearCount <= 0) {
		if (m_scale >= 0) {
			m_scale -= kScaleIncreaseMagnification;
		}
		else
		{
			m_scale = 0.0;
			m_isAppear = false;
			m_appearCount = m_appearTime;
			m_frameCount = 0;
		}
	}

}

void Katana::DrawKatana()
{
	static bool isRang = false;

	m_katanaTerminalPosX = m_playerPosX + (cosf(m_rotateAngle) * m_range);
	m_katanaTerminalPosY = m_playerPosY + (sinf(m_rotateAngle) * m_range);

	if (m_isAppear) {

		if (!isRang) {
			SoundManager::GetInstance().PlaySe(Sound::SE::Quick_Magic_Sword_Slice);
			isRang = true;
		}

		// ↓DrawRotaGraph2について
		// https://dxlib.xsrv.jp/function/dxfunc_graph1.html#R3N19
		DrawRotaGraph2(m_katanaTerminalPosX, m_katanaTerminalPosY,
			kImageCenterPosX, kImageCenterPosY, m_scale,
			(DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f),
			m_graphHandle, true, false);

#ifdef _DEBUG
		for (int i = 0; i < 5; i++) {

			DrawBox((m_katanaTerminalPosX)+((cosf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale - 10,
				(m_katanaTerminalPosY)+((sinf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale - 10,
				(m_katanaTerminalPosX)+((cosf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale + 10,
				(m_katanaTerminalPosY)+((sinf(m_rotateAngle) * kKatanaHeadPos) * (0.1f + (0.2f * i))) * m_scale + 10,
				Color::kGreen, false);
		}
#endif // _DEBUG

		if (!(m_coolTime <= 0))return;
		if (m_angle != 0)return;
		SoundManager::GetInstance().PlaySe(Sound::SE::Quick_Magic_Sword_Slice);
	}
	else
	{
		isRang = false;
	}

}

void Katana::DebugUpdate() 
{
	if (CheckHitKey(KEY_INPUT_F) == 1 && m_attackRange > 2.0) {
		m_attackRange -= 0.2;
	}

	if (CheckHitKey(KEY_INPUT_G) == 1 && m_attackRange < 4.0) {
		m_attackRange += 0.2;
	}

}

void Katana::DebugDraw()
{
	//m_katanaTerminalPosX = 400.0f + (cosf(m_rotateAngle) * m_range);
	//m_katanaTerminalPosY = 300.0f + (sinf(m_rotateAngle) * m_range);

	//

	//if (m_isAppear) {

	//	//DrawRotaGraph(x, y, 3.0, (DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f), m_graphHandle, true, false);
	//	DrawRotaGraph2(m_katanaTerminalPosX, m_katanaTerminalPosY,
	//		kImageCenterPosX, kImageCenterPosY, m_scale, 
	//		(DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f),
	//		m_graphHandle, true, false);

	//	DrawBox((m_katanaTerminalPosX) + (cosf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
	//		(m_katanaTerminalPosY)+ (sinf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
	//		(m_katanaTerminalPosX),
	//		m_katanaTerminalPosY,
	//		Color::kCyan, false);
	//}

	printfDx("\nx : %4f // y : %4f\n", m_katanaTerminalPosX, m_katanaTerminalPosY);
	printfDx("m_rotateAngle : %4f\n", m_rotateAngle);
	printfDx("cosf(m_rotateAngle) : %4f\n", cosf(m_rotateAngle));
	printfDx("sinf(m_rotateAngle) : %4f\n", sinf(m_rotateAngle));
	printfDx("m_angle : %4f\n", m_angle);
	printfDx("m_coolTime : %d\n", m_coolTime);
	printfDx("m_appearTime : %d\n", m_appearTime);
	printfDx("m_frameCount : %d\n", m_frameCount);
	printfDx("m_appearCount : %d\n", m_appearCount);
}