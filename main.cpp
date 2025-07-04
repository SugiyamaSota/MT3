#include <Novice.h>
#include<imgui.h>
#include"Struct.h"
#include"HeaderReader.h"
#include <algorithm>

const char kWindowTitle[] = "LC1B_13_スギヤマソウタ_タイトル";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// カメラ
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);

	// 振り子
	Pendulum pendulum;
	pendulum.anchor = { 0.0f,1.0f,0.0f };
	pendulum.length = 0.8f;
	pendulum.angle = 0.7f;
	pendulum.angularVelocity = 0.0f;
	pendulum.angularAcceleration = 0.0f;

	// 紐
	Segment segment;
	segment.origin = pendulum.anchor;
	segment.diff = {};

	// 球
	Sphere sphere;
	sphere.center = {};
	sphere.radius = 0.05f;

	float deltaTime = 1.0f / 60.0f;

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

		// ImGui
		ImGui::Begin("Window");
		if (ImGui::Button("Start")) {
			// 開始処理
			pendulum.anchor = { 0.0f,1.0f,0.0f };
			pendulum.length = 0.8f;
			pendulum.angle = 0.7f;
			pendulum.angularVelocity = 0.0f;
			pendulum.angularAcceleration = 0.0f;
		}
		ImGui::End();

		// カメラ
		camera->Update();

		// 振り子
		pendulum.angularAcceleration =
			-(9.8f / pendulum.length) * std::sin(pendulum.angle);
		pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
		pendulum.angle += pendulum.angularVelocity * deltaTime;
		
		// 球
		sphere.center.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
		sphere.center.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
		sphere.center.z = pendulum.anchor.z;

		//紐
		segment.origin = pendulum.anchor;
		segment.diff = sphere.center-pendulum.anchor;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		DrawGrid(camera);

		// 紐
		DrawSegment(segment, camera, WHITE);

		// 球
		DrawSphere(sphere, camera, BLUE);

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