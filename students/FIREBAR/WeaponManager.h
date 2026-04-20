#pragma once
#include <string>
#include <vector>
#include <iostream>
//#include "../oreistake/Weapon.h"

/// <summary>
/// 武器構造体
/// </summary>
struct Weapons
{
	//武器の名前
	std::string name;

	//武器のダメージ
	float damage;

	//武器の射程距離
	float range;

	//武器の攻撃範囲
	float attackRange;

	//武器の攻撃速度
	int coolDown;
};

class WeaponStatus
{
public:
	/// <summary>
	/// WeaponManagerのコンストラクタ
	/// </summary>
	WeaponStatus();

	/// <summary>
	/// WeaponManagerのデストラクタ
	/// </summary>
	~WeaponStatus() = default;

	//////////////いつのもセット
	void Init();
	void End();
	void Draw() const;
	void Update();
	//////////////

	/// <summary>
	/// 武器詳細表示
	/// </summary>
	void DisplayWeapons() const;

	/// <summary>
	/// 武器の初期ステータス設定
	/// </summary>
	void SetWeaponStatus();

	/// <summary>
	/// 何番目の武器のクールダウンを持ってくるか
	/// </summary>
	/// <param name="num">武器の番号
	/// ０：弓、１：刀、２：斧、３：魔法</param>
	/// <returns>対応する武器のステータス</returns>
	int GetWeaponCoolDown(int num) { return weapons[num].coolDown; }

	/// <summary>
	/// 何番目の武器の攻撃範囲を持ってくるか
	/// </summary>
	/// <param name="num">武器の番号
	/// ０：弓、１：刀、２：斧、３：魔法</param>
	/// <returns>対応する武器のステータス</returns>
	int GetWeaponAttackRange(int num) { return weapons[num].attackRange; }

	/// <summary>
	///	攻撃力増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	void AddAttackSpeed();

	/// <summary>
	/// 攻撃範囲増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	void AddAttackRange();

	Weapons WeaponNum[4];

private:

	std::vector<Weapons> weapons;
};