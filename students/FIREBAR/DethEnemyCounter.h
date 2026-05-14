#pragma once

class DeathEnemyCounter
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DeathEnemyCounter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeathEnemyCounter() = default;

	//ハッピーセット
	void Init();
	void End();
	void Draw();
	//

	/// <summary>
	/// カウントアップ用
	/// </summary>
	void CountUP();

private:
	int m_gHandle;
	int m_enemyCount;
};

