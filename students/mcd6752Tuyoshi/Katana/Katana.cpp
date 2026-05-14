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
#include "../Utility/Input.h"
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

	// 刀の当たり判定の大きさの倍率
	constexpr double kKatanaRectScale = 0.4;

	// 刀の当たり判定の座標の補正値
	constexpr float kKatanaCoordinateMargin = 0.1f;

	// 刀の当たり判定の座標の倍率
	constexpr float kKatanaCoordinateMagnification = 0.4f;

	// 刀の当たり判定の大きさの補正値
	constexpr int kKatanaRectMargin = 10;
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
	// 画像の読み込み
	m_graphHandle = LoadGraph(kGraphPath);
}

void Katana::Init(Vector2 playerPos)
{
	// 画像の読み込み
	m_graphHandle = LoadGraph(kGraphPath);

	// プレイヤー座標の設定
	m_playerPosX = playerPos.x;
	m_playerPosY = playerPos.y;
}

void Katana::End() 
{
	// 読み込んだ画像の破棄
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
#ifdef _DEBUG
	DebugDraw();
#endif // _DEBUG
}

std::vector<Rect> Katana::GetCheckRects() const
{
	// 戻り値で返すための変数を作成
	std::vector<Rect> myRects;

	// 武器の描画フラグがfalseなら早期リターン
	if (!m_isAppear)return myRects;

	// m_scaleを0.4で割った数だけRectを作る
	for (int i = 0; i < static_cast<int>(m_scale / kKatanaRectScale); i++) {

		// 刀の先端座標から(0.1f＋(0.4f × i))倍の座標を基準に矩形を作る
		myRects.push_back({ static_cast<int>(m_katanaTerminalPosX + ((cosf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) - kKatanaRectMargin),
				static_cast<int>(m_katanaTerminalPosY + ((sinf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) - kKatanaRectMargin),
				static_cast<int>(m_katanaTerminalPosX + ((cosf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) + kKatanaRectMargin),
				static_cast<int>(m_katanaTerminalPosY + ((sinf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) + kKatanaRectMargin)
			});
	}

	return myRects;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Katana::UpdateKatana()
{
	// 武器が表示される座標の回転角度を0.05fずつ加算し、武器が一周したら0にする
	m_rotateAngle += kRotateAngle;
	if (m_rotateAngle >= (DX_PI_F * kAroundRotateMagnification))
		m_rotateAngle = 0.0f;

	// 武器自体の角度をラジアン角に変換した0.05fずつ加算し、武器が一周したら0にする
	m_angle += (180.0f / DX_PI_F * kRotateAngle);
	if (m_angle >= 360.0f)
		m_angle = 0;

	// 計測したフレーム数が現在のクールタイム以上なら
	if (m_coolTime <= m_frameCount) {
		m_isAppear = true;	// 武器描画フラグをtrueに

		// 残り出現時間が0より上なら
		if (m_appearCount > 0) {

			// 武器のサイズを段々大きくして攻撃範囲以上になったら止める
			if (m_scale < m_attackRange)
				m_scale += kScaleIncreaseMagnification;
			if (m_scale >= m_attackRange)
				m_scale = m_attackRange;
		}

		if (!(m_coolTime <= 0))	// クールタイムが0以下でなければ
			m_appearCount--;	// 残り出現時間をカウントダウン
	}
	else
	{
		// 計測したフレーム数が現在のクールタイム未満なら
		// フレーム数をカウントアップ
		m_frameCount++;
	}

	// 残り出現時間が0以下なら
	if (m_appearCount <= 0) {

		// かつ、武器のサイズが0以上ならサイズを段々小さくする
		if (m_scale >= 0) {
			m_scale -= kScaleIncreaseMagnification;
		}
		else
		{
			// 0未満なら武器のサイズを0に、武器描画フラグをfalseに
			// 残り出現時間を最大に、クールタイム計測用フレーム数を0にする
			m_scale = 0.0;
			m_isAppear = false;
			m_appearCount = m_appearTime;
			m_frameCount = 0;
		}
	}

}

void Katana::DrawKatana()
{
	// 出現時に音を再生するためのローカル変数
	static bool isRang = false;

	// 武器を回転描画する画面上の中心座標を更新
	m_katanaTerminalPosX = m_playerPosX + (cosf(m_rotateAngle) * m_range);
	m_katanaTerminalPosY = m_playerPosY + (sinf(m_rotateAngle) * m_range);

	// 武器出現フラグがtrueなら
	if (m_isAppear) {

		// かつ、まだ出現音が再生されていなければ
		if (!isRang) {
			// 音を再生しフラグを立てる
			SoundManager::GetInstance().PlaySe(Sound::SE::Quick_Magic_Sword_Slice);
			isRang = true;
		}

		// 刀の描画
		// ↓DrawRotaGraph2について
		// https://dxlib.xsrv.jp/function/dxfunc_graph1.html#R3N19
		DrawRotaGraph2(m_katanaTerminalPosX, m_katanaTerminalPosY,
			kImageCenterPosX, kImageCenterPosY, m_scale,
			(DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f),
			m_graphHandle, true, false);

		// ソリューション構成がデバッグなら当たり判定の矩形を表示する
#ifdef _DEBUG
		for (int i = 0; i < static_cast<int>(m_scale/kKatanaRectScale); i++) {

			DrawBox((m_katanaTerminalPosX)+((cosf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) -kKatanaRectMargin,
				(m_katanaTerminalPosY)+((sinf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) - kKatanaRectMargin,
				(m_katanaTerminalPosX)+((cosf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) + kKatanaRectMargin,
				(m_katanaTerminalPosY)+((sinf(m_rotateAngle) * kKatanaHeadPos) * (kKatanaCoordinateMargin + (kKatanaCoordinateMagnification * i))) + (m_attackRange * kKatanaRectScale) + kKatanaRectMargin,
				Color::kGreen, false);
		}
#endif // _DEBUG

		// クールタイムが0以下なら、刀が一周した時に音を再生
		if (!(m_coolTime <= 0))return;
		if (m_angle != 0)return;
		SoundManager::GetInstance().PlaySe(Sound::SE::Quick_Magic_Sword_Slice);
	}
	else
	{	// 武器出現フラグがfalseなら音再生フラグをfalseに
		isRang = false;
	}

}

// ソリューション構成がデバッグならZキーとXキーで刀のサイズの大小を増減できる
// あといろんな変数を見れる
#ifdef _DEBUG

void Katana::DebugUpdate() 
{
	if (Input::IsPressed(PAD_INPUT_1) == 1 && m_attackRange > kAttackRange) {
		m_attackRange -= kKatanaRectScale;
	}

	if (Input::IsPressed(PAD_INPUT_2) == 1 && m_attackRange < 4.0) {
		m_attackRange += kKatanaRectScale;
	}

}


void Katana::DebugDraw()
{
	printfDx("\nx : %4f // y : %4f\n", m_katanaTerminalPosX, m_katanaTerminalPosY);
	printfDx("m_rotateAngle : %4f\n", m_rotateAngle);
	printfDx("cosf(m_rotateAngle) : %4f\n", cosf(m_rotateAngle));
	printfDx("sinf(m_rotateAngle) : %4f\n", sinf(m_rotateAngle));
	printfDx("m_angle : %4f\n", m_angle);
	printfDx("m_coolTime : %d\n", m_coolTime);
	printfDx("m_appearTime : %d\n", m_appearTime);
	printfDx("m_frameCount : %d\n", m_frameCount);
	printfDx("m_appearCount : %d\n", m_appearCount);
	printfDx("m_attackRenge : %f\n", m_attackRange);
	printfDx("m_attackRenge / 0.4 : %f\n", m_attackRange/kKatanaRectScale);
	printfDx("m_scale : %lf\n", m_scale);
}
#endif // _DEBUG