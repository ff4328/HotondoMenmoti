#pragma once

class DeathEnemyCounter
{
public:
	DeathEnemyCounter();
	~DeathEnemyCounter() = default;

	void Init();
	void End();
	void Update();
	void Draw();

	void CountUP();

private:
	int m_gHandle;
	int m_enemyCount;

};

