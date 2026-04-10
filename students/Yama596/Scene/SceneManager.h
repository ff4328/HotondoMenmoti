#pragma once

// 前方宣言
class SceneBase;

/// <summary>
/// シーン全体を管理するクラス
/// </summary>
class SceneManager 
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SceneManager() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// シーンベースのポインタ
	/// </summary>
	SceneBase* m_pScene;

};