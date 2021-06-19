#include "CRoadManager.h"
#include "CPoint.h"
#include "CEnemy.h"

#define RADIUS 120.0f

//CRoadManager(���f���f�[�^�̃|�C���^,�ʒu,��],�g��k��,�X�^�[�g�ʒu,�i�s����)
CRoadManager::CRoadManager(CModel* model, const CVector& position, const CVector& rotation, const CVector& scale, const CVector& startPos, const CVector& foward)
	: CObjFloor(model, position, rotation, scale)
{
	Init(model, position, rotation, scale, startPos, foward);
}

void CRoadManager::Init(CModel* pmodel, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward)
{
	//mMatrix�̍X�V
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	CCharacter::Update();


	//�����P�@�O�p�`�|���S���̏d�S���W�����߂Ĕz��ɂ���
	//�i�P�jpmodel����O�p�`�|���S���̐����擾����
	int triangle_size = pmodel->mTriangles.size();
	//printf("�O�p�`�|���S���̐��F%d\n", triangle_size);

	//�i�Q�j�|���S���̐����x�N�g���̔z����쐬����B
	CVector* polygonarray;
	polygonarray = new CVector[triangle_size];

	////�i�R�j�O�p�`�|���S���̊e���_��mMatrix���|���ă��[���h���W�����߁A�O�p�`�̏d�S�̍��W�����߂�
	////�e�R���C�_�̒��_�����[���h���W�֕ϊ�//�Q�l
	//v[0] = y->mV[0] * y->mMatrix * y->mpParent->mMatrix;
	//v[1] = y->mV[1] * y->mMatrix * y->mpParent->mMatrix;
	//v[2] = y->mV[2] * y->mMatrix * y->mpParent->mMatrix;
	for (int i = 0; i < triangle_size; i++) {
		CVector v[3], sv;
		v[0] = pmodel->mTriangles[i].mV[0] * mMatrix;
		v[1] = pmodel->mTriangles[i].mV[1] * mMatrix;
		v[2] = pmodel->mTriangles[i].mV[2] * mMatrix;
		sv = CVector((v[0].mX + v[1].mX + v[2].mX) / 3.0f, (v[0].mY + v[1].mY + v[2].mY) / 3.0f, (v[0].mZ + v[1].mZ + v[2].mZ) / 3.0f);
		//�i�S�j�z��̃x�N�g���̒l�ɁA�O�p�`�|���S���̏d�S���W�������Ă���
		polygonarray[i] = sv;
	}

	//�����Q�@�擪�f�[�^�̒T��
	//�d�S���W�̔z�񂩂�A�X�^�[�g�ʒu�ɍł��߂��d�S�����߂�B
	//���߂��d�S�Ɣz��̐擪�����ւ���B
	CVector spos = startPos;
	CVector vdist;
	CVector nearestvec = CVector(0.0f, 0.0f, 0.0f);
	int nearest_arraynum;
	for (int i = 0; i < triangle_size; i++) {
		vdist = spos - polygonarray[i];
		//��ԍŏ��̏d�S���W�͖������ɍł��߂����̂Ƃ���
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
	//���߂��d�S�Ɣz��̐擪�����ւ���B
	CVector temp = polygonarray[0];
	polygonarray[0] = polygonarray[nearest_arraynum];
	polygonarray[nearest_arraynum] = temp;


	//�����R�@2�Ԗڃf�[�^�̒T��
	//�d�S���W��2�Ԗڈȍ~�̔z��ɂ��āA�擪�̃f�[�^����i�s�����ɂ���d�S�̒��ŁA
	//�ł��擪�ɋ߂��d�S��T���A�z���2�ԖڂƓ���ւ���B
	CVector poly_forward = foward;
	float sdot = 0;
	int sArraynum = 0;
	bool isfirst = true;
	for (int i = 0 + 1; i < triangle_size; i++) {
		CVector dir = polygonarray[i] - polygonarray[0];
		//printf("���ρF%8.2f\n", polygonarray[i].Dot(polygonarray[i] - polygonarray[0]));

		//���ς��v���X�ɂȂ���̂����
		if (poly_forward.Dot(polygonarray[i] - polygonarray[0]) > 0) {
			//���̒��ōł�polygonarray[0]�Ƌ߂����̂�[1]�ƂȂ�
			vdist = polygonarray[i] - polygonarray[0];
			//��ԍŏ��̃v���X���ς͂����ݒ�
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

	//�����S�@3�Ԗڈȍ~�̃f�[�^�̕��ѕς�
	//�z���3�Ԗڈȍ~�ɂ��Ĉȉ��̎菇�ŕ��ѕς���
	//�i�P�j���݈ʒu��3�Ԗڂɂ���
	//�i�Q�j���݈ʒu�̈�O�̒l�ɍł��߂��d�S��T���A���݈ʒu�Ɠ���ւ���
	//�i�R�j���݈ʒu������ɂ��āA�i�Q�j���J��Ԃ�	
	sArraynum = 0;
	for (int i = 2; i < triangle_size; i++) {
		//i�Ԗڂ��O�̃f�[�^�͕��ѕς��̑ΏۂɂȂ�Ȃ�
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
	////�z��S�Ă̍��W���o�͂���
	//for (int i = 0; i < triangle_size; i++){
	//	printf("[%3d]   X:%10.2f  Y:%10.2f  Z:%10.2f�@�@ �X�^�[�g�n�_����̋����F%8.2f\n", i, polygonarray[i].mX, polygonarray[i].mY, polygonarray[i].mZ, (spos - polygonarray[i]).Length());
	//}

	//�����T�@�d�S�̔z�񂩂�CPoint�𐶐�����
	//�i�P�j�z��̍Ō�ƍŌォ��1�O�̏d�S���A���ԍ��W�����߁ACPoint�𐶐�����B
	//�i�Q�j�z��̌�3�ڂ���O�Ɍ����āA2�����ԍ��W������CPoint�𐶐�����B
	//�i�R�j�������I���ƁA�ŏ��ɍ쐬����CPoint�̎��|�C���^�ɍŌ��CPoint�̃|�C���^��������
	CPoint* next, * first;
	CVector center;
	isfirst = true;
	for (int i = triangle_size - 1; i >= 0; i -= 2) {
		//���S���W
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
	//�ŏ��ɐ��������|�C���^�̎��|�C���^�̐ݒ�
	first->Set(first->mPosition, 120, next);
	//�ŏ��̖ڕW��ݒ�
	CEnemy::mPoint = next->GetNextPoint();

	delete[] polygonarray;
}
