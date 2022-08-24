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
	void printResult();
	void dataPrepare();
private:
	//data_controller* Cont;//データをいじいじするクラスへのポインタ。たぶんプライベートでいい->ダメでした。当たり前だよなぁ！？
	Individual* newInd[MusicNum];//次世代
	char* toRead;
	std::string makePass;
};