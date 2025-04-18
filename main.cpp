#include <Novice.h>
#include"Vector.h"
#include"Matrix.h"

const char kWindowTitle[] = "LC1B_13_スギヤマソウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Matrix4x4 m1 = { 3.2f,0.7f,9.6f,4.4f,
					 5.5f,1.3f,7.8f,2.1f,
					 6.9f,8.0f,2.6f,1.0f,
					 0.5f,7.2f,5.1f,3.3f };

	Matrix4x4 m2 = { 4.1f,6.5f,3.3f,2.2f,
					 8.8f,0.6f,9.9f,7.7f,
					 1.1f,5.5f,6.6f,0.0f,
					 3.3f,9.9f,8.8f,2.2f };

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 resultInverseM1 = Inverse(m1);
	Matrix4x4 resultInverseM2 = Inverse(m2);
	Matrix4x4 resultTransposeM1 = Transpose(m1);
	Matrix4x4 resultTransposeM2 = Transpose(m2);
	Matrix4x4 resultIdentity = MakeIdentity4x4();


	const int kRowHeight = 20;
	const int kColumnWidth = 50;

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
		MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, resultInverseM1, "InverseM1");
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, resultInverseM2, "InverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, resultTransposeM1, "TransposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, resultTransposeM2, "TransposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, resultIdentity, "Identity");
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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