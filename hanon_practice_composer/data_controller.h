#pragma once
#include <iostream>
#include <string>
#include <fstream>

//定数定義(ポインタで示さなくても使えたほうが良いやつ)
const int Lega = 3;//最長の長さ(八分音符基準)
const int Stac = 1;//最短の単位(八分音符基準)
const int meloMakeNum = 7;//メロディ作成数合計
const int meloMakeFrag = 2;//一度に作成するメロディ
const int meloMakeRep = 2;//メロディ作成繰り返し回数
const static int Kstuck = 30;//key.csv読み込み用の2次元配列の要素数その1
const static int Kline = 4;//上に同じその2
const static int Sstuck = 3;//scale_tmp_keynote.csv読み込み用の2次元配列の要素数その1
const static int Sline = 18;//上に同じその2
const static int MusicNum = 5;//作成する練習曲の数


class data_controller {
public:
	//定数定義する
	char chord[3] = { '1','3','5' }, notes[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'H' };
	char scaleTKeynote[Sstuck][Sline];
	char keynoteOrder[2][7] = { {'F', 'C', 'G', 'D', 'A', 'E', 'H'},{'H', 'E', 'A', 'D', 'G', 'C', 'F'} };
	char key[Kstuck][Kline];
	//chord:和音の音の位置、度数表記, key;調の名前と調号の種類と数、外部から読むわ, keynoteOrder:調号のつき方, 
	//notes:7音, scaleTKeynote:スケールの臨時記号の数と場所(度数表記)、外部から読む
	
	/*以下没、プログラム完成時点で削除
	int chord[3];//chord.csvのデータ数:3
	int key[24][3];//key.csvのデータ数:72
	int keynoteOrder[7][2];//keynote_order.csvのデータ数:14
	int notes[7];//notes.csvのデータ数(7)
	int scaleTKeynote[5][3];//scale_tmp_keynote.csvのデータ数(15)
	//ここまで。領域は最低限しか確保してないのでデータが増えたら領域も増やす必要がある。
	*/

	//関数
	data_controller();
	~data_controller();
private:
	//定数系

	//変数
	std::ifstream fin;
	std::string passer;
	char* tmpp;
	char textHolder[80];
	
	//関数
	void readData(std::string fileName, char* databox, int chunkNum, int lineNum);//linenum:key[30][3]の3のほう

	//確認用に3秒で作った関数、本筋には関係ない。
	//雑に作ったので確認の度に確認したい配列の名前をプログラムから指定する必要があるとかいう欠陥があります
	void confirmCorrect(int tate, int yoko);
};