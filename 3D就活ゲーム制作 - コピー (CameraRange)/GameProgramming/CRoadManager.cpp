#include "CRoadManager.h"
#include "CPoint.h"
#include "CEnemy.h"

#define RADIUS 120.0f

//CRoadManager(モデルデータのポインタ,位置,回転,拡大縮小,スタート位置,進行方向)
CRoadManager::CRoadManager(CModel* model, const CVector& position, const CVector& rotation, const CVector& scale, const CVector& startPos, const CVector& foward)
	: CObjFloor(model, position, rotation, scale)
{
	Init(model, position, rotation, scale, startPos, foward);
}

void CRoadManager::Init(CModel* pmodel, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward)
{
	//mMatrixの更新
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	CCharacter::Update();


	//実装１　三角形ポリゴンの重心座標を求めて配列にする
	//（１）pmodelから三角形ポリゴンの数を取得する
	int triangle_size = pmodel->mTriangles.size();
	//printf("三角形ポリゴンの数：%d\n", triangle_size);

	//（２）ポリゴンの数分ベクトルの配列を作成する。
	CVector* polygonarray;
	polygonarray = new CVector[triangle_size];

	////（３）三角形ポリゴンの各頂点にmMatrixを掛けてワールド座標を求め、三角形の重心の座標を求める
	////各コライダの頂点をワールド座標へ変換//参考
	//v[0] = y->mV[0] * y->mMatrix * y->mpParent->mMatrix;
	//v[1] = y->mV[1] * y->mMatrix * y->mpParent->mMatrix;
	//v[2] = y->mV[2] * y->mMatrix * y->mpParent->mMatrix;
	for (int i = 0; i < triangle_size; i++) {
		CVector v[3], sv;
		v[0] = pmodel->mTriangles[i].mV[0] * mMatrix;
		v[1] = pmodel->mTriangles[i].mV[1] * mMatrix;
		v[2] = pmodel->mTriangles[i].mV[2] * mMatrix;
		sv = CVector((v[0].mX + v[1].mX + v[2].mX) / 3.0f, (v[0].mY + v[1].mY + v[2].mY) / 3.0f, (v[0].mZ + v[1].mZ + v[2].mZ) / 3.0f);
		//（４）配列のベクトルの値に、三角形ポリゴンの重心座標を代入していく
		polygonarray[i] = sv;
	}

	//実装２　先頭データの探索
	//重心座標の配列から、スタート位置に最も近い重心を求める。
	//求めた重心と配列の先頭を入れ替える。
	CVector spos = startPos;
	CVector vdist;
	CVector nearestvec = CVector(0.0f, 0.0f, 0.0f);
	int nearest_arraynum;
	for (int i = 0; i < triangle_size; i++) {
		vdist = spos - polygonarray[i];
		//一番最初の重心座標は無条件に最も近いものとする
		if (i == 0) {
			nearestvec = vdist;
			nearest_arraynum = i;
		}
		else {
			if (vdist.Length() < nearestvec.Length()) {
				nearestvec = vdist;
				nearest_arraynum = i;
			}
		}
	}
	//求めた重心と配列の先頭を入れ替える。
	CVector temp = polygonarray[0];
	polygonarray[0] = polygonarray[nearest_arraynum];
	polygonarray[nearest_arraynum] = temp;


	//実装３　2番目データの探索
	//重心座標の2番目以降の配列について、先頭のデータから進行方向にある重心の中で、
	//最も先頭に近い重心を探し、配列の2番目と入れ替える。
	CVector poly_forward = foward;
	float sdot = 0;
	int sArraynum = 0;
	bool isfirst = true;
	for (int i = 0 + 1; i < triangle_size; i++) {
		CVector dir = polygonarray[i] - polygonarray[0];
		//printf("内積：%8.2f\n", polygonarray[i].Dot(polygonarray[i] - polygonarray[0]));

		//内積がプラスになるものが候補
		if (poly_forward.Dot(polygonarray[i] - polygonarray[0]) > 0) {
			//その中で最もpolygonarray[0]と近いものが[1]となる
			vdist = polygonarray[i] - polygonarray[0];
			//一番最初のプラス内積はすぐ設定
			if (isfirst) {
				nearestvec = vdist;
				sArraynum = i;
				isfirst = false;
			}
			else {
				if (vdist.Length() < nearestvec.Length()) {
					nearestvec = vdist;
					sArraynum = i;
				}
			}
		}
	}
	temp = polygonarray[1];
	polygonarray[1] = polygonarray[sArraynum];
	polygonarray[sArraynum] = temp;

	//実装４　3番目以降のデータの並び変え
	//配列の3番目以降について以下の手順で並び変える
	//（１）現在位置を3番目にする
	//（２）現在位置の一つ前の値に最も近い重心を探し、現在位置と入れ替える
	//（３）現在位置を一つ後ろにして、（２）を繰り返す	
	sArraynum = 0;
	for (int i = 2; i < triangle_size; i++) {
		//i番目より前のデータは並び変えの対象にならない
		isfirst = true;
		for (int j = i; j < triangle_size; j++) {
			vdist = polygonarray[i - 1] - polygonarray[j];
			if (isfirst) {
				nearestvec = vdist;
				sArraynum = j;
				isfirst = false;
			}
			else {
				if (vdist.Length() < nearestvec.Length()) {
					nearestvec = vdist;
					sArraynum = j;
				}
			}
		}
		temp = polygonarray[i];
		polygonarray[i] = polygonarray[sArraynum];
		polygonarray[sArraynum] = temp;
	}
	////配列全ての座標を出力する
	//for (int i = 0; i < triangle_size; i++){
	//	printf("[%3d]   X:%10.2f  Y:%10.2f  Z:%10.2f　　 スタート地点からの距離：%8.2f\n", i, polygonarray[i].mX, polygonarray[i].mY, polygonarray[i].mZ, (spos - polygonarray[i]).Length());
	//}

	//実装５　重心の配列からCPointを生成する
	//（１）配列の最後と最後から1つ前の重心より、中間座標を求め、CPointを生成する。
	//（２）配列の後3つ目から前に向けて、2つずつ中間座標を求めCPointを生成する。
	//（３）生成し終わると、最初に作成したCPointの次ポインタに最後のCPointのポインタを代入する
	CPoint* next, * first;
	CVector center;
	isfirst = true;
	for (int i = triangle_size - 1; i >= 0; i -= 2) {
		//中心座標
		center = (polygonarray[i] + polygonarray[i - 1]) * (1.0f / 2.0f);
		//printf("X:%10.2f  Y:%10.2f  Z:%10.2f\n", center.mX, center.mY, center.mZ);
		if (isfirst) {
			first = next = new CPoint(center, 120, nullptr);
			isfirst = false;
		}
		else {
			//			if ((next->mPosition - center).Length() > RADIUS * 2)
			{
				next = new CPoint(center, 120, next);
			}
		}
	}
	//最初に生成したポインタの次ポインタの設定
	first->Set(first->mPosition, 120, next);
	//最初の目標を設定
	CEnemy::mPoint = next->GetNextPoint();

	delete[] polygonarray;
}
