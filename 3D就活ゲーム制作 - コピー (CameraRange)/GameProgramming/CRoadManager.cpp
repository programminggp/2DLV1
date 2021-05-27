#include "CRoadManager.h"
#include "CPoint.h"
#include "CEnemy.h"

#define START_INDEX 0 //�����J�n�ʒu
#define COURSE_POINT_SIZE 120.0f //�|�C���g�R���C�_�̃T�C�Y

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

	//size�F�O�p�`�̌�
	int size = pmodel->mTriangles.size();
	int last = size; //�z��̍Ō�
	//�O�p�`�̌����̍��W��z��Ŏ���
	CVector* mpPoint = new CVector[size];
	for (int i = 0; i < size; i++)
	{
		//�O�p�`�����[���h���W�ɕϊ�
		CVector v[3];
		v[0] = pmodel->mTriangles[i].mV[0] * mMatrix;
		v[1] = pmodel->mTriangles[i].mV[1] * mMatrix;
		v[2] = pmodel->mTriangles[i].mV[2] * mMatrix;
		//�O�p�`�̏d�S�����߂�
		mpPoint[i].mX = (v[0].mX + v[1].mX + v[2].mX) / 3.0f;
		mpPoint[i].mY = (v[0].mY + v[1].mY + v[2].mY) / 3.0f;
		mpPoint[i].mZ = (v[0].mZ + v[1].mZ + v[2].mZ) / 3.0f;
	}

	int start = START_INDEX; //�J�n����ԍ�
	float min = FLT_MAX; //FLT_MAX ��float�^�̍ő�l
	float len; //����
	CVector vector; //�����Ȃ�

	//startPos�����ԋ߂��|�C���g�����߂�
	for (int i = 0; i < size; i++)
	{
		//���������߂�
		vector = mpPoint[i] - startPos;
		//���������߂�
		len = vector.Length();
		if (len < min)
		{
			start = i;
			min = len;
		}
	}
	std::vector<CVector> vecPoint;
	//��Ԗڂ̃|�C���g��ǉ�����
	vecPoint.push_back(mpPoint[start]);
	//�z��̗v�f���폜���A�Ō�����Z����
	mpPoint[start] = mpPoint[--last];

	//2�Ԗڂ����߂�
	//1�Ԗڂ���i�s�����ň�Ԃ������|�C���g��T��
	start = 0;
	min = FLT_MAX;
	for (int i = 0; i < last; i++)
	{
		vector = mpPoint[i] - vecPoint[vecPoint.size() - 1];
		//�i�s�������������̑Ώ�
		if (vector.Dot(foward) > 0.0f)
		{
			//�ł��߂��|�C���g��T��
			if (min > vector.Length())
			{
				min = vector.Length();
				start = i;
			}
		}
	}
	vecPoint.push_back(mpPoint[start]);
	mpPoint[start] = mpPoint[--last];

	//3�Ԗڈȍ~�����߂�
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

	//�|�C���g�z�񂩂琳���ȃ|�C���g�𐶐�����
	//�|�C���g�z��̌ォ��O�Ɍ������č쐬
	CPoint* next;
	//lastPoint�F�Ō�̃|�C���g����쐬
	CPoint* lastPoint = next = new CPoint((vecPoint[size - 1] + vecPoint[size - 2]) * 0.5f, COURSE_POINT_SIZE);
	CVector length;
	const int between = 4; // �|�C���g�̊Ԋu�萔�@���Ȃ��Ƒ����z�u����
	//�|�C���g�Ԃ̋������R���g���[������
	float betweenPoint = COURSE_POINT_SIZE * between;
	for (int i = size - 3; i >= 0; i -= 2) {
		length = (vecPoint[i] + vecPoint[i - 1]) * 0.5f - next->mPosition;
		if (length.Length() > betweenPoint)
		{
			next = new CPoint((vecPoint[i] + vecPoint[i - 1]) * 0.5f, COURSE_POINT_SIZE, next);
		}
	}
	lastPoint->Set((vecPoint[size - 1] + vecPoint[size - 2]) * 0.5f, COURSE_POINT_SIZE, next);
	//�ŏ��̖ڕW��ݒ�
	CEnemy::mPoint = next->GetNextPoint();
	//�z��̍폜
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
