#pragma once
#include "Individual.h"

class makePractice {
public:
	makePractice();
	~makePractice();
	void printResult();
private:
	data_controller* Cont;//�f�[�^��������������N���X�ւ̃|�C���^�B���Ԃ�v���C�x�[�g�ł���
	Individual* Ind[MusicNum];//�́B
};