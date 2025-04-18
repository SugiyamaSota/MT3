#pragma once
#include"Vector.h"
#include"Matrix.h"
#include<assert.h>

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate">移動量</param>
/// <returns>平行移動後の行列</returns>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

/// <summary>
/// 拡縮後の行列
/// </summary>
/// <param name="scale">拡縮の大きさ</param>
/// <returns>拡縮後の行列</returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

/// <summary>
/// 座標変換
/// </summary>
/// <param name="vector">変換させる点</param>
/// <param name="matrix">変換する大きさ</param>
/// <returns>変換後の座標</returns>
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);