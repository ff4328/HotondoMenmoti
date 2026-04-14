#pragma once
#include "SceneBase.h"
#include "DxLib.h"

/// <summary>
/// SceneTitleのクラス
/// </summary>
class SceneTitle : public SceneBase
{

public:

	/// <summary>
	/// SceneTitle画面のコンストラクタ
	/// </summary>
	SceneTitle();

	/// <summary>
	/// SceneTitle画面のデストラクタ
	/// </summary>
	virtual ~SceneTitle() override = default;

	/// <summary>
	/// 初期設定
	/// 画面の初期設定を行う
	/// </summary>
	void Init() override;

	/// <summary>
	/// 後処理
	/// 画面の後処理を行う
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理
	/// SceneTitle画面の処理を行う
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// 描画処理
	/// SceneTitle画面の描画を行う
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
	/// 
	/// </summary>
	bool m_startSelect;

	/// <summary>
	/// 
	/// </summary>
	bool m_tutorialSelect;

	/// <summary>
	/// 
	/// </summary>
	bool m_endSelect;

};

