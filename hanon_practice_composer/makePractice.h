#pragma once
#include "Individual.h"

class makePractice {
public:
	//変数系
	Individual* Ind[MusicNum];//個体。
	int selectedNum = -1;

	//関数系
	makePractice(int selectNum);
	~makePractice();
	void printResult();
private:
	data_controller* Cont;//データをいじいじするクラスへのポインタ。たぶんプライベートでいい
	Individual* newInd[MusicNum];//次世代
};