#pragma once

#include <array>
#include <memory>

namespace {

	/// <summary>
	/// 武器の数
	/// </summary>
	enum WeaponNum {
		kWeaponZero = 0,
		kWeaponOne,
		kWeaponTwo,
		kWeaponThree,
		kWeaponMax
	};

	/// <summary>
	/// 能力の数
	/// </summary>
	enum PassiveNum {
		kPassiveZero = 0,
		kPassiveOne,
		kPassiveTwo,
		kPassiveThree,
		kPassiveMax
	};

	/// <summary>
	/// 行の数
	/// </summary>
	enum ColumnNum {
		kColumnZero = 0,
		kColumnOne,
		kColumnMax
	};
}

class ShowChoice;

class ShowChoiceManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShowChoiceManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ShowChoiceManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	//void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 枠に表示する武器の情報を設定する関数
	/// </summary>
	/// <param name="v">武器番号</param>
	/// <param name="weaponGraphHandle">武器の画像ハンドル</param>
	/// <param name="choiceLevel">武器のレベル</param>
	void SetChoiceWeapons(const int& v, 
		const int& weaponGraphHandle, 
		const int& choiceLevel);
	
	/// <summary>
	/// 枠に表示する能力の情報を設定する関数
	/// </summary>
	/// <param name="v">能力番号</param>
	/// <param name="passiveGraphHandle">能力の画像ハンドル</param>
	/// <param name="choiceLevel">能力のレベル</param>
	void SetChoicePassives(const int& v,
		const int& passiveGraphHandle, 
		const int& choiceLevel);

private:

	/// <summary>
	/// 枠に表示する武器の番号を設定する関数
	/// </summary>
	/// <param name="v">武器の番号</param>
	void SetChoiceWeaponsNum(const int& v);

	/// <summary>
	/// 枠に表示する能力の番号を設定する関数
	/// </summary>
	/// <param name="v">能力の番号</param>
	void SetChoicePassivesNum(const int& v);

	/// <summary>
	/// 枠に表示する武器の画像ハンドルを設定する関数
	/// </summary>
	/// <param name="weaponGraphHandle">武器の画像ハンドル</param>
	void SetChoiceWeaponsGraph(const int& weaponGraphHandle);

	/// <summary>
	/// 枠に表示する能力の画像ハンドルを設定する関数
	/// </summary>
	/// <param name="passiveGraphHandle">能力の画像ハンドル</param>
	void SetChoicePassivesGraph(const int& passiveGraphHandle);

	/// <summary>
	/// 枠に表示する武器のレベルを設定する関数
	/// </summary>
	/// <param name="choiceLevel">武器のレベル</param>
	/// <param name="v">武器の番号</param>
	void SetChoiceWeaponsLevel(const int& choiceLevel, const int& v);

	/// <summary>
	/// 枠に表示する能力のレベルを設定する関数
	/// </summary>
	/// <param name="choiceLevel">能力のレベル</param>
	/// <param name="v">能力の番号</param>
	void SetChoicePassivesLevel(const int& choiceLevel, const int& v);

private:

	/// <summary>
	/// 枠に表示する武器のクラスのポインタ
	/// </summary>
	std::array<std::unique_ptr<ShowChoice>, static_cast<int>(kWeaponMax)>m_pChoiceWeapons;

	/// <summary>
	/// 枠に表示する能力のクラスのポインタ
	/// </summary>
	std::array<std::unique_ptr<ShowChoice>, static_cast<int>(kPassiveMax)>m_pChoicePassives;

};

