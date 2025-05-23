#include <Novice.h>
#include<imgui.h>
#include"Struct.h"
#include"HeaderReader.h"

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

	Plane plane = {
		{0.0f,1.0f,0.0f},
		0.5f,
	};

	Segment segment = {
		{-1.0f,-1.0f,0.0f},
		{2.0f,1.0f,1.5f},
	};

	int segmentColor = WHITE;

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
		ImGui::SliderFloat("Plane Disntance", &plane.distance, -1.0f, 1.0f);
		ImGui::SliderFloat3("Segment Diff", &segment.diff.x, 0.0f, 2.0f);
		ImGui::End();

		///// カメラの更新 /////
		camera->Update();

		///// 線分の変換 /////
		Vector3 segmentStart = camera->Conversion(segment.origin);
		Vector3 segmentEnd = camera->Conversion(Add(segment.origin, segment.diff));

		///// 衝突判定 /////
		//線と平面
		if (isCollision(segment, plane)) {
			segmentColor = RED;
		} else {
			segmentColor = WHITE;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///// グリッドの描画 /////
		DrawGrid(camera);

		/////　平面の描画 /////
		DrawPlane(plane, camera, WHITE);

		///// 線の描画 /////
		Novice::DrawLine(int(segmentStart.x), int(segmentStart.y), int(segmentEnd.x), int(segmentEnd.y), segmentColor);
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