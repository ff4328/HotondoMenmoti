#pragma once
class LotteryPusive
{
public:
	enum Pusive
	{
		ATTACKRANGE,
		ATTACKSPEED,
		MAXHPUP,
		MOVESPEED,
		MAXPUSIVE,
	};

public:
	LotteryPusive();
	~LotteryPusive() = default;

	void RandomLottery();
	void Draw();

private:
	int slot[3];
};