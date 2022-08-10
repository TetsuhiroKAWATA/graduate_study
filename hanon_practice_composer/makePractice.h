#pragma once
#include "Individual.h"

class makePractice {
public:
	makePractice();
	~makePractice();
	void printResult();
private:
	data_controller* Cont;//データをいじいじするクラスへのポインタ。たぶんプライベートでいい
	Individual* Ind[MusicNum];//個体。
};