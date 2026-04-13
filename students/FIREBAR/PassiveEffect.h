#pragma once

class PassiveEffect
{
public:
	/// <summary>
	/// PassiveEffectのコンストラクタ
	/// </summary>
	PassiveEffect();

	/// <summary>
	/// PassiveEffectのデストラクタ
	/// </summary>
	~PassiveEffect() = default;

	void Init();
	void End();
	void Update();
	void Draw();

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

	/// <summary>
	/// プレイヤーの移動速度増加
	/// </summary>
	/// <param name="playerStatus">プレイヤー</param>
	void AddPlayerSpeed();

	/// <summary>
	/// プレイヤーの最大HP増加
	/// </summary>
	/// <param name="playerStatus">プレイヤー</param>
	void AddPlayerHp();
private:
};