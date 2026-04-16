#pragma once
#include "SceneBase.h"

class SceneGameClear : public SceneBase
{

public:

	/// <summary>
	/// SceneGameClear
	/// </summary>
	SceneGameClear();

	/// <summary>
	/// SceneGameClear画面のデストラクタ
	/// </summary>
	virtual ~SceneGameClear() override = default;

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init() override;

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End() override;

	/// <summary>
	/// SceneGameClear画面の処理を行う
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// SceneGameClear画面の描画を行う
	/// </summary>
	void Draw() override;

private:

	/// <summary>
	/// メニューの選択処理を行う
	/// </summary>
	void SelectMenu();

	/// <summary>
	/// タイトルとメニューを描画する
	/// </summary>
	void DrawTitleMenu();

private:

	/// <summary>
	/// 背景のハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 選択してる項目
	/// </summary>
	int m_select;

	/// <summary>
	/// 最初のフレームかどうか
	/// </summary>
	bool m_firstFrame;

	/// <summary>
	/// もういちどを選択したか
	/// </summary>
	bool m_retrySelect;

	/// <summary>
	/// タイトルを選択したか
	/// </summary>
	bool m_titleSelect;

};

