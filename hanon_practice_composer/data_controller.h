#pragma once
#include <iostream>
#include <string>


//定数定義(ポインタで示さなくても使えたほうが良いやつ)
const int Lega = 3;//最長の長さ(八分音符基準)
const int Stac = 1;//最短の単位(八分音符基準)
const int meloMakeNum = 7;//メロディ作成数合計
const int meloMakeFrag = 2;//一度に作成するメロディ
const int meloMakeRep = 2;//メロディ作成繰り返し回数


class data_controller{
public:
	//定数定義する
	int chord[3];//chord.csvのデータ数:3
	int key[24][3];//key.csvのデータ数:72
	int keynoteOrder[7][2];//keynote_order.csvのデータ数:14
	int notes[7];//notes.csvのデータ数(7)
	int scaleTKeynote[5][3];//scale_tmp_keynote.csvのデータ数(15)

	//関数
	data_controller();
	~data_controller();
private:
	const static int dataNum = 5;
	std::string toRead[dataNum] = { "chord.csv", "key.csv", "keynote_order.csv", "notes.csv", "scale_tmp_keynote.csv" };//あんまよくないかもけど解決分からんかった許して
	
	//関数
	void readData(std::string fileName);
};