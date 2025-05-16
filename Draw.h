#pragma once
#include<Novice.h>
#include"Camera.h"
#include"Struct.h"
#define _USE_MATH_DEFINES
#include<math.h>

//グリッドの描画
void DrawGrid(Camera* camera);

//球体の描画
void DrawSphere(const Sphere& sphere, Camera* camera, int color);

//平面の描画
void DrawPlane(const Plane& plane, Camera* camera, int color);