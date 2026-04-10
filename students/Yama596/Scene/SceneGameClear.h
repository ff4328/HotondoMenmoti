#pragma once
#include "SceneBase.h"

class SceneGameClear : public SceneBase
{

public:

	/// <summary>
	/// SceneGameClear
	/// </summary>
	SceneGameClear();

	virtual ~SceneGameClear() override = default;

	void Init() override;

	void End() override;

	SceneBase* Update() override;

	void Draw() override;

};

