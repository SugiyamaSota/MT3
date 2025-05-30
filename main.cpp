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
	//AABB
	AABB aabb{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},
	};
	int aabbColor = WHITE;

	//球
	Sphere sphere{
		{0.5f,0.5f,0.5f},
		1.0f,
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
		ImGui::SliderFloat3("aabb1.min", &aabb.min.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("aabb1.max", &aabb.max.x, -1.0f, 1.0f);
		ImGui::End();

		//aabb の座標制御
		aabb.min.x = (std::min)(aabb.min.x, aabb.max.x);
		aabb.max.x = (std::max)(aabb.min.x, aabb.max.x);
		aabb.min.y = (std::min)(aabb.min.y, aabb.max.y);
		aabb.max.y = (std::max)(aabb.min.y, aabb.max.y);
		aabb.min.z = (std::min)(aabb.min.z, aabb.max.z);
		aabb.max.z = (std::max)(aabb.min.z, aabb.max.z);

		///// カメラの更新 /////
		camera->Update();

		///// 座標の変換 /////

		///// 衝突判定 /////
		if (IsCollision(aabb, sphere)) {
			aabbColor = RED;
		} else {
			aabbColor = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///// グリッドの描画 /////
		DrawGrid(camera);

		///// AABBの描画 /////
		DrawAABB(aabb, camera, aabbColor);

		///// 球の描画 /////
		DrawSphere(sphere, camera, WHITE);
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