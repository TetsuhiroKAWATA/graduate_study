#pragma once
#include "Individual.h"

class makePractice {
public:
	//�ϐ��n
	Individual* Ind[MusicNum];//�́B
	data_controller* Cont;//�f�[�^��������->static�����炤�����Ȃ��Ȃ�����

	//�֐��n
	makePractice(int selectNum);
	~makePractice();
	void printResult();
	void dataPrepare();
private:
	//data_controller* Cont;//�f�[�^��������������N���X�ւ̃|�C���^�B���Ԃ�v���C�x�[�g�ł���->�_���ł����B������O����Ȃ��I�H
	Individual* newInd[MusicNum];//������
	char* toRead;
	std::string makePass;
};