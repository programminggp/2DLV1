#ifndef CINPUT_H
#define CINPUT_H

/*
CInput�N���X
���͂��擾����
*/
class CInput {
public:
	static bool Flg[256];
	/*
	Key��static(�X�^�e�B�b�N)���\�b�h
	key�̒l�̃L�[��������Ă����true���A
	������Ă��Ȃ����false��߂�
	*/
	static bool Key(char key);
	static bool KeyOP(char key);
};

#endif
