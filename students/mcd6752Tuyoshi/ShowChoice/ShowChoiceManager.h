#pragma once

#include <array>
#include <memory>

namespace {

	enum WeaponNum {
		kWeaponZero = 0,
		kWeaponOne,
		kWeaponTwo,
		kWeaponThree,
		kWeaponMax
	};

	enum PassiveNum {
		kPassiveZero = 0,
		kPassiveOne,
		kPassiveTwo,
		kPassiveThree,
		kPassiveMax
	};

	enum ColumnNum {
		kColumnZero = 0,
		kColumnMax
	};
}

class ShowChoice;

class ShowChoiceManager
{
public:

	ShowChoiceManager();

	~ShowChoiceManager();

	void Init();

	void End();

	//void Update();

	void Draw();

	void SetChoiceWeapons(const int& v, 
		const int& passiveGraphHandle, 
		const int& choiceLevel);
	
	void SetChoicePassives(const int& v,
		const int& passiveGraphHandle, 
		const int& choiceLevel);

private:

	void SetChoiceWeaponsNum(const int& v);

	void SetChoicePassivesNum(const int& v);

	void SetChoiceWeaponsGraph(const int& passiveGraphHandle);

	void SetChoicePassivesGraph(const int& passiveGraphHandle);

	void SetChoiceWeaponsLevel(const int& choiceLevel, const int& v);

	void SetChoicePassivesLevel(const int& choiceLevel, const int& v);

private:

	std::array<std::unique_ptr<ShowChoice>, static_cast<int>(kWeaponMax)>m_pChoiceWeapons;

	std::array<std::unique_ptr<ShowChoice>, static_cast<int>(kPassiveMax)>m_pChoicePassives;

};

