#pragma once
#include "CVector.h"

// ��`�N���X
class CRect
{
public:
	// �R���X�g���N�^�i�����Ȃ��j
	CRect();
	// �R���X�g���N�^�ixywh�j
	CRect(float x, float y, float w, float h);
	// �R���X�g���N�^�ipos + size�j
	CRect(const CVector2& pos, const CVector2& size);
	// �f�X�g���N�^
	~CRect();

	/// <summary>
	/// ��`���̐ݒ�
	/// </summary>
	/// <param name="x">X���̊J�n�ʒu</param>
	/// <param name="y">Y���̊J�n�ʒu</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	void Set(float x, float y, float w, float h);
	/// <summary>
	/// ��`���̐ݒ�iCVector2�j
	/// </summary>
	/// <param name="pos">�J�n�ʒu</param>
	/// <param name="size">�T�C�Y</param>
	void Set(const CVector2& pos, const CVector2& size);

	/// <summary>
	/// ��`�̊J�n�ʒu��ݒ�
	/// </summary>
	/// <param name="x">X���̊J�n�ʒu</param>
	/// <param name="y">Y���̊J�n�ʒu</param>
	void SetPos(float x, float y);
	/// <summary>
	/// ��`�̊J�n�ʒu��ݒ�iCVector2�j
	/// </summary>
	/// <param name="pos">�J�n�ʒu</param>
	void SetPos(const CVector2& pos);
	/// <summary>
	/// ��`�̊J�n�ʒu���擾
	/// </summary>
	/// <returns></returns>
	const CVector2& GetPos() const;

	/// <summary>
	/// ��`�̃T�C�Y��ݒ�
	/// </summary>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	void SetSize(float w, float h);
	/// <summary>
	/// ��`�̃T�C�Y��ݒ�iCVector2�j
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(const CVector2& size);
	/// <summary>
	/// ��`�̃T�C�Y���擾
	/// </summary>
	/// <returns></returns>
	const CVector2& GetSize() const;

	float X() const;
	void X(float x);
	float Y() const;
	void Y(float y);
	float W() const;
	void W(float w);
	float H() const;
	void H(float h);

private:
	CVector2 mPosition;	// ��`�̊J�n�ʒu
	CVector2 mSize;		// ��`�̃T�C�Y
};
