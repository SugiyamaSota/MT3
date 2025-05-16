#include <Novice.h>
#include<imgui.h>
#include"Camera.h"
#include"Draw.h"
#include"Matrix.h"
#include"Vector.h"
#include"Struct.h"
#include"Function.h"

const char kWindowTitle[] = "LC1B_13_スギヤマソウタ_タイトル";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//カメラの生成と初期化
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);

	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		1.0f,
	};

	Plane plane = {
		{0.0f,1.0f,0.0f},
		1.0f,
	};

	int sphereColor = BLACK;
	int planeColor = BLACK;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//カメラの更新
		camera->Update();
		ImGui::Begin("sphere");
		ImGui::DragFloat3("spherePosition", &sphere.center.x, 0.01f);
		ImGui::DragFloat3("planeNormal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("planeDistance", &plane.distance, 0.01f);
		ImGui::End();
		plane.normal = Normalize(plane.normal);

		if (isCollision(sphere, plane) == true) {
			sphereColor = RED;
		} else {
			sphereColor = BLACK;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		

		DrawGrid(camera);
		DrawSphere(sphere, camera, sphereColor);
		DrawPlane(plane, camera, planeColor);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}