#pragma once
#include "Vector2.h"
#include<vector>
class Items
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Items() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Items() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 定位置生成
	/// </summary>
	/// <param name="position">position</param>
	/// <returns></returns>
	bool Create(const Vector2& position);

	/// <summary>
	/// ランダム生成
	/// </summary>
	/// <param name="Length">ステージのサイズ</param>
	/// <returns></returns>
	bool RamdumCreate(float Length);

	/// <summary>
	/// 生成物削除
	/// </summary>
	/// <param name="index"></param>
	void Remove(int index);

	/// <summary>
	/// アイテム数取得
	/// </summary>
	/// <returns></returns>
	int GetItemNum() const { return m_itemNum; }

	/// <summary>
	/// 当たっているか
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="playerSize">プレイヤー画像サイズ</param>
	void CheckCollision(const Vector2& playerPos, float playerSize);

public:
	/// <summary>
	/// 可変長配列宣言
	/// </summary>
	std::vector<Vector2> m_itemPos;

	/// <summary>
	/// デバッグ
	/// </summary>
	void DebugDraw() const;
private:
	/// <summary>
	/// アイテム数
	/// </summary>
	int m_itemNum;

	/// <summary>
	/// 画像ハンドル
	/// </summary>
	int m_graphHandle;

};

