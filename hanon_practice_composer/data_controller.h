#pragma once
#include <iostream>
#include <string>

//’è”
const static int dataNum = 5;

class data_controller{
public:
	data_controller();
	~data_controller();
private:
	std::string toRead[dataNum] = { "chord.csv", "key.csv", "keynote_order.csv", "notes.csv", "scale_tmp_keynote.csv" };
	void readData(std::string fileName);
};