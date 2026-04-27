#pragma once
#include "Collision.h"
#include <memory>

#include "../FIREBAR/MagicBottle.h"
#include "../mcd6752Tuyoshi/Katana/Katana.h"
#include "../oreistake/Weapon/Arrow.h"
#include "../oreistake/Weapon/Axe.h"

#include "../Yama596/Enemys/Bat.h"
#include "../Yama596/Enemys/Goblin.h"
#include "../Yama596/Enemys/Mushroom.h"
#include "../Yama596/Enemys/Skeleton.h"

#include "../Yama596/Enemys/BatManager.h"
#include "../Yama596/Enemys/GoblinManager.h"
#include "../Yama596/Enemys/MushroomManager.h"
#include "../Yama596/Enemys/SkeletonManager.h"

#include "../FIREBAR/WeaponManager.h"

class CollisionMgr
{
public:
	CollisionMgr();
	~CollisionMgr() = default;

	void Init();
	void End();
	void Update();

	void Bats(WeaponStatus* katana);
	void Goblins();
	void Mushrooms();
	void Skeletons();

private:
	std::unique_ptr<Collision>m_Collision;

	std::unique_ptr<MagicBottle>m_magic;
	std::unique_ptr<Katana>m_katana;
	std::unique_ptr<Arrow>m_arrow;
	std::unique_ptr<Axe>m_axe;
	std::unique_ptr<Bat>m_bats;
	std::unique_ptr<Goblin>m_goblins;
	std::unique_ptr<Mushroom>m_mushrooms;
	std::unique_ptr<Skeleton>m_skeltons;
	BatManager* m_bat;
	GoblinManager* m_goblin;
	MushroomManager* m_mushroom;
	SkeletonManager* m_skelton;


};

