#include"Draw.h"

void DrawGrid(const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const Matrix4x4& cameraMatrix) {
	const float kGridHalfWidth = 2.0f;
	const int kSubDivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubDivision);

	for (int xIndex = 0; xIndex <= kSubDivision; ++xIndex) {
		Vector3 startPos = { (xIndex - 5) * kGridEvery,0.0f,-kGridHalfWidth };
		Vector3 endPos = { (xIndex - 5) * kGridEvery,0.0f,kGridHalfWidth };

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, viewProjection));
		Vector3 ndcStartPos = Transform(startPos, worldViewProjectionMatrix);
		Vector3 screenStartPos = Transform(ndcStartPos, viewportMatrix);
		Vector3 ndcEndPos = Transform(endPos, worldViewProjectionMatrix);
		Vector3 screenEndPos = Transform(ndcEndPos, viewportMatrix);

		int color;
		if (xIndex - 5 == 0) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}

		Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), color);
	}

	for (int zIndex = 0; zIndex <= kSubDivision; ++zIndex) {
		Vector3 startPos = { -kGridHalfWidth,0.0f,(zIndex - 5) * kGridEvery };
		Vector3 endPos = { kGridHalfWidth,0.0f,(zIndex - 5) * kGridEvery };

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, viewProjection));
		Vector3 ndcStartPos = Transform(startPos, worldViewProjectionMatrix);
		Vector3 screenStartPos = Transform(ndcStartPos, viewportMatrix);
		Vector3 ndcEndPos = Transform(endPos, worldViewProjectionMatrix);
		Vector3 screenEndPos = Transform(ndcEndPos, viewportMatrix);

		int color;
		if (zIndex - 5 == 0) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}

		Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), color);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const Matrix4x4& cameraMatrix, int color) {
    const int kSubdivision = 10;
    const float kLonEvery = float(2 * M_PI / kSubdivision);
    const float kLatEvery = float(M_PI / kSubdivision);

    // 頂点数は (kSubdivision + 1) * (kSubdivision + 1)
    const int vertexCount = (kSubdivision + 1) * (kSubdivision + 1);
    Vector3 vertices[vertexCount];
    int vertexIndex = 0;

    for (int latIndex = 0; latIndex <= kSubdivision; ++latIndex) {
        float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;
        for (int lonIndex = 0; lonIndex <= kSubdivision; ++lonIndex) {
            float lon = kLonEvery * lonIndex;

            Vector3 pos;
            pos.x = sphere.radius * cosf(lat) * cosf(lon) + sphere.center.x;
            pos.y = sphere.radius * sinf(lat) + sphere.center.y;
            pos.z = sphere.radius * cosf(lat) * sinf(lon) + sphere.center.z;
            vertices[vertexIndex++] = pos;
        }
    }

    Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
    Matrix4x4 viewMatrix = Inverse(cameraMatrix);
    Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, viewProjection));

    for (int latIndex = 0; latIndex < kSubdivision; ++latIndex) {
        for (int lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
            int index = latIndex * (kSubdivision + 1) + lonIndex;
            int nextLonIndex = (lonIndex + 1) % (kSubdivision + 1);
            int nextLatIndex;
            if (latIndex + 1 < kSubdivision) {
                nextLatIndex = latIndex + 1;
            } else {
                nextLatIndex = kSubdivision;
            }

            Vector3 v0 = vertices[index];
            Vector3 v1 = vertices[latIndex * (kSubdivision + 1) + nextLonIndex];
            Vector3 v2 = vertices[nextLatIndex * (kSubdivision + 1) + lonIndex];
            Vector3 v3 = vertices[nextLatIndex * (kSubdivision + 1) + nextLonIndex];

            Vector3 ndcA = Transform(v0, worldViewProjectionMatrix);
            Vector3 screenA = Transform(ndcA, viewportMatrix);
            Vector3 ndcB = Transform(v1, worldViewProjectionMatrix);
            Vector3 screenB = Transform(ndcB, viewportMatrix);
            Vector3 ndcC = Transform(v2, worldViewProjectionMatrix);
            Vector3 screenC = Transform(ndcC, viewportMatrix);
            Vector3 ndcD = Transform(v3, worldViewProjectionMatrix);
            Vector3 screenD = Transform(ndcD, viewportMatrix);

            Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
            Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
            Novice::DrawLine(int(screenB.x), int(screenB.y), int(screenD.x), int(screenD.y), color);
            Novice::DrawLine(int(screenC.x), int(screenC.y), int(screenD.x), int(screenD.y), color);
        }
    }
}