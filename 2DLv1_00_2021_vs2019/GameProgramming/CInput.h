#ifndef CINPUT_H
#define CINPUT_H

/*
CInput�N���X
���͂��擾����
*/
class CInput {
	bool mFlg[256];
public:
	CInput();
	/*
	key�̒l�̃L�[��������Ă����true���A
	������Ă��Ȃ����false��߂�
	*/
	bool Key(char key);
	/*
	key�̒l�̃L�[�������ꂽ�u�Ԃ���true���A
	����ȊO��false��߂�
	*/
	bool KeyOP(char key);
};

#endif
