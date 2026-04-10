#include "SceneBase.h"

namespace Color {

	// 白
	constexpr int kWhite = 0xffffff;

	// 黒
	constexpr int kBlack = 0x000000;

	// 赤
	constexpr int kRed = 0xff0000;

	// 緑
	constexpr int kGreen = 0x00ff00;

	// 青
	constexpr int kBlue = 0x0000ff;

	// イエロー
	constexpr int kYellow = 0xffff00;

	// シアン
	constexpr int kCyan = 0x00ffff;

	// マゼンタ
	constexpr int kMazenta = 0xff00ff;

	// オレンジ
	constexpr int kOrange = 0xF07023;

}

namespace {

	constexpr int kFadeSpeed = 5;

}

SceneBase::SceneBase():
	m_fadeColor(Color::kBlack),
	m_fadeBright(255),
	m_fadeSpeed(-kFadeSpeed),
	m_isFadeOut(false)
{
}

void SceneBase::UpdateFade()
{
}

void SceneBase::DrawFade() const
{
}

bool SceneBase::IsFadingIn() const
{
	return false;
}

bool SceneBase::IsFadingOut() const
{
	return false;
}

bool SceneBase::IsFading() const
{
	return false;
}

void SceneBase::StartFadeOut()
{
}

bool SceneBase::IsFadeOutEnd() const
{
	return false;
}

bool SceneBase::IsFadeInEnd() const
{
	return false;
}
