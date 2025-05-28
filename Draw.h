#pragma once

///// 前方宣言 /////
class Camera;
struct Sphere;
struct Plane;
struct Triangle;
struct AABB;

//グリッドの描画
void DrawGrid(Camera* camera);

//球体の描画
void DrawSphere(const Sphere& sphere, Camera* camera, int color);

//平面の描画
void DrawPlane(const Plane& plane, Camera* camera, int color);

//三角形の描画
void DrawTriangle(const Triangle& triangle, Camera* camera, int color);

//AABBの描画
void DrawAABB(const AABB& aabb, Camera* camera, int color);