#include "Arrow.h"
#include <DxLib.h>

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
#include"../students/oreistake/Player.h"



namespace
{

	const char* const kGraphPath = ".\\Resource\\image\\Arrow.png";

}


Arrow::Arrow():
	m_graphHandle(),
	m_range(),
	m_coolTime(),
	m_appearTime(),
	m_angle(),
	m_pPlayerMove(nullptr)
{
	m_pPlayerMove = new PlayerMove();
}

Arrow::Arrow(
	std::string name,
	float damage,
	float range,
	float attackRange,
	int coolTime,
	int weaponNum,
	Vector2 playerPos)
{
}

void Arrow::Init()
{
	m_graphHandle = LoadGraph(kGraphPath);
}

void Arrow::End()
{

}

void Arrow::Update()
{
	
}

void Arrow::Draw()
{
	//DrawGraph();
}

