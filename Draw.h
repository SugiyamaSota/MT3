#pragma once
#include<Novice.h>
#include"Struct.h"
#include"Convert.h"
#define _USE_MATH_DEFINES
#include<math.h>

//グリッドの描画
void DrawGrid(const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const Matrix4x4& cameraMatrix);

//球体の描画
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const Matrix4x4& cameraMatrix, int color);