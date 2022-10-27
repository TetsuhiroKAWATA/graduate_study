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
	const static int mkNum = 300;
	char mkPath[mkNum];


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
	void mutate();
	void loadChrom(int Num);

	void printChrom();
private:
	int seekTP(std::string tmpS, int num);//���O��seekTP�����ǁATP�ł͂Ȃ�chrom�̓Y������Ԃ��֐�
	int defNoteNum(std::string tmpS, int num);//�Ώۂ�C4���̗v�f�𐔒l�ɕϊ����� �����F�ϊ������������A���̕����̓Y����(chrom��)

	void printMelody(std::string fileName, int i, int j, std::ofstream& fout);
	void printAccom(std::string fileName, int I, std::ofstream& fout);
	int seekNote(std::string* randomTable, std::string tmpS, int* nowChordNum, int* noteRange, int noteHei);//�אډ���I������֐��A1~20�ɂ͑����g���Ȃ�
	void decidePT(int PTnum, int range1, int range2);//���Y�������߂�֐�(����:PT�̐��A�Ώۂ�chrom�͈̔�)
};