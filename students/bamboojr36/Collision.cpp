#include "Collision.h"
#include <cassert>
#include <DxLib.h>

bool Collision::CheckCollision(const Collision& other) const
{
	const float checkBox = dynamic_cast<const Collision&>(other).m_size.x / 2 + m_size.x / 2;

	assert(checkBox > 0 && "Collision:衝突判定のサイズが0以下");

	if(m_position.x - checkBox < other.m_position.x && m_position.x + checkBox > other.m_position.x)return false;
	if(m_position.y - checkBox < other.m_position.y && m_position.y + checkBox > other.m_position.y)return false;

	return true;
}

bool Collision::CheckPointInRange(float posX, float posY, Rect box)
{
	if (!(posX >= box.left))		return false;
	if (!(posX <= box.right))		return false;
	if (!(posY >= box.top))		return false;
	if (!(posY <= box.bottom))		return false;

	// ここまで来たら座標は矩形の中にあるのでtrueを返す
	return true;
}

bool Collision::CheckRectCommon(Rect myBox, Rect checkBox)
{// 当たっているかチェックするフラグ 当たっていたらtrueにする
	bool checkFlag = false;

	// myRectの座標とcheckRectが当たっているかチェック
	if (CheckPointInRange(myBox.left, myBox.top, checkBox)) checkFlag = true;
	if (CheckPointInRange(myBox.left, myBox.bottom, checkBox)) checkFlag = true;
	if (CheckPointInRange(myBox.right, myBox.top, checkBox)) checkFlag = true;
	if (CheckPointInRange(myBox.right, myBox.bottom, checkBox)) checkFlag = true;

	// myRectとcheckRectの座標が当たっているかチェック
	if (CheckPointInRange(checkBox.left, checkBox.top, myBox)) checkFlag = true;
	if (CheckPointInRange(checkBox.left, checkBox.bottom, myBox)) checkFlag = true;
	if (CheckPointInRange(checkBox.right, checkBox.top, myBox)) checkFlag = true;
	if (CheckPointInRange(checkBox.right, checkBox.bottom, myBox)) checkFlag = true;

	printfDx("%d\n", checkFlag);

	// フラグを返す
	return checkFlag;
}

void Collision::DebugDraw(Rect myBox, Rect checkBox)
{
	printfDx("%d\n", CheckRectCommon(myBox, checkBox));
}
