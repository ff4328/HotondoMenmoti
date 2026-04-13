#pragma once

/// <summary>
/// 経験値バーのクラス
/// </summary>
class EXPBar {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EXPBar();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EXPBar() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 要求経験値を設定する初期化
	/// </summary>
	/// <param name="req">要求経験値</param>
	void Init(int req);

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// 金子のデバッグ用更新処理
	/// </summary>
	void DebugUpdate();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="isEarn">経験値を獲得したか</param>
	/// <param name="exp">経験値量(基準値：1)</param>
	void Update(bool isEarn, int exp);

	/// <summary>
	/// 更新処理
	/// 要求経験値増加倍率を1.15倍以外にしたいならこっち
	/// </summary>
	/// <param name="isEarn">経験値を獲得したか</param>
	/// <param name="exp">経験値量(基準値：1)</param>
	/// <param name="requiredExpIncreaseMagnification">要求経験値増加倍率</param>
	void Update(bool isEarn, int exp, float requiredExpIncreaseMagnification);

	/// <summary>
	/// 更新処理
	/// ウィンドウの幅を変えるならこっち
	/// </summary>
	/// <param name="isEarn">経験値を獲得したか</param>
	/// <param name="exp">経験値量(基準値：1)</param>
	/// <param name="requiredExpIncreaseMagnification">要求経験値増加倍率</param>
	/// <param name="screenWidth">ウィンドウの幅</param>
	void Update(bool isEarn, int exp, float requiredExpIncreaseMagnification, int screenWidth);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 描画処理
	/// ウィンドウサイズを変えるならこっち
	/// </summary>
	/// <param name="screenWidth">ウィンドウの幅</param>
	/// <param name="screenHeight">ウィンドウの高さ</param>
	void Draw(int screenWidth, int screenHeight);

private:

	/// <summary>
	/// 要求経験値の設定
	/// </summary>
	/// <param name="requiredExp">要求経験値</param>
	void SetRequiredEXP(int requiredExp);

	/// <summary>
	/// 経験値ゲージの増加量の設定
	/// </summary>
	void SetIncreaseRate();

	/// <summary>
	/// 経験値ゲージの増加量の設定
	/// </summary>
	/// <param name="screenWidth">ウィンドウの幅</param>
	void SetIncreaseRate(int screenWidth);

	/// <summary>
	/// 要求経験値の更新
	/// </summary>
	void UpdateRequiredEXP();

	/// <summary>
	/// 要求経験値の更新
	/// </summary>
	/// <param name="requiredExpIncreaseMagnification">要求経験値増加倍率</param>
	void UpdateRequiredEXP(float requiredExpIncreaseMagnification);

	/// <summary>
	/// 要求経験値の更新
	/// </summary>
	/// <param name="requiredExpIncreaseMagnification">要求経験値増加倍率</param>
	/// <param name="screenWidth">ウィンドウの幅</param>
	void UpdateRequiredEXP(float requiredExpIncreaseMagnification, int screenWidth);

	/// <summary>
	/// 経験値ゲージと取得回数の増加
	/// </summary>
	/// <param name="exp">経験値量(基準値：1)</param>
	void IncreaseEXP(int exp);

	/// <summary>
	/// 経験値ゲージと取得回数の増加
	/// </summary>
	/// <param name="isEarn">経験値を獲得したか</param>
	/// <param name="exp">経験値量(基準値：1)</param>
	void IncreaseEXP(bool isEarn, int exp);

	/// <summary>
	/// レベルの増加と経験値ゲージ、取得回数のリセット
	/// </summary>
	void IncreaseLevel();

	/// <summary>
	/// レベルの増加と経験値ゲージ、取得回数のリセット
	/// </summary>
	/// <param name="requiredExpIncreaseMagnification">要求経験値増加倍率</param>
	void IncreaseLevel(float requiredExpIncreaseMagnification);

	/// <summary>
	/// レベルの増加と経験値ゲージ、取得回数のリセット
	/// </summary>
	/// <param name="requiredExpIncreaseMagnification">要求経験値増加倍率</param>
	/// <param name="screenWidth">ウィンドウの幅</param>
	void IncreaseLevel(float requiredExpIncreaseMagnification, int screenWidth);

	/// <summary>
	/// 経験値バーの背景の描画
	/// </summary>
	void DrawBarBG();

	/// <summary>
	/// 経験値バーの背景の描画
	/// </summary>
	/// <param name="screenWidth">ウィンドウの幅</param>
	/// <param name="screenHeight">ウィンドウの高さ</param>
	void DrawBarBG(int screenWidth, int screenHeight);

	/// <summary>
	/// 経験値ゲージの描画
	/// </summary>
	void DrawBarGauge();

	/// <summary>
	/// 経験値ゲージの描画
	/// </summary>
	/// <param name="screenHeight">ウィンドウの高さ</param>
	void DrawBarGauge(int screenHeight);

	/// <summary>
	/// 経験値バーの枠の描画
	/// </summary>
	void DrawBarFrame();

	/// <summary>
	/// 経験値バーの枠の描画
	/// </summary>
	/// <param name="screenWidth">ウィンドウの幅</param>
	/// <param name="screenHeight">ウィンドウの高さ</param>
	void DrawBarFrame(int screenWidth, int screenHeight);

	/// <summary>
	/// レベルの描画
	/// </summary>
	void DrawLevel();

	/// <summary>
	/// レベルの描画
	/// </summary>
	/// <param name="screenWidth">ウィンドウの幅</param>
	/// <param name="screenHeight">ウィンドウの高さ</param>
	void DrawLevel(int screenWidth, int screenHeight);

	/// <summary>
	/// デバッグ用経験値増加処理
	/// Zキー		：1回押すごとに経験値取得回数1増加
	/// スペースキー：押している間経験値取得回数1増加
	/// </summary>
	void DebugIncreaseEXP();

	/// <summary>
	/// デバッグ用関数
	/// 以下の数値を可視化：
	/// ・経験値増加割合
	/// ・ゲージ右下のX座標
	/// ・要求経験値
	/// ・経験値取得回数
	/// </summary>
	void DebugDraw();

private:

	/// <summary>
	/// 経験値ゲージの幅(ゲージ右下のX座標)
	/// </summary>
	float m_gaugeWidth;

	/// <summary>
	/// 要求経験値
	/// </summary>
	int m_requiredExp;

	/// <summary>
	/// 経験値ゲージの増加量
	/// </summary>
	float m_expIncreaseRate;

	/// <summary>
	/// 現在レベル
	/// </summary>
	int m_currentLevel;

	/// <summary>
	/// 前回のレベル
	/// </summary>
	int m_beforeLevel;

	/// <summary>
	/// 経験値取得回数
	/// </summary>
	int m_expEarnCount;
};