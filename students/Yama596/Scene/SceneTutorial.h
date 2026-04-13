#pragma once
#include "SceneBase.h"

class SceneTutorial : public SceneBase
{

public:

	/// <summary>
	/// SceneTutorial画面のコンストラクタ
	/// </summary>
	SceneTutorial();

	/// <summary>
	/// SceneTutorial画面のデストラクタ
	/// </summary>
	virtual ~SceneTutorial() override = default;

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init() override;

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End() override;

	/// <summary>
	/// SceneTutorial画面の処理を行う
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// SceneTutorial画面の描画を行う
	/// </summary>
	void Draw() override;

private:



};

