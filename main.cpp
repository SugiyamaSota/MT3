#include <Novice.h>
#include"Convert.h"
#include"Draw.h"
#include<imgui.h>

const char kWindowTitle[] = "LC1B_13_スギヤマソウタ_タイトル";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//const int kRowHeight = 20;

	//カメラ
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

	//変換行列
	Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 viewProjectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;

	//点
	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		0.01f,
	};

	//線分
	Segment segment{
		{-2.0f,-1.0f,0.0f},
		{3.0f,2.0f,2.0f}
	};

	//点
	Vector3 point = { -1.5f,0.6f,0.6f };

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
		//変換行列
		worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Inverse(cameraMatrix);
		viewProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, viewProjectionMatrix));
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		//座標を変換
		//線分
		Vector3 ndcSegmentStart = Transform(segment.origin, worldViewProjectionMatrix);
		Vector3 screenSegmentStart = Transform(ndcSegmentStart, viewportMatrix);
		Vector3 ndcSegmentEnd = Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix);
		Vector3 screenSegmentEnd = Transform(ndcSegmentEnd, viewportMatrix);
		
		Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
		Vector3 closestPoint = ClosetPoint(point, segment);
		Sphere pointSphere = { point,0.01f };
		Sphere closestPointSphere = { closestPoint,0.01f };

		//ImGuiの処理
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(viewProjectionMatrix, viewportMatrix, cameraMatrix);
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, cameraMatrix, RED);
		DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, cameraMatrix, BLACK);
		Novice::DrawLine(int(screenSegmentStart.x), int(screenSegmentStart.y), int(screenSegmentEnd.x), int(screenSegmentEnd.y), WHITE);
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