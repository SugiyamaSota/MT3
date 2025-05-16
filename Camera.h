#pragma once
#include"struct.h"
#include"imgui.h"
#include<assert.h>
#include<cmath>
#include"Matrix.h"

class Camera {
private:
	int kWindowWidth_;
	int kWindowHeight_;

	//カメラ関連
	Vector3 cameraTranslate_;
	Vector3 cameraRotate_;

	//変換行列
	Matrix4x4 worldMatrix_;
	Matrix4x4 cameraMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 viewProjectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;
	Matrix4x4 viewportMatrix_;

	//平行移動行列
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	//拡縮後の行列
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	//座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	//x軸回転行列
	Matrix4x4 MakeRotateXMatrix(float radian);

	//Y軸回転行列
	Matrix4x4 MakeRotateYMatrix(float radian);

	//Y軸回転行列
	Matrix4x4 MakeRotateZMatrix(float radian);

	//合成された行列の作成
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	//透視射影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	//正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	//ビューポート行列
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

public:
	Vector3 Conversion(const Vector3& v);

	//初期化
	void Initialize(const int kWindowWidth, const int kWindowHeight);

	//更新処理
	void Update();
};

