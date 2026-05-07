#pragma once

/// <summary>
/// SEとBGMのID管理
/// </summary>
namespace Sound {

	/// <summary>
	/// BGMのIDラベル
	/// </summary>
	enum class BGM {

		Title,
		Menu,
		GameClear,
		GameOver,
		Max
	};

	/// <summary>
	/// SEのIDラベル
	/// </summary>
	enum class SE {

		DecisionSE,
		se_battle17,
		Metal_Arrow_Hit,
		Quick_Magic_Sword_Slice,
		Sword_Hits_Heavy_Metal,
		Wine_Bottle_Clinking,
		Ahiru_ga_Oowarai,
		Gauge_Recovery01,
		Tyokotto_Sawaru,
		Hero_no_Kime_pose,
		LevelUp,
		Kansei_to_Hakusyu,
		Manuke02,
		Manuke07,
		Kingaku_hyouji,
		Keihou_ga_Naru,
		Syakuhati,
		Kodutumi,
		Sougon_na_Hunniki,
		Ashikubi_ga_Guki,
		Moji_Animation02,
		Max
	};
}

/// <summary>
/// SEやBGMの読み込み、再生、停止等を管理するクラス
/// </summary>
class SoundManager
{

public:

	/// <summary>
	/// シングルトンのインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance();

	~SoundManager() = default;

	/// <summary>
	/// SEの読み込み
	/// </summary>
	void LoadSe();

	/// <summary>
	/// SEの再生
	/// </summary>
	/// <param name="id">再生したいSEのID</param>
	void PlaySe( Sound::SE id );

	/// <summary>
	/// BGMの読み込み
	/// </summary>
	void LoadBGM();

	/// <summary>
	/// BGMの再生
	/// </summary>
	/// <param name="id">再生したいBGMのID</param>
	void PlayBGM(Sound::BGM id);

	/// <summary>
	/// 再生中のBGMの停止
	/// </summary>
	void StopBGM();

	/// <summary>
	/// 読み込んだデータの解放
	/// </summary>
	void Release();

private:

	/// <summary>
	/// コンストラクタ
	/// シングルトンパターンのクラスならprivteにして生成できないようにする
	/// </summary>
	SoundManager();

	// シングルトンパターンのクラスでは、コピーできないように『禁止』する
	// コピー禁止
	SoundManager(const SoundManager&) = delete;
	// コピー代入禁止
	SoundManager& operator=(const SoundManager&) = delete;
	// ムーブ禁止
	SoundManager(SoundManager&&) = delete;
	// ムーブ代入禁止
	SoundManager& operator=(const SoundManager&&) = delete;

private:

	/// <summary>
	/// SEのハンドル
	/// </summary>
	int m_seHandles[ static_cast<int>(Sound::SE::Max)];

	/// <summary>
	/// BGMのハンドル
	/// </summary>
	int m_bgmHandles[static_cast<int>(Sound::BGM::Max)];

	/// <summary>
	/// 再生中のBGMハンドル
	/// </summary>
	int m_currentBgmHandle;

};

