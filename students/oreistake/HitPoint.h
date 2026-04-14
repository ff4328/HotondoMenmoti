#pragma once


class HitPoint
{
	//=========================================
	// メンバ関数
	//=========================================
public:

	HitPoint();
	~HitPoint() = default;


	void Init();
	void Update();
	void Draw();
	void Finalize();
	void DebugShow();

	// ダメージ処理
	void Damage(int value);
	// 回復処理
	void Heal(int value);

	// 死亡チェック
	// HPが0になっていたらtrueを返す
	bool IsDead();

	// HPゲージの座標更新
	// 毎フレーム呼ぶことを前提とする　呼ばないとオブジェクトからずれる
	void SetPosition(float _posX, float _posY);

	// 最大HPの設定
	void SetHPMax(int value);

private:
	//=========================================
	// メンバ変数
	//=========================================

	// HPゲージを表示する座標
	float posX;
	float posY;

	// ゲージを表示するために補正した座標
	float gaugePosX;
	float gaugePosY;

	int hp;			// 現在のHP
	int hpMax;		// 最大HP

	// HPゲージに関する色
	unsigned int gaugeFrameColor;		// HPゲージの枠の色
	unsigned int gaugeNormalColor;		// HPゲージの色 通常時
	unsigned int gaugeDeathColor;		// HPゲージの色 瀕死時
	unsigned int gaugeBack;				// HPゲージの背景の色



};

