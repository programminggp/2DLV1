//25
#ifndef CCOLLISION_H
#define CCOLLISION_H

#include "CVector3.h"
#include "CMatrix44.h"
#include "CXCharacter.h"
#include "CTask.h"
//37
#include "glut.h"

/*
コライダの基底クラスの定義
*/
class CCollider : public CTask {
public:
	//コライダタイプ
	enum EColTag {
		ECOLSPHERE,	//球コライダ
		ECOLTRIANGLE, //三角形コライダ
		ECOLCAPSULE,	//29 カプセル
	};
	//コライダのタイプ識別
	EColTag mTag;

	//27 コライダのパーツ識別
	enum EColParts {
//31
		EGROUND = -2, //地面
		EWALL=-1, //壁
		ENONE=0,	//識別なし
		EBODY,
		EHEAD,
		ESWORD,
//30
	};
	EColParts mColParts;

	//コライダの親
	CXCharacter *mpParent;
	//頂点３つ
	CVector3 mV[3];
	//半径
	float mRadius;
	//位置
	CVector3 mPosition;
	//ボーンの合成行列
	CMatrix44 *mpCombinedMatrix;
	CCollider()
		: mpParent(0) {}
};
/*
球コライダの定義
*/
class CSphereCollider : public CCollider {
public:
	CSphereCollider() {
		mTag = ECOLSPHERE;
	}
	/*
	parent：コライダの持ち主
	matrix：コライダを関連付けるボーンの合成行列
	pos：ボーンからの相対位置
	radius：半径
	*/
	CSphereCollider(EColParts parts, CXCharacter *parent,CMatrix44 *matrix, const CVector3 &pos, float radius)
		: CSphereCollider()
	{
		mColParts = parts;//部分
		mpParent = parent;
		mpCombinedMatrix = matrix;
		mPosition = pos;
		mRadius = radius;
		mPriority = mColParts;
		//26 コリジョンマネージャに追加
		CCollisionManager::Get()->Add(this);
	}
	//ワールド座標上でのコライダを取得
	CSphereCollider GetWorld() {
		//インスタンスのコピー
		CSphereCollider temp = *this;
		//中心座標を移動する
		temp.mPosition = temp.mPosition * *mpCombinedMatrix;
		//コピーを返す
		return temp;
	}
	/*
	球コライダの描画
	*/
	void Render() {
		//黄色に設定
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		CMatrix44 mat;
		glPushMatrix();
		//コライダをワールド座標の位置へ移動
		mat.translate(mPosition * *mpCombinedMatrix);
		glMultMatrixf(mat.f);
		//球の描画
		glutWireSphere(mRadius, 20, 20);
		glPopMatrix();
	}
};
/*
三角形コライダの定義
*/
class CTriangleCollider : public CCollider {
public:
	//デフォルトコンストラクタ
	CTriangleCollider() {
		mTag = ECOLTRIANGLE;
	}
	//頂点座標の設定
	CTriangleCollider(EColParts parts, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2)
		: CTriangleCollider()
	{
		mColParts = parts;//部分
		mV[0] = v0;
		mV[1] = v1;
		mV[2] = v2;
		mPriority = mColParts;
		mPosition.x = (v0.x + v1.x + v2.x) / 3.0f;
		mPosition.y = (v0.y + v1.y + v2.y) / 3.0f;
		mPosition.z = (v0.z + v1.z + v2.z) / 3.0f;
		CCollisionManager::Get()->Add(this);
	}
	//コライダの描画
	void Render() {
		//黄色に設定
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		CVector3 v1 = mV[1] - mV[0];
		CVector3 v2 = mV[2] - mV[0];
		//法線を求める
		CVector3 n = v1.Cross(v2);
		glNormal3f(n.x, n.y, n.z);
		glBegin(GL_TRIANGLES);
		glVertex3f(mV[0].x, mV[0].y, mV[0].z);
		glVertex3f(mV[1].x, mV[1].y, mV[1].z);
		glVertex3f(mV[2].x, mV[2].y, mV[2].z);
		glEnd();
	}

};
/*
カプセルコライダ
*/
class CCapsuleCollider : public CCollider {
public:
	CVector3 mV[6];
	CCapsuleCollider()
	{
		mTag = ECOLCAPSULE;
		mRadius = 0.0f;
	}
	CCapsuleCollider(CXCharacter *parent, CMatrix44 *matrix, const CVector3 &v0, const CVector3 &v1, float radius)
		: CCapsuleCollider()
	{
		mColParts = ENONE;
		mpParent = parent;//親へのポインタ
		mpCombinedMatrix = matrix;//連動するボーンの合成行列
		mV[0] = v0;//線の端座標
		mV[1] = v1;//線の端座標
		mRadius = radius;//半径
		mPriority = ENONE;
		CCollisionManager::Get()->Add(this);
		CMatrix44 rot;
		CVector3 mv(0.0f, 0.0f, -radius);
		rot.rotationY(45);
		mV[2] = mV[0] + mv * rot;
		mV[3] = mV[1] + mv * rot;
		rot.rotationY(-45);
		mV[4] = mV[0] + mv * rot;
		mV[5] = mV[1] + mv * rot;
	}
	//ワールド座標上でのコライダを取得する
	CCapsuleCollider GetWorld() {
		CCapsuleCollider temp = *this;
		temp.mV[0] = temp.mV[0] * *mpCombinedMatrix;
		temp.mV[1] = temp.mV[1] * *mpCombinedMatrix;
		temp.mV[2] = temp.mV[2] * *mpCombinedMatrix;
		temp.mV[3] = temp.mV[3] * *mpCombinedMatrix;
		temp.mV[4] = temp.mV[4] * *mpCombinedMatrix;
		temp.mV[5] = temp.mV[5] * *mpCombinedMatrix;
		return temp;
	}
	//描画
	void Render() {
		//黄色に設定
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		glPushMatrix();
		//コライダをワールド座標の位置へ移動
		glMultMatrixf(mpCombinedMatrix->f);
		//線の描画
		glBegin(GL_LINES);
		glVertex3f(mV[0].x, mV[0].y, mV[0].z);
		glVertex3f(mV[1].x, mV[1].y, mV[1].z);
		glEnd();
		glPopMatrix();

		CMatrix44 mat;
		glPushMatrix();
		//コライダをワールド座標の位置へ移動
		mat.translate((mV[0]) * *mpCombinedMatrix + CVector3(0.0f, mRadius, 0.0f));
		glMultMatrixf(mat.f);
		//球の描画
		glutWireSphere(mRadius, 20, 20);
		glPopMatrix();

	}

};


/*27
コリジョンクラスの定義
衝突判定を行うメソッドを
定義します。
*/
class CCollision {
public:
	//球コライダと球コライダの衝突判定
	static bool Sphere(CCollider*, CCollider*);
	//29 カプセルと三角形の衝突判定
	static bool CapsuleTriangle(CCollider*, CCollider*, CVector3 *);
	//29 線分と三角形の衝突判定
	static bool LineTriangle(const CVector3 &p0, const CVector3 &p1, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust);
	//29 点が三角形内に存在するかの判定
	static bool PointInTriangle(const CVector3 &p0, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &n);
	//30 球と三角形の衝突判定
	static bool SphereTriangle(const CVector3 &c, float r, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust);
};



#endif
