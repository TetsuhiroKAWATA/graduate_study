#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controller�̂ۂ���
	data_controller* data;

	//�ϐ�
	int productNum;
	std::string chrom[128];
	int point;


	//�֐�
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
	int decideNoteNum(int lower, int upper);//lower�ȏ�upper�ȉ�(�ȉ��I)�̗������o�������Ȃ̂Ŏg���܂킵�͂�������
private:
	int seekTP(std::string tmpS, int num);//���O��seekTP�����ǁATP�ł͂Ȃ�chrom�̓Y������Ԃ��֐�
	int defNoteNum(std::string tmpS, int num);//�Ώۂ�C4���̗v�f�𐔒l�ɕϊ����� �����F�ϊ������������A���̕����̓Y����(chrom��)
};