#include "Individual.h"

Individual::Individual() {
	std::cout << "個体作った\n";
	//個体ナンバー管理(Ind[i]のiでやったほうが早そうだけどなんか別のこと考えてたんだよねたぶん・・・)
	GproductSum+=0.5;
	productNum = (int)GproductSum;
	point = -1;
	//初期化
	for (int i = 0; i < 128; i++) {
		chrom[i] = "-999";
	}
}

Individual::~Individual() {
	
}

void Individual::firstTake(int selectNum) {
	std::cout << "初期個体作成\n";//makePractice.cppで任意の数読んでるので大丈夫
	std::cout << "Debug::selectedNum = " << selectNum << '\n';
	switch (selectNum) {
	case 0:
		std::cout << "1~20の初期作成\n";
		//データの整備する
		if (chromLen == -999) {
			chromLen = 128;
		}

		break;
	case 1:
		std::cout << "スケールの初期集団作成\n";
		break;
	case 2:
		std::cout << "アルペジオの初期集団作成\n";
		break;
	case 3:
		std::cout << "オクターブの初期集団作成\n";

		break;
	case 4:
		std::cout << "半音階の初期集団作成\n";

		break;
	default:
		std::cout << "正しくない値\n";
		break;
	}
}