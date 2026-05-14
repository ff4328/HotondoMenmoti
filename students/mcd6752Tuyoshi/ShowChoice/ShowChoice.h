#pragma once

/// <summary>
/// プレイヤーが取得した武器・能力の一覧を表示するクラス
/// </summary>
class ShowChoice
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShowChoice();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ShowChoice() = default;

#ifdef _DEBUG

	/// <summary>
	/// デバッグ用の初期化
	/// </summary>
	void DebugInit();

#endif // _DEBUG

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

#ifdef _DEBUG

	/// <summary>
	/// 更新処理(現状デバッグ用)
	/// </summary>
	void Update();

#endif // _DEBUG

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="maxLevel">最大レベル</param>
	/// <param name="showFramePosXMagnification">表示枠のX座標を設定する倍率</param>
	/// <param name="showFramePosYMagnification">表示枠のY座標を設定する倍率</param>
	/// <param name="showFrameWhileSpaceLengthX">表示枠の間の幅</param>
	/// <param name="showFrameWhileSpaceLengthY">表示枠の間の高さ</param>
	/// <param name="counterNum">何個目の枠か(for文のiなどのカウンタを入れる想定)</param>
	/// <param name="columnCount">何行目か</param>
	/// <param name="levelDivPosMag">レベル表示を分割する倍率</param>
	/// <param name="showFrameSideLength">表示枠の大きさ</param>
	void Draw(
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPosMag,
		const int& showFrameSideLength);

	/// <summary>
	/// グラフィックハンドルを取得する関数
	/// </summary>
	/// <returns>m_graphHandle</returns>
	const int& GetChoiceGraph()const { return m_graphHandle; }

	/// <summary>
	/// 画像番号を取得する関数
	/// </summary>
	/// <returns>m_graphNum</returns>
	const int& GetChoiceNum()const { return m_graphNum; }

	/// <summary>
	/// グラフィックハンドルを設定する関数
	/// </summary>
	/// <param name="graphHandle">設定するグラフィックハンドル</param>
	void SetChoiceGraph(const int& graphHandle) { m_graphHandle = graphHandle; }

	/// <summary>
	/// 選択した武器・能力のレベルを設定する関数
	/// </summary>
	/// <param name="choiceLevel">レベル</param>
	void SetChoiceLevel(const int& choiceLevel) { m_choiceLevel = choiceLevel; }

	/// <summary>
	/// 画像番号を設定する関数
	/// </summary>
	/// <param name="graphNum">画像番号</param>
	void SetChoiceNum(const int& graphNum) { m_graphNum = graphNum; }

private:

	/// <summary>
	/// 選択した武器・能力の画像を描画する
	/// </summary>
	/// <param name="showFramePosXMagnification">表示枠のX座標を設定する倍率</param>
	/// <param name="showFramePosYMagnification">表示枠のY座標を設定する倍率</param>
	/// <param name="showFrameWhileSpaceLengthX">表示枠の間の幅</param>
	/// <param name="showFrameWhileSpaceLengthY">表示枠の間の高さ</param>
	/// <param name="counterNum">何個目の枠か(for文のiなどのカウンタを入れる想定)</param>
	/// <param name="columnCount">何行目か</param>
	/// <param name="showFrameSideLength">表示枠の大きさ</param>
	void DrawShowGraph(
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength);

	/// <summary>
	/// 表示枠を描画する
	/// </summary>
	/// <param name="showFramePosXMagnification">表示枠のX座標を設定する倍率</param>
	/// <param name="showFramePosYMagnification">表示枠のY座標を設定する倍率</param>
	/// <param name="showFrameWhileSpaceLengthX">表示枠の間の幅</param>
	/// <param name="showFrameWhileSpaceLengthY">表示枠の間の高さ</param>
	/// <param name="counterNum">何個目の枠か(for文のiなどのカウンタを入れる想定)</param>
	/// <param name="columnCount">何行目か</param>
	/// <param name="showFrameSideLength">表示枠の大きさ</param>
	void DrawShowFrame(
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const int& showFrameSideLength);

	/// <summary>
	/// 武器・能力のレベルを描画する
	/// </summary>
	/// <param name="maxLevel">最大レベル</param>
	/// <param name="showFramePosXMagnification">表示枠のX座標を設定する倍率</param>
	/// <param name="showFramePosYMagnification">表示枠のY座標を設定する倍率</param>
	/// <param name="showFrameWhileSpaceLengthX">表示枠の間の幅</param>
	/// <param name="showFrameWhileSpaceLengthY">表示枠の間の高さ</param>
	/// <param name="counterNum">何個目の枠か(for文のiなどのカウンタを入れる想定)</param>
	/// <param name="columnCount">何行目か</param>
	/// <param name="levelDivPosMag">レベル表示を分割する倍率</param>
	/// <param name="showFrameSideLength">表示枠の大きさ</param>
	void DrawShowLevel(
		const int& maxLevel,
		const float& showFramePosXMagnification,
		const float& showFramePosYMagnification,
		const int& showFrameWhileSpaceLengthX,
		const int& showFrameWhileSpaceLengthY,
		int counterNum,
		const int& columnCount,
		const float& levelDivPosMag,
		const int& showFrameSideLength);

#ifdef DEBUG

	/// <summary>
	/// デバッグ用　左右矢印でレベル増減
	/// </summary>
	void DebugLevelChange();

	/// <summary>
	/// デバッグ用　左右矢印で画像変更
	/// </summary>
	void DebugGraphChange();

#endif // DEBUG


private:

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// ウィンドウの幅
	/// </summary>
	unsigned int m_screenWidth;

	/// <summary>
	/// ウィンドウの高さ
	/// </summary>
	unsigned int m_screenHeight;

	/// <summary>
	/// 選択した武器・能力のレベル
	/// </summary>
	int m_choiceLevel;

	/// <summary>
	/// 画像番号
	/// </summary>
	int m_graphNum;
};

