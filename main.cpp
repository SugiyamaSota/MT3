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

	///--- 生成と初期化 --- ///
	// カメラ
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);

	// translates
	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	// rotates
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};

	// scales
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

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

		///// ImGuiの処理 /////
		ImGui::Begin("DebugWindow");
		ImGui::SliderFloat3("SScale", &scales[0].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("STranslate&d", &translates[0].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("SRotate&d", &rotates[0].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("EScale", &scales[1].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("ETranslate&d", &translates[1].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("ERotate&d", &rotates[1].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("HScale", &scales[2].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("HTranslate&d", &translates[2].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("HRotate&d", &rotates[2].x, -1.0f, 1.0f);
		ImGui::End();


		///// カメラの更新 /////
		camera->Update();

		/// --- ワールド行列　---
		// 肩
		Matrix4x4 shoulderWorldMatrix = camera->MakeAffineMatrix(scales[0], rotates[0], translates[0]);

		// 肘
		Matrix4x4 elbowLocalMatrix = camera->MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 elbowWorldMatrix = Multiply(elbowLocalMatrix, shoulderWorldMatrix);

		// 手
		Matrix4x4 handLocalMatrix = camera->MakeAffineMatrix(scales[2], rotates[2], translates[2]);
		Matrix4x4 handWorldMatrix = Multiply(handLocalMatrix, elbowWorldMatrix);

		/// --- 行列変換 ---
		// 肩
		Vector3 shoulderScreenPosition = camera->MakeScreenPosition(shoulderWorldMatrix);
		Sphere shoulderSphere = {
			{shoulderScreenPosition},
			{10.0f},
		};
		// 肘
		Vector3 elbowScreenPosition = camera->MakeScreenPosition(elbowWorldMatrix);
		Sphere elbowSphere = {
			{elbowScreenPosition},
			{10.0f},
		};
		// 手
		Vector3 handScreenPosition = camera->MakeScreenPosition(handWorldMatrix);
		Sphere handSphere = {
			{handScreenPosition},
			{10.0f},
		};
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///// グリッドの描画 /////
		DrawGrid(camera);

		// 球の描画
		DrawSphere(shoulderSphere, camera, GREEN);
		DrawSphere(elbowSphere, camera, RED);
		DrawSphere(handSphere, camera, BLUE);
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