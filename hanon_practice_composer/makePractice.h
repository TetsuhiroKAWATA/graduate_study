#pragma once
#include "Individual.h"

class makePractice {
public:
	//�ϐ��n
	Individual* Ind[MusicNum];//�́B
	int selectedNum = -1;

	//�֐��n
	makePractice(int selectNum);
	~makePractice();
	void printResult();
private:
	data_controller* Cont;//�f�[�^��������������N���X�ւ̃|�C���^�B���Ԃ�v���C�x�[�g�ł���
	Individual* newInd[MusicNum];//������
};