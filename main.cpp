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

	///--- 生成と初期化 ---
	// カメラ
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);

	// ばね
	Spring spring{};
	spring.anchor = { 0.0f,0.0f,0.0f };
	spring.natiralLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	// ボール
	Ball ball{};
	ball.position = { 1.2f,0.0f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 10.0f;
	ball.color = BLUE;

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
			ball.position = { 1.2f,0.0f,0.0f };
		}
		ImGui::End();


		// カメラの更新
		camera->Update();

		// ばねの計算
		Vector3 diff = ball.position - spring.anchor;
		float length = Length(diff);
		if (length != 0.0f) {
			Vector3 direction = Normalize(diff);
			Vector3 restPosition = spring.anchor + direction * spring.natiralLength;
			Vector3 displacement = (ball.position - restPosition) * length;
			Vector3 restoringForce = displacement * (-spring.stiffness);
			Vector3 dampingForce = ball.velocity * -spring.dampingCoefficient;
			Vector3 force = restoringForce + dampingForce;
			ball.acceleration = force / ball.mass;
		}
		// 加速度も速度もどちらも秒を基準とした値である
		// それが、1/60秒間(deltaTime)適用されたと考える
		ball.velocity += ball.acceleration * deltaTime;
		ball.position += ball.velocity * deltaTime;

		Vector3 scSpringAnchor = camera->Conversion(spring.anchor);
		Vector3 scBallPos = camera->Conversion(ball.position);

		Novice::ScreenPrintf(0, 0, "ballPos : %f,%f", ball.position.x, ball.position.y);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		DrawGrid(camera);

		// ばね
		Novice::DrawLine(int(scSpringAnchor.x), int(scSpringAnchor.y), int(scBallPos.x), int(scBallPos.y), WHITE);

		// 球
		Novice::DrawEllipse(int(scBallPos.x), int(scBallPos.y), int(ball.radius), int(ball.radius), 0.0f, ball.color, kFillModeSolid);

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