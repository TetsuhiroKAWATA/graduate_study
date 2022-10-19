// hanon_practice_composer.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "makePractice.h"

void printChord(makePractice* mPrac) {


    char tmp = 'X', tmp2 = 'X';
    for (int i = 0; i < Kstuck; i++) {
        tmp = mPrac->Cont->key[i][0];//使ってます
        std::cout << i << ":" << tmp;
        tmp2 = mPrac->Cont->key[i][1];
        if (tmp2 == '#')
            std::cout << "is";
        else if (tmp2 == 'b') {
            if (tmp == 'e' || tmp == 'E' || tmp == 'a' || tmp == 'A')
                std::cout << "s";
            else
                std::cout << "es";
        }

        if ('a' <= tmp && 'z' >= tmp) {
            std::cout << " moll\n";
        }
        else {
            std::cout << " dur\n";
        }
    }
}

int main()
{
    //初期値に意味がない系変数
    //int selectNum = -999;//割り当てられた練習項目
    std::string confirm = "N";//意思決定確認用変数
    int evaluation = -999;//ユーザが付けた点数入れるやつ、のはず
    int chordNum = -999;//調を選択するやつ
    int generalTmp = -999;//汎用的に仕えるデータの一時保管先(int型)
    std::string generalSTmp;
    char tmp = 'X';

    //初期値に意味がある系変数
    const int PNum = 5;//練習項目数
    std::string items[] = { "基礎練習(1～20)", "スケール(39)", "アルペジオ(41～43)", "オクターブ(51,53,57)", "半音階(40)" };
    makePractice* mPrac;

    //乱数の種
    srand((unsigned int)time(NULL));

    std::cout << "Hanon Practice Composer\n";

    //世代交代とかやる
    mPrac = new makePractice();
    mPrac->Cont->loadSNum();

    //調を決定する
    if (mPrac->Cont->selectedNum == 0 || mPrac->Cont->selectedNum == 3 || mPrac->Cont->selectedNum == 4) {
        //基礎とオクターブと半音階
        mPrac->Cont->chordNum = 0;
        mPrac->Cont->typeofChord = 2;
        //Cdurにならないとおかしいのでそうならない場合は考慮してないです
        std::cout << "楽曲の調は、" << mPrac->Cont->key[mPrac->Cont->chordNum][0] << "dur です。\n";
        
        if(mPrac->Cont->selectedNum == 0)
            mPrac->Cont->loadMusicNum();//何番の曲についてか読み込み
        mPrac->Cont->makeScale();
    }
    else if (mPrac->Cont->selectedNum == 1) {
        //楽曲No.1->スケール
        //調とタイプ(和声旋律)を設定
        mPrac->Cont->loadChordNum();

        //調作る
        mPrac->Cont->makeScale();
    }
    else if (mPrac->Cont->selectedNum == 2) {
        //楽曲No.2->アルペジオ
        //調とタイプ(和声旋律)を設定
        mPrac->Cont->loadChordNum();

        mPrac->Cont->makeScale();
    }
    else {
        std::cout << "番号選択が間違っています。\n";
        exit(1);
    }

    //データ整備をする。
    mPrac->dataPrepare();
    //よみこみ
    for (int i = 0; i < MusicNum; i++) {
        mPrac->Ind[i]->loadChrom(i);
    }


    //世代交代とかやる

    confirm = 'N';
    for (int i = 0; i < MusicNum; i++) {
        std::cout << i + 1 << ":music" << i + 1 << "\n";
        //std::cout << "Debug::zantei\n";
    }
    std::cout << "最終結果としたい楽曲はありましたか？ y/n\n";
    std::cin >> confirm;
    if (confirm == "Y" || confirm == "y") {
        do {
            std::cout << "どの楽曲を出力しますか？\n";
            evaluation = -1;
            std::cin >> evaluation;
            if (evaluation >= 1 && evaluation <= MusicNum) {
                std::cout << evaluation << "の楽曲を出力します。\n";

                mPrac->printResult(evaluation - 1);
                break;
            }
            else {
                std::cout << "正しい数字を入力してください\n";
            }

        } while (1);
    }
    else {
        std::cout << "それぞれの楽曲に点数をつけてください。\n";
        for (int i = 0; i < MusicNum; i++) {
            std::cout << "楽曲No." << i + 1 << "の点数\n";
            std::cin >> mPrac->Ind[i]->point;
        }
        //点数順に並び替え
        mPrac->sort(0, MusicNum - 1);//エリートやらねえからいらない関数なんだけど作っちゃったしやる可能性もあるから残しとくわ
        /*for (int i = 0; i < MusicNum; i++) {
            std::cout << mPrac->Ind[i]->point;
        }*/
        std::cout << "楽曲をもう一度作成します\n";
        //世代交代コマンド
        mPrac->alternate();
        //出力
        for (int i = 0; i < MusicNum; i++) {
            mPrac->printMusic(i);
        }
    }

    delete mPrac;

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
