#pragma once
#include <DxLib.h>
class Vector2
{
public:
	/// <summary>
	/// 座標
	/// </summary>
	float x, y;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	constexpr Vector2() : x(0), y(0) {}
	
	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	constexpr Vector2(float x, float y) : x(x), y(y) {}
//========================================================================================

	/// <summary>
	/// マイナスのベクトル
	/// </summary>
	/// <returns></returns>
	Vector2 operator-() const;

	/// <summary>
	/// ベクトルの加算
	/// </summary>
	/// <param name="vec">足されるベクトル</param>
	/// <returns></returns>
	Vector2 operator+(const Vector2& vec) const;

	/// <summary>
	/// ベクトルの減算
	/// </summary>
	/// <param name="vec">引かれるベクトル</param>
	/// <returns></returns>
	Vector2 operator-(const Vector2& vec) const;

	/// <summary>
	/// ベクトルとスカラーの乗算
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector2 operator*(float scale) const;

	/// <summary>
	/// ベクトルとスカラーの除算
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector2 operator/(float scale) const;

	/// <summary>
	/// ベクトルとベクトルの加算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector2& operator+= (const Vector2& vec);

	/// <summary>
	/// ベクトルとベクトルの減算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector2& operator-= (const Vector2& vec);

	/// <summary>
	/// ベクトルとスカラーの乗算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector2& operator*= (float scale);

	/// <summary>
	/// ベクトルとスカラーの除算代入演算子
	/// 自身を変更するので参照を返す
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector2& operator/= (float scale);

	/// <summary>
	/// ベクトルの比較 等しいかどうか
	/// </summary>
	/// <param name="vec"></param>
	/// <returns>等しいならtrue</returns>
	bool operator==(const Vector2& vec) const;

	/// <summary>
	/// ベクトルの比較 等しくないかどうか
	/// </summary>
	/// <param name="vec"></param>
	/// <returns>等しくなればtrue</returns>
	bool operator!=(const Vector2& vec) const;

	/// <summary>
	/// ベクトルの長さを取得
	/// 平方根の処理が少し負荷があるので厳密な長さが必要じゃなければ非推奨
	/// </summary>
	/// <returns></returns>
	float GetLength() const;

	/// <summary>
	/// ベクトルの長さの二乗を取得
	/// </summary>
	/// <returns></returns>
	float GetSqLength() const;

	/// <summary>
	/// ベクトルを正規化したものを取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetNormalize() const;

	/// <summary>
	/// DxLibのVECTOR型に変換
	/// </summary>
	/// <returns></returns>
	VECTOR ToVECTOR() const;
};

