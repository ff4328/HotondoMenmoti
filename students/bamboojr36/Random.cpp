#include "Random.h"
#include <random>

void MyRandom::Init()
{
	Engine().seed(std::random_device{}());
}

int MyRandom::Int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(Engine());
}

std::mt19937& MyRandom::Engine()
{
	static std::mt19937 engine{ std::random_device{}() };
	return engine;
}
