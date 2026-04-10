#pragma once
#include "SceneBase.h"
#include <DxLib.h>
#include "../FIREBAR/WeaponManager.h"

// 前方宣言
class GameSetting;

/// <summary>
/// 授業で作成して確認用のクラス
/// なにか機能の確認を行うときにこのクラスで検証をする
/// </summary>
class SceneTest : public SceneBase
{
public:

	/// <summary>
	/// SceneTest画面のコンストラクタ
	/// メンバの初期設定を行う
	/// </summary>
	SceneTest();

	/// <summary>
	/// SceneTest画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneTest();

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init();

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End();

	/// <summary>
	/// SceneTest画面の処理を行う
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理をする画面</returns>
	SceneBase* Update();

	/// <summary>
	/// SceneTest画面の描画を行う
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// 位置関係が分かるように地面を線で描画する
	/// </summary>
	void DrawGround();

private:
	WeaponManager* pWeaponMrg;
};
