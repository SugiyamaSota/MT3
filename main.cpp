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

	///// カメラの生成と初期化 /////
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);

	///// 変数の初期化 /////
	Vector3 controlPoints[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,0.7f,2.3f},
	};

	Sphere sphere[3];
	for (int i = 0; i < 3; i++) {
		sphere[i].center = controlPoints[i];
		sphere[i].radius = 0.01f;
	}


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
		ImGui::DragFloat3("point1", &controlPoints[0].x);
		ImGui::DragFloat3("point2", &controlPoints[1].x);
		ImGui::DragFloat3("point3", &controlPoints[2].x);
		ImGui::End();


		///// カメラの更新 /////
		camera->Update();

		///// 座標の変換 /////
		for (int i = 0; i < 3; i++) {
			sphere[i].center = controlPoints[i];
		}

		///// 衝突判定 /////

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///// グリッドの描画 /////
		DrawGrid(camera);

		// Beziers曲線
		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], camera, WHITE);

		//点描画
		for (int i = 0; i < 3; i++) {

			DrawSphere(sphere[i], camera, BLACK);
		}

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