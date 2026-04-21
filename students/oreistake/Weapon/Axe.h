#pragma once

#include <string>
#include <memory>
#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"


class Axe
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Axe();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="name">武器名</param>
	/// <param name="damage">武器の与ダメージ</param>
	/// <param name="range">武器の射程</param>
	/// <param name="attackRange">武器の攻撃範囲</param>
	/// <param name="coolTime">武器のクールタイム</param>
	/// <param name="weaponNum">武器ナンバー</param>
	/// <param name="playerPos">プレイヤーの座標</param>
	Axe(
		std::string name,
		float damage,
		float range,
		float attackRange,
		int coolTime,
		int weaponNum,
		Vector2 playerPos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Axe() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 引数ありの初期化
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	void Init(Vector2 playerPos);

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 武器名を取得する
	/// </summary>
	/// <returns>武器名</returns>
	const std::string GetWeaponName()const { return m_name; }

	/// <summary>
	/// 武器ナンバーを取得する
	/// </summary>
	/// <returns>武器ナンバー</returns>
	const int& GetWeaponNum()const { return m_weaponNum; }

	/// <summary>
	/// レクト取得
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// 当たり判定取得
	/// </summary>
	/// <returns></returns>
	Collision* GetCollision() const { return m_pCollision.get(); }

	/// <summary>
	/// 与ダメージを設定する
	/// </summary>
	/// <param name="damage">武器の与ダメージ</param>
	void SetDamage(float damage) { m_damage = damage; }

	/// <summary>
	/// 攻撃範囲を設定する
	/// </summary>
	/// <param name="attackRange">武器の攻撃範囲</param>
	void SetAttackRange(float attackRange) { m_attackRange = attackRange; }

	/// <summary>
	/// クールタイムを設定する
	/// </summary>
	/// <param name="coolTime">武器のクールタイム</param>
	void SetCoolTime(int coolTime) { m_coolTime = coolTime; }

	/// <summary>
	/// 斧の動きの基準になるプレイヤーの座標を設定する
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	void SetPlayerPos(Vector2 playerPos) { m_playerPosX = playerPos.x; m_playerPosY = playerPos.y; }

private:

	/// <summary>
	/// 刀の内部更新処理
	/// </summary>
	void UpdateAxe();

	/// <summary>
	/// 刀の内部描画処理
	/// </summary>
	void DrawAxe();

	/// <summary>
	/// デバッグ用更新処理
	/// ・Fキーでスケールダウン
	/// ・Gキーでスケールアップ
	/// </summary>
	void DebugUpdate();

	/// <summary>
	/// デバッグ用描画処理
	/// </summary>
	void DebugDraw();

private:

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 武器名
	/// </summary>
	std::string m_name;

	/// <summary>
	/// 武器の与ダメージ
	/// </summary>
	float m_damage;

	/// <summary>
	/// 武器の射程
	/// </summary>
	float m_range;

	/// <summary>
	/// 武器の攻撃範囲
	/// </summary>
	float m_attackRange;

	/// <summary>
	/// 武器のクールタイム
	/// </summary>
	int m_coolTime;

	/// <summary>
	/// 武器ナンバー
	/// </summary>
	int m_weaponNum;

	/// <summary>
	/// 武器の出現時間
	/// </summary>
	int m_appearTime;

	/// <summary>
	/// クールタイム計測用変数
	/// </summary>
	int m_frameCount;

	/// <summary>
	/// 出現時間計測用変数
	/// </summary>
	int m_appearCount;

	/// <summary>
	/// 画面に武器が描画されるかどうか
	/// </summary>
	bool m_isAppear;

	/// <summary>
	/// プレイヤーのX座標
	/// </summary>
	float m_playerPosX;

	/// <summary>
	/// プレイヤーのY座標
	/// </summary>
	float m_playerPosY;

	/// <summary>
	/// 武器が表示される座標の回転角度
	/// </summary>
	float m_rotateAngle;

	/// <summary>
	/// 武器自体の角度
	/// </summary>
	float m_angle;

	/// <summary>
	/// 武器を回転描画する画面上の中心X座標
	/// </summary>
	float m_katanaTerminalPosX;

	/// <summary>
	/// 武器を回転描画する画面上の中心Y座標
	/// </summary>
	float m_katanaTerminalPosY;

	/// <summary>
	/// 武器の現在の攻撃範囲
	/// </summary>
	double m_scale;

	/// <summary>
	/// 当たり判定ユニークポインタ
	/// </summary>
	std::unique_ptr<Collision>m_pCollision;
};
