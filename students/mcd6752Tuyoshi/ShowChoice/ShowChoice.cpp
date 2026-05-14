#include "ShowChoice.h"

#include <DxLib.h>

#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../Utility/Input.h"

#ifdef _DEBUG
namespace {

	const char* const kGraphHandles[] =
	{
		".\\Resource\\Item\\AttackRange.png",
		".\\Resource\\Item\\AttackSpeed.png",
		".\\Resource\\Item\\LimitBreak.png",
		".\\Resource\\Item\\MovementSpeed.png",
		".\\Resource\\image\\AxeSlot.png",
		".\\Resource\\image\\ArrowSlot.png",
		".\\Resource\\image\\SwordSlot.png",
		".\\Resource\\image\\MagicBottleSlot.png"
	};


	constexpr int kMaxLevel = 5;

}
#endif // _DEBUG

////////////////////////////////////////////////////////////////////////////////////////

ShowChoice::ShowChoice():
	m_graphHandle(-1),
	m_screenWidth(Game::kScreenWidth),
	m_screenHeight(Game::kScreenHeight),
	m_choiceLevel(0),
	m_graphNum(-1)
{

}

#ifdef _DEBUG

void ShowChoice::DebugInit()
{
	m_graphHandle = LoadGraph(kGraphHandles[6]);
	m_screenWidth = Game::kScreenWidth;
	m_screenHeight = Game::kScreenHeight;
	m_choiceLevel = 0;
	m_graphNum = -1;
}

#endif // _DEBUG

void ShowChoice::End() 
{
	// 画像の破棄
	DeleteGraph(m_graphHandle);
}

#ifdef _DEBUG

void ShowChoice::Update() 
{
	//DebugLevelChange();
	//DebugGraphChange();
}

#endif // _DEBUG

void ShowChoice::Draw(const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPosMag, const int& showFrameSideLength)
{
	// 画像→枠→レベル表示の順に描画
	DrawShowGraph(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowFrame(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowLevel(maxLevel,
		showFramePosXMagnification, showFramePosYMagnification,
		showFrameWhileSpaceLengthX, showFrameWhileSpaceLengthY,
		counterNum, columnCount, levelDivPosMag, showFrameSideLength);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShowChoice::DrawShowGraph(const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const int& showFrameSideLength)
{
	// 画面サイズを基準に描画
	DrawExtendGraph((m_screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		m_screenHeight * showFramePosYMagnification + (showFrameWhileSpaceLengthY * columnCount),
		(m_screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		m_graphHandle, true);
}

void ShowChoice::DrawShowFrame(const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const int& showFrameSideLength)
{
	// 画面サイズを基準に描画
	DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + (showFrameWhileSpaceLengthY * columnCount),
		(m_screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		Color::kWhite, false);
}

void ShowChoice::DrawShowLevel(const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPosMag, const int& showFrameSideLength)
{
	// 画面サイズを基準に描画
	// レベル表示
	for (int i = 0; i < m_choiceLevel; i++) {

		DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPosMag)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPosMag)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPosMag) + (showFrameWhileSpaceLengthY * columnCount),
			Color::kOrange, true);

	}

	// レベル表示枠
	for (int i = 0; i < maxLevel; i++) {

		DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPosMag)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPosMag)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPosMag) + (showFrameWhileSpaceLengthY * columnCount),
			Color::kWhite, false);

	}
}

#ifdef _DEBUG

void ShowChoice::DebugLevelChange()
{
	if (Input::IsPressed(PAD_INPUT_LEFT) && m_choiceLevel > 0) m_choiceLevel--;

	if (Input::IsPressed(PAD_INPUT_RIGHT) && m_choiceLevel < kMaxLevel)m_choiceLevel++;
}

void ShowChoice::DebugGraphChange()
{
	if (Input::IsPressed(PAD_INPUT_LEFT) && m_graphNum > 0) m_graphNum--;

	if (Input::IsPressed(PAD_INPUT_RIGHT) && m_graphNum < 7)m_graphNum++;
	SetChoiceGraph(kGraphHandles[m_graphNum]);
}
#endif // _DEBUG


