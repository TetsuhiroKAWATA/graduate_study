#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controller�̂ۂ���
	data_controller* data;

	//�ϐ�
	//int productNum;
	std::string chrom[128];
	int point;//�]���_
	int points[crossNum];//�����_��ۑ�����ꏊ


	//�֐�
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
	int decideNoteNum(int lower, int upper);//lower�ȏ�upper�ȉ�(�ȉ��I)�̗������o�������Ȃ̂Ŏg���܂킵�͂�������
	void cross(Individual* p1, Individual* p2);
	void sort(int lb, int ub);
	void printResult();
	void printMusic(int Num);
	void print(std::string fileName);

	void printChrom();
private:
	int seekTP(std::string tmpS, int num);//���O��seekTP�����ǁATP�ł͂Ȃ�chrom�̓Y������Ԃ��֐�
	int defNoteNum(std::string tmpS, int num);//�Ώۂ�C4���̗v�f�𐔒l�ɕϊ����� �����F�ϊ������������A���̕����̓Y����(chrom��)

	void printMelody(std::string fileName, int i, int j, std::ofstream& fout);
	void printAccom(std::string fileName, int i, std::ofstream& fout);
};