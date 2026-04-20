#include "Map.h"

#include <DxLib.h>

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace {

	const char* const kGPDeepForestA1 = ".\\Resource\\Map\\DeepForest\\DeepForest-A1.png";
	const char* const kGPDeepForestA2 = ".\\Resource\\Map\\DeepForest\\DeepForest-A2.png";
	const char* const kGPDeepForestA5 = ".\\Resource\\Map\\DeepForest\\DeepForest-A5.png";
	const char* const kGPDeepForestB = ".\\Resource\\Map\\DeepForest\\DeepForest-B.png";
	const char* const kGPRuinF = ".\\Resource\\Map\\DeepForest\\Ruin-F.png";
}

/////////////////////////////////////////////////////////////////////////////////////////

Map::Map():
	m_graphHandles{},
	m_chipScaleRate(static_cast<float>(kMapChipChangeSize) / 
		static_cast<float>(kMapChipOriginSize)),
	m_mapChipNumX(0),
	m_mapChipNumY(0),
	m_mapSizeX(0),
	m_mapSizeY(0),
	m_ppMapData(0),
	m_stageID(kStageZero)
{
}

void Map::Init()
{
	// グラフィックハンドルの初期化
	for (int i = 0; i < kMapTypeNum; i++) {

		m_graphHandles[i] = 0;
	}

	int buf[256];

	// 暗い森A1の読み込み
	LoadDivGraph(kGPDeepForestA1,
		192, 16, 12,
		kMapChipChangeSize, kMapChipChangeSize, m_graphHandles);

	// 暗い森A2の読み込み
	LoadDivGraph(kGPDeepForestA2,
		192, 16, 12,
		kMapChipChangeSize, kMapChipChangeSize, buf);

	// 今まで取り込んだ要素数を飛ばしてbufからgraphHandleに取り込む
	for (int i = 0; i < 192; i++) {
		m_graphHandles[i + 192] = buf[i];
	}

	// 暗い森A5の読み込み
	LoadDivGraph(kGPDeepForestA5,
		128, 8, 16,
		kMapChipChangeSize, kMapChipChangeSize, buf);

	// 今まで取り込んだ要素数を飛ばしてbufからgraphHandleに取り込む
	for (int i = 0; i < 128; i++) {
		m_graphHandles[i + 384] = buf[i];
	}

	// 暗い森Bの読み込み
	LoadDivGraph(kGPDeepForestB,
		256, 16, 16,
		kMapChipChangeSize, kMapChipChangeSize, buf);

	// 今まで取り込んだ要素数を飛ばしてbufからgraphHandleに取り込む
	for (int i = 0; i < 256; i++) {
		m_graphHandles[i + 512] = buf[i];
	}

	// 遺跡の読み込み
	LoadDivGraph(kGPRuinF,
		256, 16, 16,
		kMapChipChangeSize, kMapChipChangeSize, buf);

	// 今まで取り込んだ要素数を飛ばしてbufからgraphHandleに取り込む
	for (int i = 0; i < 256; i++) {
		m_graphHandles[i + 768] = buf[i];
	}

	// IDの設定
	m_stageID = kStageZero;

	// CSVデータを読み込む
	LoadCSVToMapData(m_stageID);
}

void Map::End()
{
	// グラフィックハンドルの破棄
	for (int i = 0; i < kMapTypeNum; i++) {

		DeleteGraph(m_graphHandles[i]);
	}

	// mapDataの破棄
	CleanUp();
}

void Map::Update()
{
}

void Map::Draw() 
{
	// 読み込んだCSVのマップ情報から描画する
	for (int y = 0; y < m_mapChipNumY; y++) {

		for (int x = 0; x < m_mapChipNumX; x++) {


			DrawRotaGraph(x * kMapChipChangeSize + (kMapChipChangeSize / 2),
				y * kMapChipChangeSize + (kMapChipChangeSize / 2),
				m_chipScaleRate, 0.0f,
				m_graphHandles[m_ppMapData[y][x]], false, false);
		}
	}
#ifdef _DEBUG
	DebugDraw();

#endif // _DEBUG

}

/////////////////////////////////////////////////////////////////////////////////////////

bool Map::LoadCSVToMapData(int stageNum)
{
	// 読み込むファイル名を作成
	char fileNameCSV[256];

	// 引数を使ってファイル名を作成
	sprintf_s(fileNameCSV, 256, ".\\data\\Map%d.csv",stageNum);

	// マップサイズを調べる
	if (!CheckMapSize(fileNameCSV))return false;

	// マップサイズからポインタを使って動的にマップ情報を格納する二次元配列を用意する
	// mapData[ ここ ][]の要素数を生成
	m_ppMapData = new int* [m_mapChipNumY];

	for (int i = 0; i < m_mapChipNumY; i++) {

		// mapData[][ ここ ]の要素数を生成
		m_ppMapData[i] = new int[m_mapChipNumX];
	}

	// ファイルを開く <fstream>
	std::ifstream ifs(fileNameCSV);

	// ファイルが開けなければプログラムを終了
	if (ifs.fail()) {

		MessageBox(NULL, "Fail to open csv file", "Fail to open csv file", MB_OK);
		return false;
	}

	// CSVデータを読み込んでマップデータに格納
	for (int y = 0; y < m_mapChipNumY; y++) {

		// 読み込んだものを一時的に格納するデータを用意
		std::string buf;

		// 1行ずつ読み込む <string>
		getline(ifs, buf);

		// この段階ではカンマがある文字列としてのデータなので、
		// カンマで区切られているものをSplit関数を使って分割する
		// 分割されたデータを可変長配列に一時保管する
		std::vector<std::string> separatedStringList = Split(buf, ',');

		// 分割されたデータを文字列から数字の情報に変換する
		// 数字に変換したデータをmapDataに格納する
		int x = 0;
		for (auto itr = separatedStringList.begin(); itr != separatedStringList.end(); ++itr, x++) {

			// separatedStringListの内容を頭から一つずつチェック
			// 文字列になっているものを数字に変換してmapDataに格納
			m_ppMapData[y][x] = atoi(itr->c_str());
		}
	}

	// 開いたファイルは必ず閉じる
	ifs.close();

	// 読み込みが完了したのでtrueを返す
	return true;
}

std::vector<std::string> Map::Split(const std::string& str, char separate) {

	// 最終的にカンマがある毎に分割した配列を返したいが、
	// 読み込んだ1行のデータの中にカンマが何個あるのかこの時点では分かっていない
	// 今まで勉強した配列は宣言時に要素数が決まっている必要があった配列(固定長配列)なので
	// 要素数が何個あっても使える可変長配列というものを使用する
	std::vector<std::string> separatedList;

	// 引数で渡された文字列を分割しやすくする <sstream>
	std::stringstream ss(str);

	// 分割したデータの一時保管をする変数を宣言
	std::string buf;

	// 引数の文字列strを1文字ずつチェック
	// 分割する記号(separate)が見つかったら分割する
	// 最後の文字まで繰り返す
	while (std::getline(ss, buf, separate)) {

		// 分割する記号(separate)が見つかったら可変長配列に入れていく
		separatedList.push_back(buf);
	}

	// 分割した配列を返す
	return separatedList;
}

bool Map::CheckMapSize(const char* fileName)
{
	// ファイルを開く
	std::ifstream ifs(fileName);

	// ファイルが開けなければプログラムを終了
	if (ifs.fail()) {

		MessageBox(NULL, "Fail to open csv file", "Fail to open csv file", MB_OK);
		return false;
	}

	// マップサイズのクリア
	m_mapChipNumX = 0;
	m_mapChipNumY = 0;

	// マップの大きさを1行ずつ読み込んで調べる
	// 読み込んだマップの大きさが分からないので、無限ループで調べる
	while (true) {

		// 読み込んだものを一時的に格納するデータを用意
		std::string buf;

		// 1行ずつ読み込む
		getline(ifs, buf);

		// 読み込んだデータがなければループを終了
		if (ifs.eof())break;

		// 1行読み込めたので行をカウントアップ
		m_mapChipNumY++;

		// 読み込んだ行を分割してマップの横サイズを調べる
		std::vector<std::string> separatedList = Split(buf, ',');

		// 分割後の配列の要素数を格納する
		m_mapChipNumX = separatedList.size();
	}

	m_mapSizeX = static_cast<float>(m_mapChipNumX * kMapChipChangeSize);
	m_mapSizeY = static_cast<float>(m_mapChipNumY * kMapChipChangeSize);

	// 開いたファイルは必ず閉じる
	ifs.close();

	// 読み込みが完了したのでtrueを返す
	return true;
}

void Map::CleanUp()
{
	// mapDataの破棄
	for (int i = 0; i < m_mapChipNumX; i++) {

		// 1行分のポインタを順番に開放
		delete[] m_ppMapData[i];
	}

	// 最後にポインタを開放
	delete[] m_ppMapData;
}

#ifdef _DEBUG
void Map::DebugDraw() {

	// 読み込んだCSVのマップの情報から描画する
	for (int y = 0; y < m_mapChipNumY; y++) {

		for (int x = 0; x < m_mapChipNumX; x++) {

			DrawBox(x * kMapChipChangeSize, y * kMapChipChangeSize,
				x * kMapChipChangeSize + kMapChipChangeSize,
				y * kMapChipChangeSize + kMapChipChangeSize,
				GetColor(128, 128, 0), false);

		}
	}

	printfDx("\n\n\n\n\n\n\n\n\n\m_mapChipNumX : %4d\n", m_mapChipNumX);
	printfDx("m_mapChipNumY : %4d\n", m_mapChipNumY);
	printfDx("マップの幅 　: %f\n", GetMapSizeX());
	printfDx("マップの高さ : %f\n", GetMapSizeY());
	printfDx("stage : %4d\n", m_stageID);
}
#endif // _DEBUG

