#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

//Individualのprint関数では結構定数を使っているのでメロディ作成数とか変えた時はそこらへんも変更が必要

//定数(ポインタで示さなくても使えたほうが良いやつ)
//※ここに変数は置かない。全部constをつけろ
const static int MusicNum = 5;//作成する練習曲の数。当然最小値は2


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
const static int leftMax = 6;//左手の1小節音数最大
const static int chordKinds = 3;//楽曲内で使用されるコードの種類数
const static int noteHNum = 12;//ハノンの元曲において、1小節に含まれる最大の音数

//音域(上)
const static int scaleRange = 10;
const static int arpeRange = 10;
const static int octRange = 8;
const static int chroRange = 10;


const static double mutateProb = 0.005;//突然変異確率
const static int crossNum = 10;//crossNum点交叉
const static int restProb = 3;//restProb分の1でPが選ばれる(individual.cppのTP埋めの作業の時使われる)

//csakuraの場所
const static char resultMid[300] = "hpc\\sakura\\cSakura.exe";

class data_controller {
public:
	//データ
	int selectedNum = -999;//どの種別(基礎、スケールetc.)の練習をするか。

	char chord[4] = { '1','3','5', 0};
	char notes[15] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 0};
	//半音階専用の奴。これは変わらない(13-X)
	std::string chrNotes[2][24] = { {"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b", "c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b" },
									{"c", "b", "b-", "a", "a-", "g", "g-", "f", "e", "e-", "d", "d-", "c", "b", "b-", "a", "a-", "g", "g-", "f", "e", "e-", "d", "d-"} };
	std::string convNotes[15];//調に変換したNoteを入れる
	char scaleTKeynote[Sstuck][Sline];
	char keynoteOrder[2][7] = { {'f', 'c', 'g', 'd', 'a', 'e', 'b'},{'b', 'e', 'a', 'd', 'g', 'c', 'f'} };
	char key[Kstuck][Kline];
	//chord:和音の音の位置、度数表記, key;調の名前と調号の種類と数、外部から読むわ, keynoteOrder:調号のつき方, 
	//notes:7音, scaleTKeynote:スケールの臨時記号の数と場所(度数表記)、外部から読む

	//float GproductSum = 0.5;//作成されるIndividualに番号をつけるために使ってる数。
	int chromLen;//遺伝子の長さ
	int typeofChord;//和声or旋律。長調は2
	int hanonNum;//1~20で使用する楽曲番号
	int chordNum;//選択された調がkeyの何番目の要素であるか
	char chordProg[barNum*2];//コード進行(14151451とか)

	int noteNum[2];//[0]が最小音数、[1]が最大音数。noteNum[1]は必ずその小節に最小音節で最大まで音を入れた時の音数にしないといけない(4拍子なら8、3拍子なら6)
	int noteNumEnd[2];
	int beat;//拍子
	char accompany[chordKinds][leftMax];//伴奏の度数
	int accNoteNum;//伴奏の音数
	char hanon[3][noteHNum];//ハノン元曲を入れる場所,hanon[2][0]が最低音の度数、hanon[2][1]が最高音の度数

	int Xceil = -999;//Xの上限(1〜20で26が現在の最高値)

	int tempo = 150;

	int heiDiff = -999;//C durを基準として調の主音が何音上にあるかを格納すr

	//midi出力関係
	char mmlpath[100] = ".\\mml\\";
	char midpath[100] = ".\\";

	//関数
	data_controller();
	~data_controller();
	bool checkInt(std::string input);
	void readData(std::string fileName, char* databox, int chunkNum, int lineNum);//linenum:key[30][3]の3のほう
	void makeScale();
	void saveSNum();
	void saveChordNum();
	void saveMusicNum();
private:
	//定数系

	//変数
	std::ifstream fin;
	std::string passer;
	char* tmpp;
	char textHolder[80];
	
	//関数
	
	//確認用に3秒で作った関数、本筋には関係ない。
	//雑に作ったので確認の度に確認したい配列の名前をプログラムから指定する必要があるとかいう欠陥があります
	void confirmCorrect(int tate, int yoko);
};