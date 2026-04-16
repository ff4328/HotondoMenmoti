#pragma once
#include "../Yama596/Scene/SceneBase.h"
#include "DxLib.h"

#include "LotteryPusive.h"
#include "WeaponManager.h"
#include "PlayerStatus.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/EnemyYama.h"

#include <string>
#include <vector>
#include <iostream>

class EXPBar;

class FIREBAR_Scene : public SceneBase
{
public:
	/// <summary>
	/// FIREBAR_Sceneのコンストラクタ
	/// </summary>
	FIREBAR_Scene();

	/// <summary>
	/// FIREBAR_Sceneのデストラクタ
	/// </summary>
	~FIREBAR_Scene()override = default;

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
	/// SceneMain画面の処理を行う
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:
	std::unique_ptr<LotteryPusive> m_pLotteryPassive;
	PlayerMove* m_pPlayer;
	std::unique_ptr<EnemyYama> m_pEnemy;
	WeaponManager* m_pWeaponMgr;
	PlayerStatus* m_pPlayerStatus;
	EXPBar* m_pExpBar;
};