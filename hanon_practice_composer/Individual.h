#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controller‚Ì‚Û‚¢‚ñ‚½
	data_controller* data;

	//•Ï”
	int productNum;
	std::string chrom[128];
	int point;


	//ŠÖ”
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
	int decideNoteNum(int lower, int upper);//lowerˆÈãupperˆÈ‰º(ˆÈ‰ºI)‚Ì—”‚ğo‚·‚¾‚¯‚È‚Ì‚Åg‚¢‚Ü‚í‚µ‚Í‚«‚­‚©‚à
private:
};