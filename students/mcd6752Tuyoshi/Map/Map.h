#pragma once

#include <vector>
#include <string>

namespace {

	constexpr int kMapChipChangeSize = 32;
	constexpr int kMapChipOriginSize = 32;

	/// <summary>
	/// 画像ごとのナンバー(現在未使用)
	/// </summary>
	enum {
		kGraphZero = 0,
		kGraphOne,
		kGraphTwo,
		kGraphThree,
		kGraphFour,
		kGraphMax
	};

	/// <summary>
	/// マップチップの種類の数
	/// </summary>
	enum {
		kMapTypeNum = 1024
	};

	/// <summary>
	/// ステージ数
	/// </summary>
	enum
	{
		kStageZero = 0,
		kStageMax
	};
}

/// <summary>
/// マップのクラス
/// シーンにポインタ変数を作って使ってください
/// </summary>
class Map
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Map();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="stageID">ステージID</param>
	Map(int stageID);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Map() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新(現在未使用)
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 横軸のマップチップの総数を取得する
	/// </summary>
	/// <returns>横軸のマップチップの総数幅</returns>
	const int& GetMapChipNumX()const { return m_mapChipNumX; }

	/// <summary>
	/// 縦軸のマップチップの総数を取得する
	/// </summary>
	/// <returns>縦軸のマップチップの総数</returns>
	const int& GetMapChipNumY()const { return m_mapChipNumY; }

	/// <summary>
	/// マップの幅を取得する
	/// </summary>
	/// <returns>マップの幅</returns>
	const float& GetMapSizeX()const { return m_mapSizeX; }

	/// <summary>
	/// マップの高さを取得する
	/// </summary>
	/// <returns>マップの高さ</returns>
	const float& GetMapSizeY()const { return m_mapSizeY; }

	/// <summary>
	/// マップチップのサイズを取得する
	/// </summary>
	/// <returns></returns>
	const int& GetMapChipChangeSize()const { return kMapChipChangeSize; }

private:

	/// <summary>
	/// CSVデータをマップデータとして読み込む
	/// </summary>
	/// <param name="stageNum">ステージID</param>
	/// <returns>読み込めたか</returns>
	bool LoadCSVToMapData(int stageNum);

	/// <summary>
	/// 1行の文字列をカンマで分割する
	/// </summary>
	/// <param name="str">分割させたい文字列</param>
	/// <param name="separate">何の文字で分裂させるのかを指定(ここでは",")</param>
	/// <returns>分割した配列</returns>
	std::vector<std::string>Split(const std::string& str, char separate);

	/// <summary>
	///  CSVデータを読み込んでマップのサイズを調べる
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>読み込めたか</returns>
	bool CheckMapSize(const char* fileName);

	/// <summary>
	/// マップデータのクリーンアップ
	/// </summary>
	void CleanUp();

#ifdef _DEBUG
	/// <summary>
	/// デバッグ情報表示
	/// </summary>
	void DebugDraw();

#endif // _DEBUG


private:

	/// <summary>
	/// グラフィックハンドルの配列
	/// </summary>
	int m_graphHandles[kMapTypeNum];

	/// <summary>
	/// マップチップの拡大率
	/// </summary>
	float m_chipScaleRate;

	/// <summary>
	/// 横軸のマップチップの総数
	/// </summary>
	int m_mapChipNumX;

	/// <summary>
	/// 縦軸のマップチップの総数
	/// </summary>
	int m_mapChipNumY;

	float m_mapSizeX;

	float m_mapSizeY;

	/// <summary>
	/// マップデータ
	/// </summary>
	int** m_ppMapData;

	/// <summary>
	/// 読み込むマップのステージID
	/// </summary>
	int m_stageID;
};

