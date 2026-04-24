#include "ShowChoiceManager.h"

#include <array>

#include "ShowChoice.h"


//void ShowChoice::DrawShowFrame()
//{
//	for (int i = 0; i < kWeaponMax; i++)
//	{
//		DrawBoxAA((m_screenWidth * kShowFramePosXMagnification) + (kShowFrameWhileSpaceLengthX * i),
//			m_screenHeight * kShowFramePosYMagnification,
//			(m_screenWidth * kShowFramePosXMagnification) + kShowFrameSideLength + (kShowFrameWhileSpaceLengthX * i),
//			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength,
//			Color::kWhite, false);
//	}
//
//	for (int i = 0; i < kPassiveMax; i++)
//	{
//		DrawBoxAA((m_screenWidth * kShowFramePosXMagnification) + (kShowFrameWhileSpaceLengthX * i),
//			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameWhileSpaceLengthY,
//			(m_screenWidth * kShowFramePosXMagnification) + kShowFrameSideLength + (kShowFrameWhileSpaceLengthX * i),
//			(m_screenHeight * kShowFramePosYMagnification) + kShowFrameSideLength + kShowFrameWhileSpaceLengthY,
//			Color::kWhite, false);
//	}
//}

namespace {

	constexpr float kShowFramePosXMagnification = 0.01f;
	constexpr float kShowFramePosYMagnification = 0.07f;
	constexpr int kShowFrameWhileSpaceLengthX = 45;
	constexpr int kShowFrameWhileSpaceLengthY = 55;
	constexpr int kShowFrameSideLength = 40;

	constexpr int kMaxLevel = 5;
	constexpr float kLevelDivPos = 1.0f / kMaxLevel;
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
	for (int i = 0; i < kWeaponMax; i++)
	{
		m_pChoiceWeapons[i]->Draw(kMaxLevel, kShowFramePosXMagnification,
			kShowFramePosYMagnification, kShowFrameWhileSpaceLengthX,
			kShowFrameWhileSpaceLengthY, i, static_cast<int>(kColumnZero), 
			kLevelDivPos, kShowFrameSideLength);
	}

	for (int i = 0; i < kPassiveMax; i++)
	{
		m_pChoicePassives[i]->Draw(kMaxLevel, kShowFramePosXMagnification,
			kShowFramePosYMagnification, kShowFrameWhileSpaceLengthX,
			kShowFrameWhileSpaceLengthY, i, static_cast<int>(kColumnMax), 
			kLevelDivPos, kShowFrameSideLength);
	}
}

void ShowChoiceManager::SetChoiceWeapons(const int& v, 
	const int& passiveGraphHandle, const int& choiceLevel)
{
	SetChoiceWeaponsNum(v);
	SetChoiceWeaponsGraph(passiveGraphHandle);
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
	{
		if (m_pChoiceWeapons[i]->GetChoiceNum() != -1) {
			if (m_pChoiceWeapons[i]->GetChoiceNum() == v) {
				return;
			}
			else
			{
				continue;
			}
		}
		else
		{
			m_pChoiceWeapons[i]->SetChoiceNum(v);
			return;
		}
	}
}

void ShowChoiceManager::SetChoicePassivesNum(const int& v)
{
	for (int i = 0; i < kPassiveMax; i++)
	{
		if (m_pChoicePassives[i]->GetChoiceNum() != -1) {
			if (m_pChoicePassives[i]->GetChoiceNum() == v) {
				return;
			}
			else
			{
				continue;
			}
		}
		else
		{
			m_pChoicePassives[i]->SetChoiceNum(v);
			return;
		}
	}
}

void ShowChoiceManager::SetChoiceWeaponsGraph(const int& passiveGraphHandle)
{
	for (int i = 0; i < kWeaponMax; i++) {
		if (m_pChoiceWeapons[i]->GetChoiceGraph() != -1) {
			if (m_pChoiceWeapons[i]->GetChoiceGraph() == passiveGraphHandle) {
				return;
			}
			else
			{
				continue;
			}
		}
		else
		{
			m_pChoiceWeapons[i]->SetChoiceGraph(passiveGraphHandle);
			return;
		}
	}
}

void ShowChoiceManager::SetChoicePassivesGraph(const int& passiveGraphHandle)
{
	for (int i = 0; i < kPassiveMax; i++) {
		if (m_pChoicePassives[i]->GetChoiceGraph() != -1) {
			if (m_pChoicePassives[i]->GetChoiceGraph() == passiveGraphHandle) {
				return;
			}
			else
			{
				continue;
			}
		}
		else
		{
			m_pChoicePassives[i]->SetChoiceGraph(passiveGraphHandle);
			return;
		}
	}
}

void ShowChoiceManager::SetChoiceWeaponsLevel(const int& choiceLevel, const int& v)
{
	for (int i = 0; i < kWeaponMax; i++)
	{
		if (m_pChoiceWeapons[i]->GetChoiceNum() != v)continue;
		else
		{
			m_pChoiceWeapons[i]->SetChoiceLevel(choiceLevel);
			return;
		}
	}
}

void ShowChoiceManager::SetChoicePassivesLevel(const int& choiceLevel, const int& v)
{
	for (int i = 0; i < kPassiveMax; i++)
	{
		if (m_pChoicePassives[i]->GetChoiceNum() != v)continue;
		else
		{
			m_pChoicePassives[i]->SetChoiceLevel(choiceLevel);
			return;
		}
	}
}

