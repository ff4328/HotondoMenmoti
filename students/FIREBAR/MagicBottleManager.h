#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "../students/bamboojr36/Collision.h"

// 前方宣言
	struct Vector2;
	class MagicBottle;
	class PlayerMove;

	class MagicBottleManager
	{
	public:

		// 可変長配列は要素数は持たなくてもいい
		// static constexpr int kMaxGrassNum = 300000;

		// Grassクラスの生ポインタからスマートポインタに変えたので
		// デストラクタをヘッダーで完結させるのはよくない
		// 対応方法をしては.cpp側に定義をうつす
		// ヘッダー定義くぉ記載すると、ヘッダーでGrassの内容が必要になるため
		MagicBottleManager();
		MagicBottleManager(PlayerMove* pPlayer);
		~MagicBottleManager();

		void Init();
		void End();
		void Update();
		void Draw();

		/// <summary>
		/// 指定した座標にGrassクラスのインスタンスを生成
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		bool Create(std::string name,
			float damage,
			float range,
			float attackRange,
			int coolTime,
			int weaponNum,
			Vector2 playerPos);

		Rect GetCheckRect();

		/// <summary>
		/// ランダムの座標にGrassクラスのインスタンスを生成
		/// </summary>
		/// <param name="areaLength">ランダムで生成するエリアの大きさ</param>
		/// <returns></returns>
		//bool RandomCreate(float areaLength);

		/// <summary>
		/// 指定したインデックスの草を削除
		/// </summary>
		/// <param name="index"></param>
		//void Remove(int index);

		/// <summary>
		/// 草の数を取得
		/// </summary>
		/// <returns></returns>
		//int GetGrassCount() const { return m_grasses.size(); }

		/// <summary>
		/// 引数の球と草が当たっているか調べる
		/// </summary>
		/// <param name="other"></param>
		//void CheckHitSphere(Collision::Sphere other);

	private:

		/// <summary>
		/// デバッグ情報を表示する
		/// </summary>
		//void DebugDraw();

	private:

		/// <summary>
		/// 草の配列
		/// 可変長配列の宣言
		/// std::vector<どの型の配列> 可変長配列名;
		/// </summary>
		// std::array<Grass*, kMaxGrassNum> m_grasses;
		// std::vector<Grass*> m_grasses;
		std::vector<std::unique_ptr<MagicBottle>> m_MagicBottle;

		/// <summary>
		/// 草の数
		/// </summary>
		/// 可変長配列の場合なくても制御できる
		// int m_grassCount;

		/// <summary>
		/// 画像のハンドル
		/// </summary>
		int m_graphHandle;

		PlayerMove* m_pPlayer;
	};