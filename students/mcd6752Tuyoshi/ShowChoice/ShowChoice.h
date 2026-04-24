#pragma once



/// <summary>
/// プレイヤーが取得した武器・能力の一覧を表示するクラス
/// </summary>
class ShowChoice
{
public:

	ShowChoice();

	ShowChoice(unsigned int screenWidth, unsigned int screenHeight, int choiceLevel);

	~ShowChoice() = default;

	void DebugInit();

	void Init();

	void Init(const char* const filePath);

	void End();

	void Update();

	void Draw();

	void Draw(
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPos,
		const int& showFrameSideLength);

	void Draw(
		const int& choiceLv,
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPos,
		const int& showFrameSideLength);

	void Draw(
		const int& choiceLv,
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPos,
		const int& showFrameSideLength,
		const int& graphHandle);

	void Draw(
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
		const int& showFrameSideLength,
		const int& graphHandle);

	const int& GetChoiceGraph()const { return m_graphHandle; }

	const int& GetChoiceNum()const { return m_graphNum; }

	void SetChoiceGraph(const char* const filePath);

	void SetChoiceGraph(const int& graphHandle) { m_graphHandle = graphHandle; }

	void SetChoiceLevel(const int& choiceLevel) { m_choiceLevel = choiceLevel; }

	void SetChoiceNum(const int& graphNum) { m_graphNum = graphNum; }

private:

	void DrawShowGraph();

	void DrawShowGraph(const int& graphHandle);

	void DrawShowGraph(
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength);

	void DrawShowGraph(
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength,
		const int& graphHandle);

	void DrawShowGraph(
		const unsigned int& screenWidth,
		const unsigned int& screenHeight,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength,
		const int& graphHandle);
	
	//void DrawShowGraph(int graphHandle);

	void DrawShowFrame();

	void DrawShowFrame(
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength);

	void DrawShowFrame(
		const unsigned int& screenWidth, 
		const unsigned int& screenHeight,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength);

	void DrawShowLevel(const int& choiceLv);

	void DrawShowLevel(
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPos,
		const int& showFrameSideLength);

	void DrawShowLevel(
		const int& choiceLv,
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPos,
		const int& showFrameSideLength);

	void DrawShowLevel(
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
		const int& showFrameSideLength);

	void DebugLevelChange();

	void DebugGraphChange();

private:

	int m_graphHandle;

	unsigned int m_screenWidth;

	unsigned int m_screenHeight;

	int m_choiceLevel;

	int m_graphNum;
};

