#pragma once
class Player
{

public:

	/// <summary>
	/// Playerのコンストラクタ
	/// </summary>
	Player() ;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理を行う
	/// </summary>
	void End();

	/// <summary>
	/// アニメーションの初期設定
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 表示
	/// </summary>
	void Draw();

	/// <summary>
	/// 
	/// </summary>
	void Finalize();
private:

	//=========================================
	// メンバ変数
	//=========================================

	int m_graphHandle;

	float m_posX;
	float m_posY;
	int m_sizeX;
	int m_sizeY;

};

