#pragma once
#include "Vector2.h"
#include <vector>
#include <memory>
#include "DxLib.h"
#include "Heal.h"
#include "Magnet.h"
#include "Bomb.h"
#include "EXPItem.h"
#include "../oreistake/Player.h"
#include "Collision.h"

class Collision;
class PlayerStatus;

class Items
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Items();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	Items(PlayerMove* player);

	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="playerstatus">プレイヤーステータス</param>
	Items(PlayerMove* player, PlayerStatus* playerstatus);

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
	/// デバッグ
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 経験値ゲッター
	/// </summary>
	/// <returns></returns>
	bool GetEXP() const { return m_getexp; }
	
	/// <summary>
	/// 経験値セッター
	/// </summary>
	/// <param name="getexp"></param>
	void Setexp(bool getexp) { m_getexp = getexp; }

	/// <summary>
	/// プレイヤーゲッター
	/// </summary>
	/// <returns></returns>
	bool GetPlayer() const { return m_Player; }

	/// <summary>
	/// ボムが起動したか
	/// </summary>
	/// <returns></returns>
	bool BombTrigger();

private:

	/// <summary>
	/// 回復ハンドル
	/// </summary>
	int m_graphHandleHeal;
	
	/// <summary>
	/// 回収ハンドル
	/// </summary>
	int m_graphHandleMagnet;
	
	/// <summary>
	/// 全滅ハンドル
	/// </summary>
	int m_graphHandleBomb;
	
	/// <summary>
	/// 経験値ハンドル
	/// </summary>
	int m_graphHandleEXPItem;
	
	/// <summary>
	/// プレイヤーハンドル
	/// </summary>
	int m_graphHandlePlayer;
	
	/// <summary>
	/// 経験値の取得
	/// </summary>
	bool m_getexp = false;
	
	/// <summary>
	/// プレイヤーかどうか
	/// </summary>
	bool m_Player = false;
	
	/// <summary>
	/// 入手したかどうか
	/// </summary>
	bool Get = false;
	
	/// <summary>
	/// カウント
	/// </summary>
	int Count = 0;

	/// <summary>
	///	ボムとプレイヤーが当たったかどうか
	/// </summary>
	bool m_bombTrigger;

	/// <summary>
	/// 回復ユニークポインタ
	/// </summary>
	std::unique_ptr<Heal> m_heal;
	
	/// <summary>
	/// 回収ユニークポインタ
	/// </summary>
	std::unique_ptr<Magnet>m_magnet;
	
	/// <summary>
	/// 全滅ユニークポインタ
	/// </summary>
	std::unique_ptr<Bomb>m_bomb;
	
	/// <summary>
	/// 経験値ユニークポインタ
	/// </summary>
	std::unique_ptr<EXPItem>m_EXPItem;
	
	/// <summary>
	/// プレイヤー生ポインタ
	/// </summary>
	PlayerMove* m_player;

	/// <summary>
	/// プレイヤーステータス生ポインタ
	/// </summary>
	PlayerStatus* m_pPlayerStatus;
	
	/// <summary>
	/// 当たり判定ユニークポインタ
	/// </summary>
	std::unique_ptr<Collision>m_collision;

	/// <summary>
	/// アイテムの可変長配列
	/// </summary>
	std::vector<std::unique_ptr<EXPItem>> m_expItems;

};