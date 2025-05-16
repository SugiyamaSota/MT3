#include"Draw.h"
#include"Function.h"
#include"Vector.h"

void DrawGrid(Camera* camera) {
	const float kGridHalfWidth = 2.0f;
	const int kSubDivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubDivision);

	for (int xIndex = 0; xIndex <= kSubDivision; ++xIndex) {
		Vector3 startPos = { (xIndex - 5) * kGridEvery,0.0f,-kGridHalfWidth };
		Vector3 endPos = { (xIndex - 5) * kGridEvery,0.0f,kGridHalfWidth };
		;
		Vector3 screenStartPos = camera->Conversion(startPos);
		Vector3 screenEndPos = camera->Conversion(endPos);

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

		Vector3 screenStartPos = camera->Conversion(startPos);
		Vector3 screenEndPos = camera->Conversion(endPos);

		int color;
		if (zIndex - 5 == 0) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}

		Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), color);
	}
}

void DrawSphere(const Sphere& sphere, Camera* camera, int color) {
	const int kSubdivision = 10;
	const float kLonEvery = float(2 * M_PI / kSubdivision);
	const float kLatEvery = float(M_PI / kSubdivision);

	// 頂点数は (kSubdivision + 1) * (kSubdivision + 1)
	const int vertexCount = (kSubdivision + 1) * (kSubdivision + 1);
	Vector3 vertices[vertexCount] = {};
	int vertexIndex = 0;

	for (int latIndex = 0; latIndex <= kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;
		for (int lonIndex = 0; lonIndex <= kSubdivision; ++lonIndex) {
			float lon = kLonEvery * lonIndex;

			Vector3 pos = {};
			pos.x = sphere.radius * cosf(lat) * cosf(lon) + sphere.center.x;
			pos.y = sphere.radius * sinf(lat) + sphere.center.y;
			pos.z = sphere.radius * cosf(lat) * sinf(lon) + sphere.center.z;
			vertices[vertexIndex++] = pos;
		}
	}

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


			Vector3 screenA = camera->Conversion(v0);
			Vector3 screenB = camera->Conversion(v1);
			Vector3 screenC = camera->Conversion(v2);
			Vector3 screenD = camera->Conversion(v3);

			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
			Novice::DrawLine(int(screenB.x), int(screenB.y), int(screenD.x), int(screenD.y), color);
			Novice::DrawLine(int(screenC.x), int(screenC.y), int(screenD.x), int(screenD.y), color);
		}
	}
}

void DrawPlane(const Plane& plane, Camera* camera, int color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicuar(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = camera->Conversion(point);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);
}