#include "ShowChoiceManager.h"

#include <array>

#include "ShowChoice.h"

namespace {

	/// <summary>
	/// 表示枠のX座標を設定する倍率
	/// </summary>
	constexpr float kShowFramePosXMagnification = 0.01f;

	/// <summary>
	/// 表示枠のY座標を設定する倍率
	/// </summary>
	constexpr float kShowFramePosYMagnification = 0.07f;

	/// <summary>
	/// 表示枠の間の幅
	/// </summary>
	constexpr int kShowFrameWhileSpaceLengthX = 45;

	/// <summary>
	/// 表示枠の間の高さ
	/// </summary>
	constexpr int kShowFrameWhileSpaceLengthY = 55;

	/// <summary>
	/// 表示枠の大きさ
	/// </summary>
	constexpr int kShowFrameSideLength = 40;


	/// <summary>
	/// 最大レベル
	/// </summary>
	constexpr int kMaxLevel = 5;

	/// <summary>
	/// レベル表示を分割する倍率
	/// </summary>
	constexpr float kLevelDivPosMagnification = 1.0f / kMaxLevel;
}

/////////////////////////////////////////////////////////////////////////////////////////

ShowChoiceManager::ShowChoiceManager():
	m_pChoiceWeapons{nullptr},
	m_pChoicePassives{nullptr}
{
}

ShowChoiceManager::~ShowChoiceManager()
{
}

void ShowChoiceManager::Init() 
{
	// 範囲for文で初期化する
	for (auto& weapon : m_pChoiceWeapons)
	{
		weapon = std::make_unique<ShowChoice>();
		//weapon->Init();
	}

	for (auto& passive : m_pChoicePassives)
	{
		passive = std::make_unique<ShowChoice>();
		//passive->Init();
	}

}

void ShowChoiceManager::End()
{
	// 範囲for文で終了処理を行う
	for (auto& weapon : m_pChoiceWeapons)
	{
		weapon->End();
	}

	for (auto& passive : m_pChoicePassives) 
	{
		passive->End();
	}

}

//void ShowChoiceManager::Update()
//{
//	for (auto& weapon : m_pChoiceWeapons)
//	{
//		weapon->Update();
//	}
//
//	for (auto& passive : m_pChoicePassives)
//	{
//		passive->Update();
//	}
//}

void ShowChoiceManager::Draw()
{
	// 範囲for文で描画処理を行う
	for (int i = 0; i < kWeaponMax; i++)
	{
		m_pChoiceWeapons[i]->Draw(kMaxLevel, kShowFramePosXMagnification,
			kShowFramePosYMagnification, kShowFrameWhileSpaceLengthX,
			kShowFrameWhileSpaceLengthY, i, static_cast<int>(kColumnZero), 
			kLevelDivPosMagnification, kShowFrameSideLength);
	}

	for (int i = 0; i < kPassiveMax; i++)
	{
		m_pChoicePassives[i]->Draw(kMaxLevel, kShowFramePosXMagnification,
			kShowFramePosYMagnification, kShowFrameWhileSpaceLengthX,
			kShowFrameWhileSpaceLengthY, i, static_cast<int>(kColumnOne), 
			kLevelDivPosMagnification, kShowFrameSideLength);
	}
}

void ShowChoiceManager::SetChoiceWeapons(const int& v, 
	const int& weaponGraphHandle, const int& choiceLevel)
{
	SetChoiceWeaponsNum(v);
	SetChoiceWeaponsGraph(weaponGraphHandle);
	SetChoiceWeaponsLevel(choiceLevel, v);
}

void ShowChoiceManager::SetChoicePassives(const int& v, 
	const int& passiveGraphHandle, const int& choiceLevel)
{
	SetChoicePassivesNum(v);
	SetChoicePassivesGraph(passiveGraphHandle);
	SetChoicePassivesLevel(choiceLevel, v);
}

/////////////////////////////////////////////////////////////////////////////////////////

void ShowChoiceManager::SetChoiceWeaponsNum(const int& v)
{
	for (int i = 0; i < kWeaponMax; i++)
	{	// 武器の番号が初期値でないなら
		if (m_pChoiceWeapons[i]->GetChoiceNum() != -1) {
			// i番目の番号がvと同じならリターン
			if (m_pChoiceWeapons[i]->GetChoiceNum() == v) {
				return;
			}
			else
			{// そうでなければ繰り返す
				continue;
			}
		}
		else
		{// 初期値なら番号を設定する
			m_pChoiceWeapons[i]->SetChoiceNum(v);
			return;
		}
	}
}

void ShowChoiceManager::SetChoicePassivesNum(const int& v)
{
	for (int i = 0; i < kPassiveMax; i++)
	{	// 能力の番号が初期値でないなら
		if (m_pChoicePassives[i]->GetChoiceNum() != -1) {
			// i番目の番号がvと同じならリターン
			if (m_pChoicePassives[i]->GetChoiceNum() == v) {
				return;
			}
			else
			{// そうでなければ繰り返す
				continue;
			}
		}
		else
		{// 初期値なら番号を設定する
			m_pChoicePassives[i]->SetChoiceNum(v);
			return;
		}
	}
}

void ShowChoiceManager::SetChoiceWeaponsGraph(const int& weaponGraphHandle)
{
	for (int i = 0; i < kWeaponMax; i++) {
		// 武器のグラフハンドルが初期値でないなら
		if (m_pChoiceWeapons[i]->GetChoiceGraph() != -1) {
			// i番目のグラフハンドルが引数と同じならリターン
			if (m_pChoiceWeapons[i]->GetChoiceGraph() == weaponGraphHandle) {
				return;
			}
			else
			{// そうでなければ繰り返す
				continue;
			}
		}
		else
		{// 初期値ならグラフハンドルを設定する
			m_pChoiceWeapons[i]->SetChoiceGraph(weaponGraphHandle);
			return;
		}
	}
}

void ShowChoiceManager::SetChoicePassivesGraph(const int& passiveGraphHandle)
{
	for (int i = 0; i < kPassiveMax; i++) {
		// 能力のグラフハンドルが初期値でないなら
		if (m_pChoicePassives[i]->GetChoiceGraph() != -1) {
			// i番目のグラフハンドルが引数と同じならリターン
			if (m_pChoicePassives[i]->GetChoiceGraph() == passiveGraphHandle) {
				return;
			}
			else
			{// そうでなければ繰り返す
				continue;
			}
		}
		else
		{// 初期値ならグラフハンドルを設定する
			m_pChoicePassives[i]->SetChoiceGraph(passiveGraphHandle);
			return;
		}
	}
}

void ShowChoiceManager::SetChoiceWeaponsLevel(const int& choiceLevel, const int& v)
{
	for (int i = 0; i < kWeaponMax; i++)
	{	// i番目の番号がvと同じでないなら繰り返す
		if (m_pChoiceWeapons[i]->GetChoiceNum() != v)continue;
		else
		{// 同じならレベルを設定する
			m_pChoiceWeapons[i]->SetChoiceLevel(choiceLevel);
			return;
		}
	}
}

void ShowChoiceManager::SetChoicePassivesLevel(const int& choiceLevel, const int& v)
{
	for (int i = 0; i < kPassiveMax; i++)
	{	// i番目の番号がvと同じでないなら繰り返す
		if (m_pChoicePassives[i]->GetChoiceNum() != v)continue;
		else
		{// 同じならレベルを設定する
			m_pChoicePassives[i]->SetChoiceLevel(choiceLevel);
			return;
		}
	}
}

