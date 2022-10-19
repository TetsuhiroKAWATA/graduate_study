#pragma once
#include "Individual.h"

class makePractice {
public:
	//変数系
	Individual* Ind[MusicNum];//個体。
	data_controller* Cont;//データいじいじ->staticつけたらうごかなくなったわ

	//関数系
	makePractice(int selectNum);
	~makePractice();
	void printResult(int Num);
	void printMusic(int Num);
	void dataPrepare();
	void firstTake();
	void sort(int lb, int ub);
	void alternate();
private:
	//data_controller* Cont;//データをいじいじするクラスへのポインタ。たぶんプライベートでいい->ダメでした。当たり前だよなぁ！？
	Individual* newInd[MusicNum];//次世代
	char* toRead;
	std::string makePass;
	int select(int pointSum, int p1Num);
};