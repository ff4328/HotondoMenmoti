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
	/// シーンに入って最初の1フレームかどうか
	/// </summary>
	bool m_firstFrame = true;

};

