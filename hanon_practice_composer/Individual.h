#pragma once
#include "data_controller.h"


class Individual {
public:
	//�ϐ�
	int productNum;
	std::string chrom[128];


	//�֐�
	Individual();
	~Individual();
	void firstTake(int selectNum);
private:
	int point;
};