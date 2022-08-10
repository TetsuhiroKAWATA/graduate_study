#pragma once
#include <iostream>
#include <string>
#include <fstream>

//�萔��`(�|�C���^�Ŏ����Ȃ��Ă��g�����ق����ǂ����)
const int Lega = 3;//�Œ��̒���(���������)
const int Stac = 1;//�ŒZ�̒P��(���������)
const int meloMakeNum = 7;//�����f�B�쐬�����v
const int meloMakeFrag = 2;//��x�ɍ쐬���郁���f�B
const int meloMakeRep = 2;//�����f�B�쐬�J��Ԃ���
const static int Kstuck = 30;//key.csv�ǂݍ��ݗp��2�����z��̗v�f������1
const static int Kline = 4;//��ɓ�������2
const static int Sstuck = 3;//scale_tmp_keynote.csv�ǂݍ��ݗp��2�����z��̗v�f������1
const static int Sline = 18;//��ɓ�������2
const static int MusicNum = 5;//�쐬������K�Ȃ̐�


class data_controller {
public:
	//�萔��`����
	char chord[3] = { '1','3','5' }, notes[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'H' };
	char scaleTKeynote[Sstuck][Sline];
	char keynoteOrder[2][7] = { {'F', 'C', 'G', 'D', 'A', 'E', 'H'},{'H', 'E', 'A', 'D', 'G', 'C', 'F'} };
	char key[Kstuck][Kline];
	//chord:�a���̉��̈ʒu�A�x���\�L, key;���̖��O�ƒ����̎�ނƐ��A�O������ǂނ�, keynoteOrder:�����̂���, 
	//notes:7��, scaleTKeynote:�X�P�[���̗Վ��L���̐��Əꏊ(�x���\�L)�A�O������ǂ�
	
	/*�ȉ��v�A�v���O�����������_�ō폜
	int chord[3];//chord.csv�̃f�[�^��:3
	int key[24][3];//key.csv�̃f�[�^��:72
	int keynoteOrder[7][2];//keynote_order.csv�̃f�[�^��:14
	int notes[7];//notes.csv�̃f�[�^��(7)
	int scaleTKeynote[5][3];//scale_tmp_keynote.csv�̃f�[�^��(15)
	//�����܂ŁB�̈�͍Œ�������m�ۂ��ĂȂ��̂Ńf�[�^����������̈�����₷�K�v������B
	*/

	//�֐�
	data_controller();
	~data_controller();
private:
	//�萔�n

	//�ϐ�
	std::ifstream fin;
	std::string passer;
	char* tmpp;
	char textHolder[80];
	
	//�֐�
	void readData(std::string fileName, char* databox, int chunkNum, int lineNum);//linenum:key[30][3]��3�̂ق�

	//�m�F�p��3�b�ō�����֐��A�{�؂ɂ͊֌W�Ȃ��B
	//�G�ɍ�����̂Ŋm�F�̓x�Ɋm�F�������z��̖��O���v���O��������w�肷��K�v������Ƃ��������ׂ�����܂�
	void confirmCorrect(int tate, int yoko);
};