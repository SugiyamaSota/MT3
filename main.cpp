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
	ConicalPendulum conicalPendulum;
	conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
	conicalPendulum.length = 0.8f;
	conicalPendulum.halfApexAngle = 0.7f;
	conicalPendulum.angle = 0.0f;
	conicalPendulum.angularVelocity = 0.0f;

	// 紐
	Segment segment;
	segment.origin = conicalPendulum.anchor;
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
			conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
			conicalPendulum.length = 0.8f;
			conicalPendulum.halfApexAngle = 0.7f;
			conicalPendulum.angle = 0.0f;
			conicalPendulum.angularVelocity = 0.0f;
		}
		ImGui::End();

		// カメラ
		camera->Update();

		// 振り子
		conicalPendulum.angularVelocity = std::sqrt(9.8f / (conicalPendulum.length * std::cos(conicalPendulum.halfApexAngle)));
		conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;

		// 球
		float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		sphere.center.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
		sphere.center.y = conicalPendulum.anchor.y - height;
		sphere.center.z = conicalPendulum.anchor.z - std::sin(conicalPendulum.angle) * radius;

		//紐
		segment.origin = conicalPendulum.anchor;
		segment.diff = sphere.center - conicalPendulum.anchor;

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