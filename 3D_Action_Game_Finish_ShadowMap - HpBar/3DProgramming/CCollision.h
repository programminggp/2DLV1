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
�R���C�_�̊��N���X�̒�`
*/
class CCollider : public CTask {
public:
	//�R���C�_�^�C�v
	enum EColTag {
		ECOLSPHERE,	//���R���C�_
		ECOLTRIANGLE, //�O�p�`�R���C�_
		ECOLCAPSULE,	//29 �J�v�Z��
	};
	//�R���C�_�̃^�C�v����
	EColTag mTag;

	//27 �R���C�_�̃p�[�c����
	enum EColParts {
//31
		EGROUND = -2, //�n��
		EWALL=-1, //��
		ENONE=0,	//���ʂȂ�
		EBODY,
		EHEAD,
		ESWORD,
//30
	};
	EColParts mColParts;

	//�R���C�_�̐e
	CXCharacter *mpParent;
	//���_�R��
	CVector3 mV[3];
	//���a
	float mRadius;
	//�ʒu
	CVector3 mPosition;
	//�{�[���̍����s��
	CMatrix44 *mpCombinedMatrix;
	CCollider()
		: mpParent(0) {}
};
/*
���R���C�_�̒�`
*/
class CSphereCollider : public CCollider {
public:
	CSphereCollider() {
		mTag = ECOLSPHERE;
	}
	/*
	parent�F�R���C�_�̎�����
	matrix�F�R���C�_���֘A�t����{�[���̍����s��
	pos�F�{�[������̑��Έʒu
	radius�F���a
	*/
	CSphereCollider(EColParts parts, CXCharacter *parent,CMatrix44 *matrix, const CVector3 &pos, float radius)
		: CSphereCollider()
	{
		mColParts = parts;//����
		mpParent = parent;
		mpCombinedMatrix = matrix;
		mPosition = pos;
		mRadius = radius;
		mPriority = mColParts;
		//26 �R���W�����}�l�[�W���ɒǉ�
		CCollisionManager::Get()->Add(this);
	}
	//���[���h���W��ł̃R���C�_���擾
	CSphereCollider GetWorld() {
		//�C���X�^���X�̃R�s�[
		CSphereCollider temp = *this;
		//���S���W���ړ�����
		temp.mPosition = temp.mPosition * *mpCombinedMatrix;
		//�R�s�[��Ԃ�
		return temp;
	}
	/*
	���R���C�_�̕`��
	*/
	void Render() {
		//���F�ɐݒ�
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		CMatrix44 mat;
		glPushMatrix();
		//�R���C�_�����[���h���W�̈ʒu�ֈړ�
		mat.translate(mPosition * *mpCombinedMatrix);
		glMultMatrixf(mat.f);
		//���̕`��
		glutWireSphere(mRadius, 20, 20);
		glPopMatrix();
	}
};
/*
�O�p�`�R���C�_�̒�`
*/
class CTriangleCollider : public CCollider {
public:
	//�f�t�H���g�R���X�g���N�^
	CTriangleCollider() {
		mTag = ECOLTRIANGLE;
	}
	//���_���W�̐ݒ�
	CTriangleCollider(EColParts parts, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2)
		: CTriangleCollider()
	{
		mColParts = parts;//����
		mV[0] = v0;
		mV[1] = v1;
		mV[2] = v2;
		mPriority = mColParts;
		mPosition.x = (v0.x + v1.x + v2.x) / 3.0f;
		mPosition.y = (v0.y + v1.y + v2.y) / 3.0f;
		mPosition.z = (v0.z + v1.z + v2.z) / 3.0f;
		CCollisionManager::Get()->Add(this);
	}
	//�R���C�_�̕`��
	void Render() {
		//���F�ɐݒ�
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		CVector3 v1 = mV[1] - mV[0];
		CVector3 v2 = mV[2] - mV[0];
		//�@�������߂�
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
�J�v�Z���R���C�_
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
		mpParent = parent;//�e�ւ̃|�C���^
		mpCombinedMatrix = matrix;//�A������{�[���̍����s��
		mV[0] = v0;//���̒[���W
		mV[1] = v1;//���̒[���W
		mRadius = radius;//���a
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
	//���[���h���W��ł̃R���C�_���擾����
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
	//�`��
	void Render() {
		//���F�ɐݒ�
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		glPushMatrix();
		//�R���C�_�����[���h���W�̈ʒu�ֈړ�
		glMultMatrixf(mpCombinedMatrix->f);
		//���̕`��
		glBegin(GL_LINES);
		glVertex3f(mV[0].x, mV[0].y, mV[0].z);
		glVertex3f(mV[1].x, mV[1].y, mV[1].z);
		glEnd();
		glPopMatrix();

		CMatrix44 mat;
		glPushMatrix();
		//�R���C�_�����[���h���W�̈ʒu�ֈړ�
		mat.translate((mV[0]) * *mpCombinedMatrix + CVector3(0.0f, mRadius, 0.0f));
		glMultMatrixf(mat.f);
		//���̕`��
		glutWireSphere(mRadius, 20, 20);
		glPopMatrix();

	}

};


/*27
�R���W�����N���X�̒�`
�Փ˔�����s�����\�b�h��
��`���܂��B
*/
class CCollision {
public:
	//���R���C�_�Ƌ��R���C�_�̏Փ˔���
	static bool Sphere(CCollider*, CCollider*);
	//29 �J�v�Z���ƎO�p�`�̏Փ˔���
	static bool CapsuleTriangle(CCollider*, CCollider*, CVector3 *);
	//29 �����ƎO�p�`�̏Փ˔���
	static bool LineTriangle(const CVector3 &p0, const CVector3 &p1, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust);
	//29 �_���O�p�`���ɑ��݂��邩�̔���
	static bool PointInTriangle(const CVector3 &p0, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &n);
	//30 ���ƎO�p�`�̏Փ˔���
	static bool SphereTriangle(const CVector3 &c, float r, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust);
};



#endif
