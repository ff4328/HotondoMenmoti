#include "SoundManager.h"

#include <DxLib.h>
#include <string>
#include <cassert>

namespace {

	// サウンドデータが入ったフォルダのパス
	const char* const kFolderPath = ".\\Resource\\sounds\\";

	// SEデータのファイルパス
	const char* const kSeDataPath[] = {

		"SE\\「お客様にご案内いたします」.mp3",
		"SE\\「お金をお入れください」.mp3",
		"SE\\「スペイン」.mp3",
		"SE\\「チェストー！」.mp3",
		"SE\\「ハッピーハロウィン！」.mp3",
		"SE\\「ぴーんぽーんぱーんぽーん」.mp3",
		"SE\\「もう怒った」.mp3",
		"SE\\「や、やだな～本気にしないでよぉ」.mp3",
		"SE\\「開けましておめでとうございます」.mp3",
		"SE\\「緊急事態発生！」.mp3",
		"SE\\「残念でした」.mp3",
		"SE\\「続きはWebで」.mp3",
		"SE\\「不合格です」.mp3",
		"SE\\DecisionSE.mp3",
		"SE\\maou_se_battle17.mp3",
		"SE\\mixkit-metal-arrow-hit-2769.wav",
		"SE\\mixkit-quick-magic-sword-slice-2793.wav",
		"SE\\mixkit-sword-hits-heavy-metal-2797.wav",
		"SE\\mixkit-wine-bottles-clinking-525.wav",
		"SE\\アヒルが大笑い.mp3",
		"SE\\ゲージ回復1.mp3",
		"SE\\ちょこっと触る.mp3",
		"SE\\ヒーローの決めポーズ.mp3",
		"SE\\レベルアップ.mp3",
		"SE\\歓声と拍手.mp3",
		"SE\\間抜け2.mp3",
		"SE\\間抜け7.mp3",
		"SE\\金額表示.mp3",
		"SE\\警報が鳴る.mp3",
		"SE\\尺八.mp3",
		"SE\\小鼓（こつづみ）.mp3",
		"SE\\荘厳な雰囲気.mp3",
		"SE\\足首がグキッ.mp3",
		"SE\\男衆「オウ！」.mp3",
		"SE\\男衆「始めいッ！」.mp3",
		"SE\\文字アニメーション2.mp3",
	};

	// BGMデータのファイルパス
	const char* const kBgmDataPath[] = {

		"BGM\\TitleBGM.mp3",
		"BGM\\MeinBGM.mp3",
		"BGM\\GameClearBGM.mp3",
		"BGM\\GameOverBGM.mp3"
	};

	// デフォルトの音量 0-255
	constexpr int kDefaultVolume = 160;
}

SoundManager::SoundManager():
	m_currentBgmHandle(-1)
{

	for ( auto& e : m_seHandles ) {

		e = -1;
	}

	for (auto& e : m_bgmHandles) {

		e = -1;
	}
}

SoundManager& SoundManager::GetInstance()
{

	static SoundManager instance;
	return instance;
}

void SoundManager::LoadSe()
{

	for (int i = 0; i < static_cast<int>(Sound::SE::Max); i++ ) {

		// ファイルパスを作成 フォルダ＋データ名
		std::string filePath = std::string(kFolderPath) + kSeDataPath[i];

		// SEの読み込み
		m_seHandles[i] = LoadSoundMem(filePath.c_str());

		// 読み込みが失敗していたら警告
		if ( m_seHandles[i] == -1) {

			assert(false && "SE 読み込み失敗");
		}

		// ボリュームの設定
		ChangeVolumeSoundMem(kDefaultVolume, m_seHandles[i]);
	}

}

void SoundManager::PlaySe(Sound::SE id)
{

	int handle = m_seHandles[static_cast<int>(id)];

	// 読み込めていないIDなら即時return
	if (handle == -1) return;

	// SEの再生
	PlaySoundMem(handle, DX_PLAYTYPE_BACK);

}

void SoundManager::LoadBGM()
{
	for (int i = 0; i < static_cast<int>(Sound::BGM::Max); i++) {

		// ファイルパスを作成 フォルダ＋データ名
		std::string filePath = std::string(kFolderPath) + kBgmDataPath[i];
		// SEの読み込み
		m_bgmHandles[i] = LoadSoundMem(filePath.c_str());

		// 読み込みが失敗していたら警告
		if (m_bgmHandles[i] == -1) {

			assert(false && "BGM 読み込み失敗");
		}
		// ボリュームの設定
		ChangeVolumeSoundMem(kDefaultVolume, m_bgmHandles[i]);
	}
}

void SoundManager::PlayBGM(Sound::BGM id)
{

	// すでに再生していたら停止する 多重再生を防ぐ
	if ( m_currentBgmHandle != -1 ) {

		StopSoundMem(m_currentBgmHandle);
	}

	// 再生中のBGMハンドルの更新
	m_currentBgmHandle = m_bgmHandles[static_cast<int>(id)];
	
	// BGMの再生
	PlaySoundMem(m_currentBgmHandle, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBGM()
{

	// BGMが再生しているか確認
	if (m_currentBgmHandle == -1) return;

	// BGMの停止
	StopSoundMem(m_currentBgmHandle);

	m_currentBgmHandle = -1;

}

void SoundManager::Release()
{

	for ( auto& e : m_seHandles) {

		if (e != -1) {

			// SEデータの削除
			DeleteSoundMem(e);
			// ハンドルを初期値にしておく
			e = -1;
		}
	}

	for (auto& e : m_bgmHandles) {

		if (e != -1) {

			// BGMデータの削除
			DeleteSoundMem(e);
			// ハンドルを初期値にしておく
			e = -1;
		}
	}

}
