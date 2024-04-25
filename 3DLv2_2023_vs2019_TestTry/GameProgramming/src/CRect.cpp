#include "CRect.h"

// �R���X�g���N�^�i�����Ȃ��j
CRect::CRect()
	: CRect(CVector2::zero, CVector2(100.0f, 100.0f))
{
}

// �R���X�g���N�^�ixywh�j
CRect::CRect(float x, float y, float w, float h)
	: CRect(CVector2(x, y), CVector2(w, h))
{
}

// �R���X�g���N�^�ipos + size�j
CRect::CRect(const CVector2& pos, const CVector2& size)
	: mPosition(pos)
	, mSize(size)
{
}

// �f�X�g���N�^
CRect::~CRect()
{
}

// ��`���̐ݒ�
void CRect::Set(float x, float y, float w, float h)
{
	Set(CVector2(x, y), CVector2(w, h));
}

// ��`���̐ݒ�iCVector2�j
void CRect::Set(const CVector2& pos, const CVector2& size)
{
	SetPos(pos);
	SetSize(size);
}

// ��`�̊J�n�ʒu��ݒ�
void CRect::SetPos(float x, float y)
{
	SetPos(CVector2(x, y));
}

// ��`�̊J�n�ʒu��ݒ�iCVector2�j
void CRect::SetPos(const CVector2& pos)
{
	mPosition = pos;
}

// ��`�̊J�n�ʒu���擾
const CVector2& CRect::GetPos() const
{
	return mPosition;
}

// ��`�̃T�C�Y��ݒ�
void CRect::SetSize(float w, float h)
{
	SetSize(CVector2(w, h));
}

// ��`�̃T�C�Y��ݒ�iCVector2�j
void CRect::SetSize(const CVector2& size)
{
	mSize = size;
}

// ��`�̃T�C�Y���擾
const CVector2& CRect::GetSize() const
{
	return mSize;
}

float CRect::X() const
{
	return mPosition.X();
}

void CRect::X(float x)
{
	mPosition.X(x);
}

float CRect::Y() const
{
	return mPosition.Y();
}

void CRect::Y(float y)
{
	mPosition.Y(y);
}

float CRect::W() const
{
	return mSize.X();
}

void CRect::W(float w)
{
	mSize.X(w);
}

float CRect::H() const
{
	return mSize.Y();
}

void CRect::H(float h)
{
	mSize.Y(h);
}
