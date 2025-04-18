﻿#pragma once
#include"Vector.h"
#include"Matrix.h"
#include<assert.h>
#include<cmath>

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

//x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

//Y軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

/// <summary>
/// 合成された行列の作成
/// </summary>
/// <param name="scale">拡縮の大きさ</param>
/// <param name="rotate">回転量</param>
/// <param name="translate">移動量</param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);