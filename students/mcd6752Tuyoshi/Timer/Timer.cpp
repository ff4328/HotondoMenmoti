#include "Timer.h"

#include <DxLib.h>

#include "../Utility/Color.h"
#include "../Utility/Game.h"

namespace {
	constexpr int kFontSize = 30;
	constexpr int kFontThick = 9;
	constexpr unsigned int kLimitMinute = 10;

	constexpr unsigned int kMaxNum = 99;
	constexpr unsigned int kMaxCount = 60;

	// 時間表示のX座標の倍率
	constexpr float kPosXMagnification = 0.5f;
	// 時間表示のX座標の補正値
	constexpr int kPosXMargin = -50;
	// 時間表示のY座標の倍率
	constexpr float kPosYMagnification = 0.08f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


Timer::Timer():
	m_isUp(true),
	m_minute(0),
	m_second(0),
	m_fontHandle(-1),
	m_timeCount(0)
{

}

void Timer::Init() {

	m_isUp = true;

	m_fontHandle = CreateFontToHandle(NULL, kFontSize, kFontThick,
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void Timer::Init(const bool& countMethod) {

	m_isUp = countMethod;

	if (!m_isUp) {
		m_minute = kLimitMinute;
	}

	m_fontHandle = CreateFontToHandle(NULL, kFontSize, kFontThick, 
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void Timer::Init(const bool& countMethod, const int& limitMinute)
{
	m_isUp = countMethod;

	if (!m_isUp) {
		m_minute = limitMinute;
	}

	m_fontHandle = CreateFontToHandle(NULL, kFontSize, kFontThick,
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void Timer::Init(const bool& countMethod, const int& limitMinute, const int& limitSecond)
{
	m_isUp = countMethod;

	if (!m_isUp) {
		m_minute = limitMinute;
		m_second = limitSecond;
	}

	m_fontHandle = CreateFontToHandle(NULL, kFontSize, kFontThick,
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void Timer::End() {

	DeleteFontToHandle(m_fontHandle);
}

void Timer::Update() {

	if (m_isUp)CountUp();
	else CountDown();
}

void Timer::Draw() {

	DrawTimer();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Timer::CountUp()
{
	// 時間上限を99:99に設定
	if (m_second == kMaxNum)return;

	m_timeCount++;

	if (m_timeCount < kMaxCount)return;

	m_timeCount = 0;

	m_second++;

	if (m_minute == kMaxNum)return;

	if (m_second < 60)return;

	m_second = 0;

	m_minute++;
}

void Timer::CountDown()
{
	if (m_minute <= 0 && m_second == 0)return;

	m_timeCount++;

	if (m_timeCount < kMaxCount)return;

	m_timeCount = 0;

	m_second--;

	if (m_second >= 0)return;

	if (m_minute <= 0 && m_second == 0)return;

	m_second = 59;

	m_minute--;
}

void Timer::DrawTimer()
{
	// "02:04"みたいな表記にしたいので
	// 分と秒の値で分岐
	if (m_minute < 10 && m_second < 10)
	{
		DrawFormatStringToHandle((Game::kScreenWidth * kPosXMagnification) + kPosXMargin, 
			Game::kScreenHeight * kPosYMagnification,
			Color::kWhite, m_fontHandle, "0%d:0%d", m_minute, m_second);
	}
	else if (m_minute < 10 && m_second >= 10)
	{
		DrawFormatStringToHandle((Game::kScreenWidth * kPosXMagnification) + kPosXMargin,
			Game::kScreenHeight * kPosYMagnification,
			Color::kWhite, m_fontHandle, "0%d:%d", m_minute, m_second);
	}
	else if (m_minute >= 10 && m_second < 10)
	{
		DrawFormatStringToHandle((Game::kScreenWidth * kPosXMagnification) + kPosXMargin,
			Game::kScreenHeight * kPosYMagnification,
			Color::kWhite, m_fontHandle, "%d:0%d", m_minute, m_second);
	}
	else
	{
		DrawFormatStringToHandle((Game::kScreenWidth * kPosXMagnification) + kPosXMargin,
			Game::kScreenHeight * kPosYMagnification,
			Color::kWhite, m_fontHandle, "%d:%d", m_minute, m_second);
	}
}
