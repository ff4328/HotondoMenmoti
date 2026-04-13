#pragma once

/// <summary>
/// タイマー表示のクラス
/// 使いたいシーンのヘッダーファイルでポインタ変数作ったうえで
/// Initの引数でカウント方式(や制限時間)を指定してください
/// </summary>
class Timer
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Timer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Timer() = default;

	/// <summary>
	/// 初期化　※引数なしの場合カウントアップ
	/// </summary>
	void Init();

	/// <summary>
	/// 初期化　※カウントアップorダウンを引数で指定すること！
	/// true ：カウントアップ
	/// false：カウントダウン(10分)
	/// </summary>
	/// <param name="countMethod">カウント方式</param>
	void Init(const bool& countMethod);

	/// <summary>
	/// カウントダウン時の制限時間を設定可能な初期化
	/// ※trueにすると意味ない関数なので注意！
	/// true ：カウントアップ
	/// false：カウントダウン(limitminute分)
	/// </summary>
	/// <param name="countMethod">カウント方式</param>
	/// <param name="limitMinute">制限時間</param>
	void Init(const bool& countMethod, const int& limitMinute);

	/// <summary>
	/// カウントダウン時の制限時間を設定可能な初期化
	/// ※trueにすると意味ない関数なので注意！
	/// true ：カウントアップ
	/// false：カウントダウン(limitminute分 limitSecond秒)
	/// </summary>
	/// <param name="countMethod">カウント方式</param>
	/// <param name="limitMinute">制限時間(分)</param>
	/// <param name="limitSecond">制限時間(秒)</param>
	void Init(const bool& countMethod, const int& limitMinute, const int& limitSecond);

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 分の値を取得するゲッター関数
	/// </summary>
	/// <returns>m_minute</returns>
	const int& GetMinute()const { return m_minute; }

	/// <summary>
	/// 秒の値を取得するゲッター関数
	/// </summary>
	/// <returns>m_second</returns>
	const int& GetSecond()const { return m_second; }

private:

	/// <summary>
	/// カウントアップ
	/// </summary>
	void CountUp();

	/// <summary>
	/// カウントダウン
	/// </summary>
	void CountDown();

	/// <summary>
	/// タイマーの描画
	/// </summary>
	void DrawTimer();

private:

	/// <summary>
	/// カウントアップかどうか
	/// </summary>
	bool m_isUp;

	/// <summary>
	/// 分を表す
	/// </summary>
	int m_minute;

	/// <summary>
	/// 秒を表す
	/// </summary>
	int m_second;

	/// <summary>
	/// フォントハンドル
	/// </summary>
	int m_fontHandle;

	/// <summary>
	/// FPS値に合わせて秒を更新するためのカウンター
	/// </summary>
	int m_timeCount;
};

