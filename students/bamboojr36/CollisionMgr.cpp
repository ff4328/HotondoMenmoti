#include "CollisionMgr.h"
#include "Collision.h"

#include "../FIREBAR/MagicBottle.h"
#include "../mcd6752Tuyoshi/Katana/Katana.h"
#include "../oreistake/Weapon/Arrow.h"
#include "../oreistake/Weapon/Axe.h"

#include "../Yama596/Enemys/Bat.h"
#include "../Yama596/Enemys/Goblin.h"
#include "../Yama596/Enemys/Mushroom.h"
#include "../Yama596/Enemys/Skeleton.h"

CollisionMgr::CollisionMgr() :
	m_Collision(nullptr),
	m_magic(nullptr),
	m_katana(nullptr),
	m_arrow(nullptr),
	m_axe(nullptr),
	m_bats(nullptr),
	m_goblins(nullptr),
	m_mushrooms(nullptr),
	m_skeltons(nullptr),
	m_bat(nullptr),
	m_goblin(nullptr),
	m_mushroom(nullptr),
	m_skelton(nullptr)
{
	m_Collision = std::make_unique <Collision>();
	m_magic = std::make_unique <MagicBottle>();
	m_katana = std::make_unique <Katana>();
	m_arrow = std::make_unique <Arrow>();
	m_axe = std::make_unique <Axe>();
	m_bats = std::make_unique <Bat>();
	m_goblins = std::make_unique <Goblin>();
	m_mushrooms = std::make_unique <Mushroom>();
	m_skeltons = std::make_unique <Skeleton>();
	m_bat= new BatManager();
	m_goblin = new GoblinManager();
	m_mushroom = new MushroomManager();
	m_skelton = new SkeletonManager();
}

void CollisionMgr::Init() {

}

void CollisionMgr::End() {

	m_bat->End();
	delete m_bat;
	m_bat = nullptr;

	m_goblin->End();
	delete m_goblin;
	m_goblin = nullptr;

	m_mushroom->End();
	delete m_mushroom;
	m_mushroom = nullptr;

	m_skelton->End();
	delete m_skelton;
	m_skelton = nullptr;
}

void CollisionMgr::Update() {
}

void CollisionMgr::Bats(WeaponStatus* katana) {
	printfDx("ASDFGHJK");
	m_bat->CheckHitWeapon(katana->CheckHitEnemy(1),100);
	return;
}

void CollisionMgr::Goblins() {

	if (m_Collision->CheckRectCommon(m_katana->GetCheckRect(), m_goblins->GetCheckRect())) {
		m_goblin->CheckHitAttack(100);
		return;
	}
	if (m_Collision->CheckRectCommon(m_arrow->GetCheckRect(), m_goblins->GetCheckRect())) {
		m_goblin->CheckHitAttack(100);
		printfDx("FFFFFFFFFFFFFFFFFFF");
	}
	if (m_Collision->CheckRectCommon(m_axe->GetRects(), m_goblins->GetCheckRect())) {
		m_goblin->CheckHitAttack(100);
		printfDx("J");
	}
	if (m_Collision->CheckRectCommon(m_magic->GetCheckRect(), m_goblins->GetCheckRect())) {
		m_goblin->CheckHitAttack(100);
		printfDx("N");
	}


}

void CollisionMgr::Mushrooms() {
	if (m_Collision->CheckRectCommon(m_katana->GetCheckRect(), m_mushrooms->GetCheckRect())) {
		m_mushroom->CheckHitAttack(100);
		printfDx("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n");
	}
	if (m_Collision->CheckRectCommon(m_magic->GetCheckRect(), m_mushrooms->GetCheckRect())) {
		m_mushroom->CheckHitAttack(100);
		printfDx("O");
	}
	if (m_Collision->CheckRectCommon(m_arrow->GetCheckRect(), m_mushrooms->GetCheckRect())) {
		m_mushroom->CheckHitAttack(100);
		printfDx("GGGGGGGGGGGGGGGGGG");
	}
	if (m_Collision->CheckRectCommon(m_axe->GetRects(), m_mushrooms->GetCheckRect())) {
		m_mushroom->CheckHitAttack(100);
		printfDx("K");
	}

}

void CollisionMgr::Skeletons() {

	if (m_Collision->CheckRectCommon(m_katana->GetCheckRect(), m_skeltons->GetCheckRect())) {
		m_skelton->CheckHitAttack(100);
		printfDx("DDDDDDDDDDDDDDDDDDDDDDDDDDD\n");
	}
	if (m_Collision->CheckRectCommon(m_arrow->GetCheckRect(), m_skeltons->GetCheckRect())) {
		m_skelton->CheckHitAttack(100);
		printfDx("HHHHHHHHHHHHHHHHHHH");
	}
	if (m_Collision->CheckRectCommon(m_axe->GetRects(), m_skeltons->GetCheckRect())) {
		m_skelton->CheckHitAttack(100);
		printfDx("L");
	}
	if (m_Collision->CheckRectCommon(m_magic->GetCheckRect(), m_skeltons->GetCheckRect())) {
		m_skelton->CheckHitAttack(100);
		printfDx("P");
	}
}
