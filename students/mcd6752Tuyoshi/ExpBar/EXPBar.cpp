#include "EXPBar.h"

#include <DxLib.h>

#include "../Utility/Color.h"
#include "../Utility/Game.h"
#ifdef _DEBUG
#include "../Utility/Input.h"
#endif // _DEBUG



namespace {

	// 経験値バーの幅の補正値
	constexpr int kBarWidthMargin = 5;
	// 経験値バーの高さの補正値
	constexpr int kBarHeightMargin = 5;
	// 経験値バーの高さの倍率
	constexpr float kBarHeightMagnification = 0.04f;

	// 要求経験値の初期値
	constexpr int kInitRequiredExp = 100;
	// レベルの初期値
	constexpr int kInitCurrentLevel = 0;
	// レベル上限
	constexpr int kMaxLevel = 99;

	// 要求経験値増加倍率の規定値
	constexpr float kRequiredExpIncreaseMagnification = 1.15f;

	// レベル表示のX座標の補正値
	constexpr int kLevelPosXMargin = 100;
	// レベル表示のY座標の倍率
	constexpr float kLevelPosYMarginMagnification = 0.4f;
}

//////////////////////////////////////////////////////////////////////////////

EXPBar::EXPBar() :
	m_gaugeWidth(kBarWidthMargin),
	m_requiredExp(kInitRequiredExp),
	m_expIncreaseRate(-1),
	m_currentLevel(kInitCurrentLevel),
	m_beforeLevel(m_currentLevel),
	m_expEarnCount(0),
	m_pPStatus()
{

}

EXPBar::EXPBar(PlayerStatus* playerStatus):
	m_gaugeWidth(kBarWidthMargin),
	m_requiredExp(kInitRequiredExp),
	m_expIncreaseRate(-1),
	m_currentLevel(kInitCurrentLevel),
	m_beforeLevel(m_currentLevel),
	m_expEarnCount(0),
	m_pPStatus(playerStatus)
{

}

void EXPBar::Init()
{
	SetIncreaseRate();
}

void EXPBar::Init(const int& req)
{
	SetRequiredEXP(req);
	SetIncreaseRate();
}

void EXPBar::End()
{

}

#ifdef _DEBUG
void EXPBar::DebugUpdate()
{
	// レベル上限を99に設定
	if (m_currentLevel >= kMaxLevel)return;


	DebugIncreaseEXP();

	//IncreaseEXP(true, 10);
	IncreaseLevel();
}
#endif // _DEBUG

void EXPBar::Update(const bool& isEarn, const int& exp)
{
	// レベル上限を99に設定
	if (m_currentLevel >= kMaxLevel)return;

	IncreaseEXP(isEarn, exp);
	IncreaseLevel();
}

void EXPBar::Update(const bool& isEarn, const int& exp,
	const float& requiredExpIncreaseMagnification)
{
	// レベル上限を99に設定
	if (m_currentLevel >= kMaxLevel)return;

	IncreaseEXP(isEarn, exp);
	IncreaseLevel(requiredExpIncreaseMagnification);
}

void EXPBar::Update(const bool& isEarn, const int& exp,
	const float& requiredExpIncreaseMagnification, const int& screenWidth)
{
	// レベル上限を99に設定
	if (m_currentLevel >= kMaxLevel)return;

	IncreaseEXP(isEarn, exp);
	IncreaseLevel(requiredExpIncreaseMagnification, screenWidth);
}

void EXPBar::Draw()
{
	// 背景→ゲージ→枠→レベルの順に描画
	// デバッグ時のみデバッグ情報を可視化
	DrawBarBG();
	DrawBarGauge();
	DrawBarFrame();
	DrawLevel();
#ifdef _DEBUG
	//DebugDraw();
#else
#endif // DEBUG

}

void EXPBar::Draw(const int& screenWidth, const int& screenHeight)
{
	// 背景→ゲージ→枠→レベルの順に描画
	// デバッグ時のみデバッグ情報を可視化
	DrawBarBG(screenWidth, screenHeight);
	DrawBarGauge(screenHeight);
	DrawBarFrame(screenWidth, screenHeight);
	DrawLevel(screenWidth, screenHeight);
#ifdef _DEBUG
	DebugDraw();
#else
#endif // DEBUG

}

//////////////////////////////////////////////////////////////////////////////

void EXPBar::SetRequiredEXP(const int& requiredExp)
{
	m_requiredExp = requiredExp;
}

void EXPBar::SetIncreaseRate()
{
	// 計算式
	// 増加量 = floatにキャスト((ウィンドウの幅 - (バーの幅の補正値 * 2))) / 要求経験値
	m_expIncreaseRate =
		static_cast<float>((Game::kScreenWidth - (kBarWidthMargin * 2))) / m_requiredExp;
}

void EXPBar::SetIncreaseRate(const int& screenWidth)
{
	// 計算式
	// 増加量 = floatにキャスト((ウィンドウの幅 - (バーの幅の補正値 * 2))) / 要求経験値
	m_expIncreaseRate =
		static_cast<float>((screenWidth - (kBarWidthMargin * 2))) / m_requiredExp;

}

void EXPBar::UpdateRequiredEXP()
{
	// 前回のレベルと現在レベルが同じなら早期リターン
	if (m_beforeLevel == m_currentLevel)return;

	// 要求経験値の更新
	m_requiredExp *= kRequiredExpIncreaseMagnification;
	SetIncreaseRate();

	// 前回のレベルを更新
	m_beforeLevel = m_currentLevel;
}

void EXPBar::UpdateRequiredEXP(const float& requiredExpIncreaseMagnification)
{
	// 前回のレベルと現在レベルが同じなら早期リターン
	if (m_beforeLevel == m_currentLevel)return;

	// 要求経験値の更新
	m_requiredExp *= requiredExpIncreaseMagnification;
	SetIncreaseRate();

	// 前回のレベルを更新
	m_beforeLevel = m_currentLevel;
}

void EXPBar::UpdateRequiredEXP(const float& requiredExpIncreaseMagnification,
	const int& screenWidth)
{
	// 前回のレベルと現在レベルが同じなら早期リターン
	if (m_beforeLevel == m_currentLevel)return;

	// 要求経験値の更新
	m_requiredExp *= requiredExpIncreaseMagnification;
	SetIncreaseRate(screenWidth);
	
	// 前回のレベルを更新
	m_beforeLevel = m_currentLevel;
}

void EXPBar::IncreaseEXP(const int& exp)
{
	// 経験値ゲージの加算
	// 計算式：
	// 経験値ゲージの増加量 * 経験値量
	m_gaugeWidth += (m_expIncreaseRate * exp);

	// 経験値取得回数の加算
	m_expEarnCount += exp;
}

void EXPBar::IncreaseEXP(const bool& isEarn, const int& exp)
{
	// 経験値を獲得していないなら早期リターン
	if (!isEarn)return;

	// 経験値ゲージの加算
	// 計算式：
	// 経験値ゲージの増加量 * 経験値量
	m_gaugeWidth += (m_expIncreaseRate * exp);

	// 経験値取得回数の加算
	m_expEarnCount += exp;
}

void EXPBar::IncreaseLevel()
{
	// 経験値取得回数が要求経験値を上回らないうちは早期リターン
	if (!(m_expEarnCount >= m_requiredExp)) return;

	int buf = m_expEarnCount - m_requiredExp;

	// 経験値ゲージの幅をリセット
	m_gaugeWidth = kBarWidthMargin;

	// 現在レベルをカウントアップ
	m_currentLevel++;

	UpdateRequiredEXP();

	// 経験値取得回数をリセット
	m_expEarnCount = 0;

	IncreaseEXP(buf);
}

void EXPBar::IncreaseLevel(const float& requiredExpIncreaseMagnification)
{
	// 経験値取得回数が要求経験値を上回らないうちは早期リターン
	if (!(m_expEarnCount >= m_requiredExp)) return;

	int buf = m_expEarnCount - m_requiredExp;

	// 経験値ゲージの幅をリセット
	m_gaugeWidth = kBarWidthMargin;

	// 現在レベルをカウントアップ
	m_currentLevel++;

	UpdateRequiredEXP(requiredExpIncreaseMagnification);

	// 経験値取得回数をリセット
	m_expEarnCount = 0;

	IncreaseEXP(buf);
}

void EXPBar::IncreaseLevel(const float& requiredExpIncreaseMagnification,
	const int& screenWidth)
{
	// 経験値取得回数が要求経験値を上回らないうちは早期リターン
	if (!(m_expEarnCount >= m_requiredExp)) return;

	int buf = m_expEarnCount - m_requiredExp;

	// 経験値ゲージの幅をリセット
	m_gaugeWidth = kBarWidthMargin;

	// 現在レベルをカウントアップ
	m_currentLevel++;

	UpdateRequiredEXP(requiredExpIncreaseMagnification, screenWidth);

	// 経験値取得回数をリセット
	m_expEarnCount = 0;

	IncreaseEXP(buf);
}

void EXPBar::DrawBarBG()
{
	// 左上頂点(5, 5)、右下頂点(ウィンドウの幅 - 5, (ウィンドウの高さ * 0.04f) + 5)
	// の矩形を作る
	DrawBox(kBarWidthMargin, kBarHeightMargin,
		Game::kScreenWidth - kBarWidthMargin,
		(Game::kScreenHeight * kBarHeightMagnification) + kBarHeightMargin,
		Color::kGray, true);
}

void EXPBar::DrawBarBG(const int& screenWidth, const int& screenHeight)
{
	// 左上頂点(5, 5)、右下頂点(ウィンドウの幅 - 5, (ウィンドウの高さ * 0.04f) + 5)
	// の矩形を作る
	DrawBox(kBarWidthMargin, kBarHeightMargin,
		screenWidth - kBarWidthMargin,
		(screenHeight * kBarHeightMagnification) + kBarHeightMargin,
		Color::kGray, true);
}

void EXPBar::DrawBarGauge()
{
	// 左上頂点(5, 5)、右下頂点(ゲージの幅, (ウィンドウの高さ * 0.04f) + 5)
	// の矩形を作る
	DrawBox(kBarWidthMargin, kBarHeightMargin,
		m_gaugeWidth,
		(Game::kScreenHeight * kBarHeightMagnification) + kBarHeightMargin,
		Color::kBlue, true);
}

void EXPBar::DrawBarGauge(const int& screenHeight)
{
	// 左上頂点(5, 5)、右下頂点(ゲージの幅, (ウィンドウの高さ * 0.04f) + 5)
	// の矩形を作る
	DrawBox(kBarWidthMargin, kBarHeightMargin,
		m_gaugeWidth,
		(screenHeight * kBarHeightMagnification) + kBarHeightMargin,
		Color::kBlue, true);
}

void EXPBar::DrawBarFrame()
{
	// 左上頂点(5, 5)、右下頂点(ウィンドウの幅 - 5, (ウィンドウの高さ * 0.04f) + 5)
	// の矩形を作る
	DrawBox(kBarWidthMargin, kBarHeightMargin, 
		Game::kScreenWidth - kBarWidthMargin, 
		(Game::kScreenHeight * kBarHeightMagnification) + kBarHeightMargin,
		Color::kWhite, false);
}

void EXPBar::DrawBarFrame(const int& screenWidth, const int& screenHeight)
{
	// 左上頂点(5, 5)、右下頂点(ウィンドウの幅 - 5, (ウィンドウの高さ * 0.04f) + 5)
	// の矩形を作る
	DrawBox(kBarWidthMargin, kBarHeightMargin,
		screenWidth - kBarWidthMargin,
		(screenHeight * kBarHeightMagnification) + kBarHeightMargin,
		Color::kWhite, false);
}

void EXPBar::DrawLevel()
{
	// "Level 01"みたいな表記にしたいので
	// 現在レベルで分岐
	if (m_currentLevel < 10) {

		DrawFormatString(Game::kScreenWidth - kLevelPosXMargin, 
			(Game::kScreenHeight * kBarHeightMagnification) * kLevelPosYMarginMagnification,
			Color::kWhite, "Level 0%d",m_currentLevel);
	}
	else
	{
		DrawFormatString(Game::kScreenWidth - kLevelPosXMargin,
			(Game::kScreenHeight * kBarHeightMagnification) * kLevelPosYMarginMagnification,
			Color::kWhite, "Level %d", m_currentLevel);
	}
}

void EXPBar::DrawLevel(const int& screenWidth, const int& screenHeight)
{
	// "Level 01"みたいな表記にしたいので
	// 現在レベルで分岐
	if (m_currentLevel < 10) {

		DrawFormatString(screenWidth - kLevelPosXMargin,
			(screenHeight * kBarHeightMagnification) * kLevelPosYMarginMagnification,
			Color::kWhite, "Level 0%d", m_currentLevel);
	}
	else
	{
		DrawFormatString(screenWidth - kLevelPosXMargin,
			(screenHeight * kBarHeightMagnification) * kLevelPosYMarginMagnification,
			Color::kWhite, "Level %d", m_currentLevel);
	}
}

#ifdef _DEBUG

void EXPBar::DebugIncreaseEXP()
{
	if (Input::IsDown(PAD_INPUT_10)) {
		m_gaugeWidth += m_expIncreaseRate;
		m_expEarnCount++;
	}

	if (Input::IsPressed(PAD_INPUT_1)) {
		m_gaugeWidth += m_expIncreaseRate * 100;
		m_expEarnCount += 100;
	}

}

void EXPBar::DebugDraw()
{
	printfDx("\n\n\n\n経験値ゲージの増加量：%f\n", m_expIncreaseRate);
	printfDx("ゲージ右下のX座標：%f\n", m_gaugeWidth);
	printfDx("要求経験値：%d\n", m_requiredExp);
	printfDx("経験値取得回数：%d\n", m_expEarnCount);
}
#endif // _DEBUG

