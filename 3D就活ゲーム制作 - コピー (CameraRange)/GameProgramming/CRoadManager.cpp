#include "CRoadManager.h"
#include "CPoint.h"
#include "CEnemy.h"
#include "CSceneTitle.h"

//CRoadManager(���f���f�[�^�̃|�C���^,�ʒu,��],�g��k��,�X�^�[�g�ʒu,�i�s����,�e�|�C���g�̔��a,�|�C���g�Ԃ̍ŏ��̊Ԋu)
CRoadManager::CRoadManager(CModel *model, const CVector& position, const CVector& rotation, const CVector& scale, const CVector& startPos, const CVector& foward, const float radius, const float interval)
: CObjFloor(model, position, rotation, scale)
{
	Init(model, position, rotation, scale, startPos, foward, radius, interval);
}

void CRoadManager::Init(CModel* pmodel, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward, const float radius, const float interval)
{
	//mMatrix�̍X�V
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	float rad = radius;
	CCharacter::Update();	

	//�R�[�XA�̃|�C���g�͂����ō쐬
	if (CSceneTitle::mCource == 1){
		CPoint *next, *first;
		first = next = new CPoint(CVector(340.0f, 30.0f, -1182.0f), rad, nullptr);
		next = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), rad, next);
		next = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), rad, next);
		next = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), rad, next);
		next = new CPoint(CVector(258.0f, 30.0f, 2000.0f), rad, next);
		next = new CPoint(CVector(413.0f, 30.0f, 1300.0f), rad, next);
		next = new CPoint(CVector(340.0f, 30.0f, -1182.0f), rad, next);
		next = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), rad, next);
		next = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), rad, next);
		next = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), rad, next);
		next = new CPoint(CVector(258.0f, 30.0f, 2000.0f), rad, next);
		next = new CPoint(CVector(413.0f, 30.0f, 1300.0f), rad, next);
		////�ŏ��ɐ��������|�C���^�̎��|�C���^�̐ݒ�
		first->Set(first->mPosition, rad, next);
		//�ŏ��̖ڕW��ݒ�
		CEnemy::mPoint = next->GetNextPoint();
		return;
	}
	else if (CSceneTitle::mCource == 2){
		CPoint *next, *first;
		first = next = new CPoint(CVector(2128.0f*1.1f, 30.0f, -3026.0f*1.1f), rad, nullptr);
		next = new CPoint(CVector(1317.0f*1.1f, 30.0f, -3865.0f*1.1f), rad, next);
		next = new CPoint(CVector(529.0f*1.1f, 30.0f, -3565.0f*1.1f), rad, next);
		next = new CPoint(CVector(-721.0f*1.1f, 30.0f, -1926.0f*1.1f), rad, next);
		next = new CPoint(CVector(-1500.0f*1.1f, 30.0f, -80.0f*1.1f), rad, next);
		next = new CPoint(CVector(-2652.0f*1.1f, 30.0f, 113.0f*1.1f), rad, next);
		next = new CPoint(CVector(-3355.0f*1.1f, 30.0f, 809.0f*1.1f), rad, next);
		next = new CPoint(CVector(-3127.0f*1.1f, 30.0f, 1432.0f*1.1f), rad, next);
		next = new CPoint(CVector(-2528.0f*1.1f, 30.0f, 1832.0f*1.1f), rad, next);
		next = new CPoint(CVector(-1645.0f*1.1f, 30.0f, 3612.0f)*1.1f, rad, next);
		next = new CPoint(CVector(-700.0f*1.1f, 30.0f, 4935.0f*1.1f), rad, next);
		next = new CPoint(CVector(463.0f*1.1f, 30.0f, 5010.0f*1.1f), rad, next);
		next = new CPoint(CVector(1212.0f*1.1f, 30.0f, 4516.0f*1.1f), rad, next);
		next = new CPoint(CVector(1719.0f*1.1f, 30.0f, 3250.0f*1.1f), rad, next);
		next = new CPoint(CVector(3240.0f*1.1f, 30.0f, 2207.0f*1.1f), rad, next);
		next = new CPoint(CVector(3737.0f*1.1f, 30.0f, 1280.0f*1.1f), rad, next);
		next = new CPoint(CVector(3763.0f*1.1f, 30.0f, 510.0f*1.1f), rad, next);
		next = new CPoint(CVector(3068.0f*1.1f, 30.0f, -355.0f*1.1f), rad, next);
		

		next = new CPoint(CVector(2568.0f*1.1f, 30.0f, -575.0f*1.1f), rad, next);
		next = new CPoint(CVector(2352.0f*1.1f, 30.0f, -925.0f*1.1f), rad, next);

		next = new CPoint(CVector(2285.0f*1.1f, 30.0f, -2140.0f*1.1f), rad, next);
		////�ŏ��ɐ��������|�C���^�̎��|�C���^�̐ݒ�
		first->Set(first->mPosition, rad, next);
		//�ŏ��̖ڕW��ݒ�
		CEnemy::mPoint = next->GetNextPoint();
		return;
	}

	//�O�p�`�|���S���̏d�S���W�����߂Ĕz��ɂ���
	int triangle_size = pmodel->mTriangles.size();	
	//�|���S���̐����x�N�g���̔z����쐬����
	CVector *polygonarray;
	polygonarray = new CVector[triangle_size];

	//�O�p�`�|���S���̊e���_��mMatrix���|���ă��[���h���W�����߁A�O�p�`�̏d�S�̍��W�����߂�
	for (int i = 0; i < triangle_size; i++){
		CVector v[3], sv;
		v[0] = pmodel->mTriangles[i].mV[0] * mMatrix;
		v[1] = pmodel->mTriangles[i].mV[1] * mMatrix;
		v[2] = pmodel->mTriangles[i].mV[2] * mMatrix;
		sv = CVector((v[0].mX + v[1].mX + v[2].mX) / 3.0f, (v[0].mY + v[1].mY + v[2].mY) / 3.0f, (v[0].mZ + v[1].mZ + v[2].mZ) / 3.0f);
		//�z��̃x�N�g���̒l�ɁA�O�p�`�|���S���̏d�S���W�������Ă���
		polygonarray[i] = sv;
	}

	/*�擪�f�[�^�̒T��*/
	//�d�S���W�̔z�񂩂�A�X�^�[�g�ʒu�ɍł��߂��d�S�����߂�B
	//���߂��d�S�Ɣz��̐擪�����ւ���B
	CVector spos = startPos;
	CVector vdist;
	CVector nearestvec = CVector(0.0f, 0.0f, 0.0f);
	int nearest_arraynum;
	for (int i = 0; i < triangle_size; i++){		
		vdist = spos - polygonarray[i];
		//��ԍŏ��̏d�S���W�͖������ɍł��߂����̂Ƃ���
		if (i == 0){
			nearestvec = vdist;
			nearest_arraynum = i;
		}
		else{
			if (vdist.Length() < nearestvec.Length()){
				nearestvec = vdist;
				nearest_arraynum = i;
			}
		}
	}
	//���߂��d�S�Ɣz��̐擪�����ւ���B
	CVector temp = polygonarray[0];
	polygonarray[0] = polygonarray[nearest_arraynum];
	polygonarray[nearest_arraynum] = temp;	
	

	//2�ԖڂƂȂ�f�[�^�̒T��
	//�d�S���W��2�Ԗڈȍ~�̔z��ɂ��āA�擪�̃f�[�^����i�s�����ɂ���d�S�̒��ŁA
	//�ł��擪�ɋ߂��d�S��T���A�z���2�ԖڂƓ���ւ���B
	CVector poly_forward = foward;
	float sdot = 0;
	int sArraynum = 0;
	bool isfirst = true;
	for (int i = 0 + 1; i < triangle_size; i++){
		CVector dir = polygonarray[i] - polygonarray[0];
		//printf("���ρF%8.2f\n", polygonarray[i].Dot(polygonarray[i] - polygonarray[0]));

		//���ς��v���X�ɂȂ���̂����
		if (poly_forward.Dot(polygonarray[i] - polygonarray[0]) > 0){
			//���̒��ōł�polygonarray[0]�Ƌ߂����̂�[1]�ƂȂ�
			vdist = polygonarray[i] - polygonarray[0];
			//��ԍŏ��̃v���X���ς͂����ݒ�
			if (isfirst){
				nearestvec = vdist;
				sArraynum = i;
				isfirst = false;
			}
			else{
				if (vdist.Length() < nearestvec.Length()){
					nearestvec = vdist;
					sArraynum = i;
				}
			}
		}
	}
	temp = polygonarray[1];
	polygonarray[1] = polygonarray[sArraynum];
	polygonarray[sArraynum] = temp;

	//3�Ԗڈȍ~�̃f�[�^�̕��ѕς�
	//�z���3�Ԗڈȍ~�ɂ��Ĉȉ��̎菇�ŕ��ѕς���
	//�i�P�j���݈ʒu��3�Ԗڂɂ���
	//�i�Q�j���݈ʒu�̈�O�̒l�ɍł��߂��d�S��T���A���݈ʒu�Ɠ���ւ���
	//�i�R�j���݈ʒu������ɂ��āA�i�Q�j���J��Ԃ�	
	sArraynum = 0;
	for (int i = 2; i < triangle_size; i++){
		//i�Ԗڂ��O�̃f�[�^�͕��ѕς��̑ΏۂɂȂ�Ȃ�
		isfirst = true;
		for (int j = i; j < triangle_size; j++){
			vdist = polygonarray[i - 1] - polygonarray[j];
			if (isfirst){
				nearestvec = vdist;
				sArraynum = j;
				isfirst = false;
			}
			else{
				if (vdist.Length() < nearestvec.Length()){
					nearestvec = vdist;
					sArraynum = j;
				}
			}
		}
		temp = polygonarray[i];
		polygonarray[i] = polygonarray[sArraynum];
		polygonarray[sArraynum] = temp;
	}

	//�d�S�̔z�񂩂�CPoint�𐶐�����
	//�i�P�j�z��̍Ō�ƍŌォ��1�O�̏d�S���A���ԍ��W�����߁ACPoint�𐶐�����B
	//�i�Q�j�z��̌�3�ڂ���O�Ɍ����āA2�����ԍ��W������CPoint�𐶐�����B
	//�i�R�j�������I���ƁA�ŏ��ɍ쐬����CPoint�̎��|�C���^�ɍŌ��CPoint�̃|�C���^��������
	CPoint *next, *first;
	CVector center;
	isfirst = true;
	for (int i = triangle_size - 1; i >= 0; i -= 2){
		//���S���W
		center = (polygonarray[i] + polygonarray[i - 1]) * (1.0f / 2.0f);
		if (isfirst){
			first = next = new CPoint(center, rad, nullptr);
			isfirst = false;
		}
		else{	
			if ((next->mPosition - center).Length() >= interval){
				/*if (CSceneTitle::mCource_Number == 2){
					if (center.mX > -249.0f && center.mX < -248.0f
						&& center.mZ > 5027.0f && center.mZ < 5028.0f
						&& center.mY > -5.0f && center.mY < -3.0f){
						CVector extrapoint = center;
						extrapoint.mX = -705.0f;
						extrapoint.mZ = 4848.0f;
						next = new CPoint(extrapoint, rad, next);
					}
					else if (center.mX > 1417.0f && center.mX < -1418.0f
						&& center.mZ > 4000.0f && center.mZ < 4000.5f){
						CVector extrapoint = center;
						extrapoint.mX = 1211.0f;
						extrapoint.mZ = 4433.0f;
						next = new CPoint(extrapoint, rad, next);
					}
				}*/				
				next = new CPoint(center, rad, next);
				//if (CSceneTitle::mCource_Number == 2){
				//	if (center.mX > -1226.0f && center.mX < -1225.5f
				//		&& center.mZ > -597.5f && center.mZ < -597.0f){
				//		CVector extrapoint = center;
				//		/*extrapoint.mX = -1568.0f;
				//		extrapoint.mZ = -156.0f;*/
				//		extrapoint.mX = -1543.0f;
				//		extrapoint.mZ = -78.9f;
				//		next = new CPoint(extrapoint, rad, next);
				//	}
				//	if (center.mX > -3134.0f && center.mX < -3133.5f
				//		&& center.mZ > 442.5f && center.mZ < -443.0f){
				//		CVector extrapoint = center;
				//		/*extrapoint.mX = -1568.0f;
				//		extrapoint.mZ = -156.0f;*/
				//		extrapoint.mX = -2800.0f;
				//		extrapoint.mZ = 195.0f;
				//		next = new CPoint(extrapoint, rad, next);
				//	}
				//	if (center.mX > 1417.0f && center.mX < -1418.0f
				//		&& center.mZ > 4000.0f && center.mZ < 4000.5f){
				//		CVector extrapoint = center;
				//		/*extrapoint.mX = -1568.0f;
				//		extrapoint.mZ = -156.0f;*/
				//		extrapoint.mX = 1115.0f;
				//		extrapoint.mZ = 4540.0f;
				//		next = new CPoint(extrapoint, rad, next);
				//	}
				//}				
			}			
		}
		//printf("x:%f, y:%f, z:%f\n", center.mX, center.mY, center.mZ);
	}
	////�ŏ��ɐ��������|�C���^�̎��|�C���^�̐ݒ�
	first->Set(first->mPosition, rad, next);
	//�ŏ��̖ڕW��ݒ�
	CEnemy::mPoint = next->GetNextPoint();

	delete[] polygonarray;
}
