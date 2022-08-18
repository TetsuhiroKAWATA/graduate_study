#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

//定数(ポインタで示さなくても使えたほうが良いやつ)
//※ここに変数は置かない。全部constをつけろ
const int Lega = 3;//最長の長さ(八分音符基準)
const int Stac = 1;//最短の単位(八分音符基準)
const int meloMakeNum = 7;//メロディ作成数合計
const int meloMakeFrag = 2;//一度に作成するメロディ(小節数)
const int meloMakeRep = 2;//メロディ作成繰り返し回数(右手と左手で2の意味。基本的に変わらないと思う)
const static int barNum = 8;//作成する小節数(これも基本的に変わらないのでは)

const static int Kstuck = 24;//key.csv読み込み用の2次元配列の要素数その1,最大値は30
const static int Kline = 4;//上に同じその2
const static int Sstuck = 3;//scale_tmp_keynote.csv読み込み用の2次元配列の要素数その1
const static int Sline = 18;//上に同じその2
const static int MusicNum = 5;//作成する練習曲の数

//グローバル変数系
/*
static int chromLen = -999;//染色体の長さ。初期集団作るときに設定される
static char musicChord = NULL;//調
static int typeofChord = -999;//和声短音階or旋律短音階。和声が0、旋律が1でひとまず考えておく
static int hanonNum = -999;//ハノン1～20の楽曲の際にのみ使用する、楽曲番号を入れておく場所
*/

class data_controller {
public:
	//データ
	char chord[3] = { '1','3','5' }, notes[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'H' };
	char scaleTKeynote[Sstuck][Sline];
	char keynoteOrder[2][7] = { {'F', 'C', 'G', 'D', 'A', 'E', 'H'},{'H', 'E', 'A', 'D', 'G', 'C', 'F'} };
	char key[Kstuck][Kline];
	//chord:和音の音の位置、度数表記, key;調の名前と調号の種類と数、外部から読むわ, keynoteOrder:調号のつき方, 
	//notes:7音, scaleTKeynote:スケールの臨時記号の数と場所(度数表記)、外部から読む

	float GproductSum = 0.5;//作成されるIndividualに番号をつけるために使ってる数。
	int chromLen = -999;
	//char musicChord = NULL;
	int typeofChord = -999;
	int hanonNum = -999;
	int chordNum = -999;
	char chordProg[barNum];

	//関数
	data_controller();
	~data_controller();
	bool checkInt(std::string input);
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