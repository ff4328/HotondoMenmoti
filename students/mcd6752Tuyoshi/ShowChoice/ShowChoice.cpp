#include "ShowChoice.h"

#include <DxLib.h>

#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../Utility/Input.h"

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

	constexpr float kShowFramePosXMagnification = 0.01f;
	constexpr float kShowFramePosYMagnification = 0.07f;

	constexpr int kShowFrameSideLength = 40;

	constexpr int kMaxLevel = 5;
	constexpr float kLevelDivPos = 1.0f / kMaxLevel;
}

////////////////////////////////////////////////////////////////////////////////////////

ShowChoice::ShowChoice():
	m_graphHandle(-1),
	m_screenWidth(Game::kScreenWidth),
	m_screenHeight(Game::kScreenHeight),
	m_choiceLevel(0),
	m_graphNum(-1)
{

}

ShowChoice::ShowChoice(unsigned int screenWidth, unsigned int screenHeight, int choiceLevel):
	m_graphHandle(-1),
	m_screenWidth(screenWidth),
	m_screenHeight(screenHeight),
	m_choiceLevel(choiceLevel),
	m_graphNum(0)
{
}

void ShowChoice::DebugInit()
{
	m_graphHandle = LoadGraph(kGraphHandles[6]);
	m_screenWidth = Game::kScreenWidth;
	m_screenHeight = Game::kScreenHeight;
	m_choiceLevel = 0;
	m_graphNum = -1;
}

void ShowChoice::Init()
{
}

void ShowChoice::Init(const char* const filePath)
{
	m_graphHandle = LoadGraph(filePath);
}

void ShowChoice::End() 
{
	DeleteGraph(m_graphHandle);
}

void ShowChoice::Update() 
{
	//DebugLevelChange();
	//DebugGraphChange();
}

void ShowChoice::Draw() 
{
	DrawShowGraph();
	DrawShowFrame();
	DrawShowLevel(m_choiceLevel);
}

void ShowChoice::Draw(const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPos, const int& showFrameSideLength)
{
	DrawShowGraph(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowFrame(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowLevel(maxLevel,
		showFramePosXMagnification, showFramePosYMagnification,
		showFrameWhileSpaceLengthX, showFrameWhileSpaceLengthY,
		counterNum, columnCount, levelDivPos, showFrameSideLength);
}

void ShowChoice::Draw(const int& choiceLv, const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPos, const int& showFrameSideLength)
{
	DrawShowGraph(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowFrame(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowLevel(choiceLv, maxLevel,
		showFramePosXMagnification, showFramePosYMagnification,
		showFrameWhileSpaceLengthX, showFrameWhileSpaceLengthY,
		counterNum, columnCount, levelDivPos, showFrameSideLength);
}

void ShowChoice::Draw(const int& choiceLv, const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPos, const int& showFrameSideLength, const int& graphHandle)
{
	DrawShowGraph(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength,
		graphHandle);
	DrawShowFrame(showFramePosXMagnification,
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowLevel(choiceLv, maxLevel, 
		showFramePosXMagnification, showFramePosYMagnification,
		showFrameWhileSpaceLengthX, showFrameWhileSpaceLengthY,
		counterNum, columnCount, levelDivPos, showFrameSideLength);
}

void ShowChoice::Draw(
	const int& choiceLv,
	const int& maxLevel, 
	const unsigned int& screenWidth,
	const unsigned int& screenHeight, 
	const float& showFramePosXMagnification, 
	const float& showFramePosYMagnification, 
	const int& showFrameWhileSpaceLengthX, 
	const int& showFrameWhileSpaceLengthY, 
	int counterNum, const int& columnCount, 
	const float& levelDivPos,
	const int& showFrameSideLength, const int& graphHandle)
{
	DrawShowGraph(screenWidth, screenHeight, showFramePosXMagnification, 
		showFramePosYMagnification, showFrameWhileSpaceLengthX,
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength,
		graphHandle);
	DrawShowFrame(screenWidth, screenHeight, showFramePosXMagnification, 
		showFramePosYMagnification, showFrameWhileSpaceLengthX, 
		showFrameWhileSpaceLengthY, counterNum, columnCount, showFrameSideLength);
	DrawShowLevel(choiceLv, maxLevel, screenWidth, screenHeight,
		showFramePosXMagnification, showFramePosYMagnification, 
		showFrameWhileSpaceLengthX, showFrameWhileSpaceLengthY, 
		counterNum, columnCount, levelDivPos, showFrameSideLength);

}

void ShowChoice::SetChoiceGraph(const char* const filePath)
{
	m_graphHandle = LoadGraph(filePath);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShowChoice::DrawShowGraph()
{
	DrawExtendGraph((m_screenWidth * kShowFramePosXMagnification),
		m_screenHeight * kShowFramePosYMagnification,
		(m_screenWidth * kShowFramePosXMagnification) + kShowFrameSideLength,
		(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength,
		m_graphHandle, true);
}

void ShowChoice::DrawShowGraph(const int& graphHandle)
{
	DrawExtendGraph((m_screenWidth * kShowFramePosXMagnification),
		m_screenHeight * kShowFramePosYMagnification,
		(m_screenWidth * kShowFramePosXMagnification) + kShowFrameSideLength,
		(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength,
		graphHandle, true);
}

void ShowChoice::DrawShowGraph(const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const int& showFrameSideLength)
{
	DrawExtendGraph((m_screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		m_screenHeight * showFramePosYMagnification + (showFrameWhileSpaceLengthY * columnCount),
		(m_screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		m_graphHandle, true);
}

void ShowChoice::DrawShowGraph(const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const int& showFrameSideLength, const int& graphHandle)
{
	DrawExtendGraph((m_screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		m_screenHeight * showFramePosYMagnification + (showFrameWhileSpaceLengthY * columnCount),
		(m_screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		graphHandle, true);
}

void ShowChoice::DrawShowGraph(
	const unsigned int& screenWidth, 
	const unsigned int& screenHeight, 
	const float& showFramePosXMagnification,
	const float& showFramePosYMagnification, 
	const int& showFrameWhileSpaceLengthX, 
	const int& showFrameWhileSpaceLengthY, 
	int counterNum, 
	const int& columnCount, 
	const int& showFrameSideLength, 
	const int& graphHandle)
{
	DrawExtendGraph((screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		screenHeight * showFramePosYMagnification + (showFrameWhileSpaceLengthY * columnCount),
		(screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		graphHandle, true);
}

void ShowChoice::DrawShowFrame()
{
	DrawBox((m_screenWidth * kShowFramePosXMagnification),
		m_screenHeight * kShowFramePosYMagnification,
		(m_screenWidth * kShowFramePosXMagnification) + kShowFrameSideLength,
		(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength,
		Color::kWhite, false);

}

void ShowChoice::DrawShowFrame(const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const int& showFrameSideLength)
{
	DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + (showFrameWhileSpaceLengthY * columnCount),
		(m_screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		Color::kWhite, false);
}

void ShowChoice::DrawShowFrame(
	const unsigned int& screenWidth,
	const unsigned int& screenHeight,
	const float& showFramePosXMagnification,
	const float& showFramePosYMagnification,
	const int& showFrameWhileSpaceLengthX,
	const int& showFrameWhileSpaceLengthY, 
	int counterNum,
	const int& columnCount,
	const int& showFrameSideLength)
{
	DrawBox((screenWidth * showFramePosXMagnification) + (showFrameWhileSpaceLengthX * counterNum),
		(screenHeight * showFramePosYMagnification) + (showFrameWhileSpaceLengthY * columnCount),
		(screenWidth * showFramePosXMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthX * counterNum),
		(screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
		Color::kWhite, false);
}

void ShowChoice::DrawShowLevel(const int& choiceLv)
{
	for (int i = 0; i < choiceLv; i++) {

		DrawBox((m_screenWidth * kShowFramePosXMagnification) + (kShowFrameSideLength * (i * kLevelDivPos)),
			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength,
			(m_screenWidth * kShowFramePosXMagnification) + (kShowFrameSideLength * ((i + 1) * kLevelDivPos)),
			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength + (kShowFrameSideLength * kLevelDivPos),
			GetColor(252,175,23), true);

	}

	for (int i = 0; i < kMaxLevel; i++) {

		DrawBox((m_screenWidth * kShowFramePosXMagnification) + (kShowFrameSideLength * (i * kLevelDivPos)),
			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength,
			(m_screenWidth * kShowFramePosXMagnification) + (kShowFrameSideLength * ((i + 1) * kLevelDivPos)),
			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength + (kShowFrameSideLength * kLevelDivPos),
			Color::kWhite, false);

	}
}

void ShowChoice::DrawShowLevel(const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPos, const int& showFrameSideLength)
{
	for (int i = 0; i < m_choiceLevel; i++) {

		DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPos) + (showFrameWhileSpaceLengthY * columnCount),
			GetColor(252, 175, 23), true);

	}

	for (int i = 0; i < maxLevel; i++) {

		DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPos) + (showFrameWhileSpaceLengthY * columnCount),
			Color::kWhite, false);

	}
}

void ShowChoice::DrawShowLevel(const int& choiceLv, const int& maxLevel, const float& showFramePosXMagnification, const float& showFramePosYMagnification, const int& showFrameWhileSpaceLengthX, const int& showFrameWhileSpaceLengthY, int counterNum, const int& columnCount, const float& levelDivPos, const int& showFrameSideLength)
{
	for (int i = 0; i < choiceLv; i++) {

		DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPos) + (showFrameWhileSpaceLengthY * columnCount),
			GetColor(252, 175, 23), true);

	}

	for (int i = 0; i < maxLevel; i++) {

		DrawBox((m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(m_screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(m_screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPos) + (showFrameWhileSpaceLengthY * columnCount),
			Color::kWhite, false);

	}
}

void ShowChoice::DrawShowLevel(
	const int& choiceLv, 
	const int& maxLevel, 
	const unsigned int& screenWidth, 
	const unsigned int& screenHeight, 
	const float& showFramePosXMagnification,
	const float& showFramePosYMagnification, 
	const int& showFrameWhileSpaceLengthX,
	const int& showFrameWhileSpaceLengthY, 
	int counterNum,
	const int& columnCount,
	const float& levelDivPos,
	const int& showFrameSideLength)
{

	for (int i = 0; i < choiceLv; i++) {

		DrawBox((screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPos) + (showFrameWhileSpaceLengthY * columnCount),
			GetColor(252, 175, 23), true);

	}

	for (int i = 0; i < maxLevel; i++) {

		DrawBox((screenWidth * showFramePosXMagnification) + (showFrameSideLength * (i * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameWhileSpaceLengthY * columnCount),
			(screenWidth * showFramePosXMagnification) + (showFrameSideLength * ((i + 1) * levelDivPos)) + (showFrameWhileSpaceLengthX * counterNum),
			(screenHeight * showFramePosYMagnification) + showFrameSideLength + (showFrameSideLength * levelDivPos) + (showFrameWhileSpaceLengthY * columnCount),
			Color::kWhite, false);

	}
}

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

