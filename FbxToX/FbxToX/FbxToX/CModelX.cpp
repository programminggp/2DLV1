#include <stdio.h>
#include <string.h>
#include "CModelX.h"

float CModelX::GetFloatToken()
{
	GetToken();
	//atof
	//�������float�^�֕ϊ�
	return atof(mToken);
}

CModelX::~CModelX()
{
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
	for (size_t i = 0; i < mAnimationSet.size(); i++)
	{
		delete mAnimationSet[i];
	}
	//�}�e���A���̉��
	for (size_t i = 0; i < mMaterial.size(); i++) {
		delete mMaterial[i];
	}
}

void CModelX::SkipNode()
{
	//�������I�������I��
	while (*mpPointer != '\0') {
		GetToken();	//���̒P��擾
		//{�����������烋�[�v�I��
		if (strchr(mToken, '{')) break;
	}
	int count = 1;
	//�������I��邩�A�J�E���g��0�ɂȂ�����I��
	while (*mpPointer != '\0' && count > 0) {
		GetToken();	//���̒P��擾
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{')) count++;
		//}��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}')) count--;
	}
}

CModelX::CModelX()
	: mpPointer(nullptr)
	, mLoaded(false)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}

void CModelX::Load(const char* file) {
	//
	//�t�@�C���T�C�Y���擾����
	//
	FILE* fp;	//�t�@�C���|�C���^�ϐ��̍쐬
	fp = fopen(file, "rb");	//�t�@�C�����I�[�v������
	if (fp == NULL) {	//�G���[�`�F�b�N
		printf("fopen error:%s��n", file);
		return;
	}

	//�t�@�C���̍Ō�ֈړ�
	fseek(fp, 0L, SEEK_END);
	//�t�@�C���T�C�Y�̎擾
	int size = ftell(fp);
	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
	char* buf = mpPointer = new char[size + 1];
	//
	//�t�@�C������3D���f���̃f�[�^��ǂݍ���
	//
	//�t�@�C���̐擪�ֈړ�
	fseek(fp, 0L, SEEK_SET);
	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	fread(buf, size, 1, fp);
	//�Ō��\0��ݒ肷��i������̏I�[�j
	buf[size] = '\0';
	fclose(fp);	//�t�@�C�����N���[�Y����

	CFbxModel* pFbx = nullptr;
	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();	//�P��̎擾
//		if (strcmp(mToken, "Model::Model") == 0)
		if (strcmp(mToken, "Mesh")== 0 )
		{
			pFbx = new CFbxModel(this);
			break;
		}
	}

	if (pFbx != nullptr) delete pFbx;

	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���J������

}

bool CModelX::IsLoaded()
{
	return mLoaded;
}

std::vector<CModelXFrame*>& CModelX::Frames()
{
	return mFrame;
}

bool CModelX::EOT()
{
	return *mpPointer == '\0';
}

/*
GetToken
������f�[�^����A�P���1�擾����
*/
char* CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	do {
		p = mpPointer;
		q = mToken;

		//�^�u(\t)��( )���s(\r)(\n)�C�G�h�̋�؂蕶���ȊO�ɂȂ�܂œǂݔ�΂�
		while (*p != '\0' && IsDelimiter(*p)) p++;
		if (*p == '\"') {
			p++;
			//�^�u(\t)��( )���s(\r)(\n)�C�G�h�̋�؂蕶���A
			//�܂��́A}�̕����ɂȂ�܂�mToken�ɑ������
			while (*p != '\0' && *p != '\"')
				*q++ = *p++;
			if (*p == '\"')
				p++;
		}
		else if (*p == '{' || *p == '}') {
			//{�܂���}�Ȃ�mToken�ɑ�������̕�����
			*q++ = *p++;
		}
		else {
			//�^�u(\t)��( )���s(\r)(\n)�C�G�h�̋�؂蕶���A
			//�܂��́A}�̕����ɂȂ�܂�mToken�ɑ������
			while (*p != '\0' && !IsDelimiter(*p) && *p != '}')
				*q++ = *p++;
		}
		*q = '\0';	//mToken�̍Ō��\0����
		mpPointer = p;	//���̓ǂݍ��ރ|�C���g���X�V����

	} while (strlen(mToken) == 0 && *p != '\0');


	//����mToken��//�̏ꍇ�́A�R�����g�Ȃ̂ŉ��s�܂œǂݔ�΂�
	/*
	strcmp(������1, ������2)
	������1�ƕ�����2���������ꍇ�A0��Ԃ��܂��B
	������1�ƕ�����2���������Ȃ��ꍇ�A0�ȊO��Ԃ��܂��B
	*/
	if (!strcmp("//", mToken)) {
		//���s�܂œǂݔ�΂�
		while (*p != '\0' && !strchr("\r\n", *p)) p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾����i�ċA�Ăяo���j
		return GetToken();
	}
	return mToken;
}

char* CModelX::Token()
{
	return mToken;
}

#include <ctype.h>	//isspace�֐��̐錾
/*
* IsDelimiter(c)
* c��\t \r \n �X�y�[�X�Ȃǂ̋󔒕���
* �܂��́A,:"�Ȃǂ̕����ł����
* ��؂蕶���Ƃ���true��Ԃ�
*/
bool CModelX::IsDelimiter(char c)
{
	if (c < 0) return false;
	//isspace(c)
	//c���󔒕����Ȃ�0�ȊO��Ԃ�
	if (isspace(c) != 0)
		return true;
	/*
	strchr(������, ����)
	������ɕ������܂܂�Ă���΁A
	�������������ւ̃|�C���^��Ԃ�
	������Ȃ�������NULL��Ԃ�
	*/
	//if (strchr(",;\"", c) != NULL)
	if (strchr(",;", c) != NULL)
		return true;
	//��؂蕶���ł͂Ȃ�
	return false;
}

CFbxModel::CFbxModel(CModelX* p)
	: mpModelX(p)
	, mState(EState::EZERO)
{
	while (p->GetToken()[0] != '\0') {
		switch (mState)
		{
		case EState::EZERO:
			CheckState();
			if (strcmp(p->Token(), "Properties60:") == 0)
			{
				p->SkipNode();
			}
			else if (strcmp(p->Token(), "Model:") == 0)
			{
				//break;
			}
			else if (strcmp(p->Token(), "Vertices:") == 0)
			{
				mState = EState::EVERTICES;
				printf("\n%s\n", p->Token());
			}
			break;
		case EState::EVERTICES:
			if (strcmp(p->Token(), "PolygonVertexIndex:") == 0)
			{
				mState = EState::EPOLYGONVERTEXINDEX;
				printf("\n%s\n", p->Token());
			}
			else
			{
				mVertices.push_back(atof(p->Token()));
				printf("%s,", p->Token());
			}
			break;
		case EState::EPOLYGONVERTEXINDEX:
		{
			int i = atoi(p->Token());
			if (i != 0)
			{
				mIndexes.push_back(i);
				printf("%s,", p->Token());
			}
			else if (isdigit(p->Token()[0]))
			{
				mIndexes.push_back(i);
				printf("%s,", p->Token());
			}
			else
			{
				mState = EState::EZERO;
			}
		}
			break;
		case EState::ENORMALS:
			if (strcmp(p->Token(), "}") == 0)
			{
				mState = EState::EZERO;
//				printf("\n%s\n", p->Token());
			}
			else
			{
				mNormals.push_back(atof(p->Token()));
				printf("%s,", p->Token());
			}
			break;
		}
	}
}

CFbxModel::EState CFbxModel::CheckState()
{
	if (strcmp(mpModelX->Token(), "Vertices:") == 0)
	{
		mState = EState::EVERTICES;
	}
	else if (strcmp(mpModelX->Token(), "PolygonVertexIndex:") == 0)
	{
		mState = EState::EPOLYGONVERTEXINDEX;
	}
	else if (strcmp(mpModelX->Token(), "Normals:") == 0)
	{
		mState = EState::ENORMALS;
		printf("\n%s\n", mpModelX->Token());
	}
	else
	{
		//mState = EState::EZERO;
	}
	return mState;
}
