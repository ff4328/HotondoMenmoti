#include "SceneManager.h"
#include "SceneMain.h"

#include "DxLib.h"
#include <cassert>

SceneManager::SceneManager():
	m_pScene(nullptr)
{

	m_pScene = new SceneMain;

}

void SceneManager::Init() {

	m_pScene->Init();

}

void SceneManager::End() {

	if (!m_pScene) return;

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->End();
	delete m_pScene;

}

void SceneManager::Update() {

	if (m_pScene) return;

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	// シーンの切り替えもしくは更新
	SceneBase* pScene = m_pScene->Update();

	if (pScene != m_pScene) {

		m_pScene->End();
		delete m_pScene;

		// ポインタを初期化
		m_pScene = pScene;

		if (m_pScene != nullptr)
		{

			m_pScene->Init();

		}

	}

}

void SceneManager::Draw() {

	if (!m_pScene) return;

	// 確認処理
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->Draw();

}
