#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controller�̂ۂ���
	data_controller* data;

	//�ϐ�
	int productNum;
	std::string chrom[128];


	//�֐�
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
private:
	int point;
};