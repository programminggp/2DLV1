#include "CRoadManager.h"
#include "CPoint.h"
#include "CEnemy.h"

#define START_INDEX 0 //処理開始位置
#define COURSE_POINT_SIZE 120.0f //ポイントコライダのサイズ

CRoadManager::CRoadManager(CModel *model, const CVector& position, const CVector& rotation, const CVector& scale, const CVector& startPos, const CVector& foward)
	: CObjFloor(model, position, rotation, scale)
{
	Init(model, position, rotation, scale, startPos, foward);
}

CRoadManager::~CRoadManager()
{
}

void CRoadManager::Init(CModel* pmodel, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	CCharacter::Update();

	//size：三角形の個数
	int size = pmodel->mTriangles.size();
	int last = size; //配列の最後
	//三角形の個数分の座標を配列で持つ
	CVector* mpPoint = new CVector[size];
	for (int i = 0; i < size; i++)
	{
		//三角形をワールド座標に変換
		CVector v[3];
		v[0] = pmodel->mTriangles[i].mV[0] * mMatrix;
		v[1] = pmodel->mTriangles[i].mV[1] * mMatrix;
		v[2] = pmodel->mTriangles[i].mV[2] * mMatrix;
		//三角形の重心を求める
		mpPoint[i].mX = (v[0].mX + v[1].mX + v[2].mX) / 3.0f;
		mpPoint[i].mY = (v[0].mY + v[1].mY + v[2].mY) / 3.0f;
		mpPoint[i].mZ = (v[0].mZ + v[1].mZ + v[2].mZ) / 3.0f;
	}

	int start = START_INDEX; //開始する番号
	float min = FLT_MAX; //FLT_MAX はfloat型の最大値
	float len; //長さ
	CVector vector; //向きなど

	//startPosから一番近いポイントを求める
	for (int i = 0; i < size; i++)
	{
		//向きを求める
		vector = mpPoint[i] - startPos;
		//長さを求める
		len = vector.Length();
		if (len < min)
		{
			start = i;
			min = len;
		}
	}
	std::vector<CVector> vecPoint;
	//一番目のポイントを追加する
	vecPoint.push_back(mpPoint[start]);
	//配列の要素を削除し、最後を減算する
	mpPoint[start] = mpPoint[--last];

	//2番目を決める
	//1番目から進行方向で一番ちかいポイントを探す
	start = 0;
	min = FLT_MAX;
	for (int i = 0; i < last; i++)
	{
		vector = mpPoint[i] - vecPoint[vecPoint.size() - 1];
		//進行方向だけ処理の対象
		if (vector.Dot(foward) > 0.0f)
		{
			//最も近いポイントを探す
			if (min > vector.Length())
			{
				min = vector.Length();
				start = i;
			}
		}
	}
	vecPoint.push_back(mpPoint[start]);
	mpPoint[start] = mpPoint[--last];

	//3番目以降を決める
	while (vecPoint.size() < size)
	{
		start = 0;
		min = FLT_MAX;
		for (int i = 0; i < last; i++)
		{
			if (min > (vecPoint[vecPoint.size() - 1] - mpPoint[i]).Length())
			{
				min = (vecPoint[vecPoint.size() - 1] - mpPoint[i]).Length();
				start = i;
			}
		}
		vecPoint.push_back(mpPoint[start]);
		mpPoint[start] = mpPoint[--last];
	}

	//ポイント配列から正式なポイントを生成する
	//ポイント配列の後から前に向かって作成
	CPoint* next;
	//lastPoint：最後のポイントから作成
	CPoint* lastPoint = next = new CPoint((vecPoint[size - 1] + vecPoint[size - 2]) * 0.5f, COURSE_POINT_SIZE);
	CVector length;
	const int between = 4; // ポイントの間隔定数　少ないと多く配置する
	//ポイント間の距離をコントロールする
	float betweenPoint = COURSE_POINT_SIZE * between;
	for (int i = size - 3; i >= 0; i -= 2) {
		length = (vecPoint[i] + vecPoint[i - 1]) * 0.5f - next->mPosition;
		if (length.Length() > betweenPoint)
		{
			next = new CPoint((vecPoint[i] + vecPoint[i - 1]) * 0.5f, COURSE_POINT_SIZE, next);
		}
	}
	lastPoint->Set((vecPoint[size - 1] + vecPoint[size - 2]) * 0.5f, COURSE_POINT_SIZE, next);
	//最初の目標を設定
	CEnemy::mPoint = next->GetNextPoint();
	//配列の削除
	delete[] mpPoint;
}

//void CRoadManager::Update()
//{
//	mFrameCount++;
//	mFrameCount %= INTERVAL;
//	if (mFrameCount == 0)
//	{
//		mDispCount++;
////		mDispCount %= mRoad.size();
//	}
//}
//
//void CRoadManager::Render()
//{
//	CObjFloor::Render();
//	return;
//}
