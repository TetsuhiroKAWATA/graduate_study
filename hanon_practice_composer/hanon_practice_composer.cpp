// hanon_practice_composer.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "makePractice.h"

int main()
{
    //初期値に意味がない系変数
    int selectNum = -999;
    std::string confirm = "N";
    int evaluation = -999;

    //初期値に意味がある系変数
    const int PNum = 5;//練習項目数
    std::string items[] = { "基礎練習(1～20)", "スケール(39)", "アルペジオ(41～43)", "オクターブ(51,53,57)", "半音階(40)" };
    makePractice* mPrac;

    std::cout << "Hanon Practice Composer\n";

    do {
        std::cout << "練習項目を選択してください。\n";
        std::cout << "項目名(該当するハノン楽曲番号)\n";
        for (int i = 0; i < PNum; i++) {
            std::cout << i << ":" << items[i] << "\n";
        }
        std::cin >> selectNum;
        if (selectNum >= 0 && selectNum < 5) {
            std::cout << "選択された練習項目:" << items[selectNum] << "\n";
            std::cout << "こちらの練習項目で練習曲の作成を行います。\nよろしいですか？\n";
            std::cout << "はい：Y　いいえ：N\n";
            std::cin >> confirm;
            if (confirm == "Y" || confirm == "y")
                break;
        }
        else {
            std::cout << "その番号には練習項目が割り当てられていません。\n";
        }
    } while (1);
    std::cout << "Debug::do_while_finished\n";
    std::cout << "Debug::items = " << items[selectNum] << "\n";

    //世代交代とかやる
    //初期集団作成はコントラクタから関数呼び出してやる
    mPrac = new makePractice();
    do {
        confirm = 'N';
        std::cout << "1:楽曲A\n";
        std::cout << "2:楽曲B\n";
        std::cout << "最終結果としたい楽曲はありましたか？ y/n\n";
        std::cin >> confirm;
        if (confirm == "Y" || confirm == "y") {
            do {
                std::cout << "どちらの楽曲を出力しますか？\n";
                evaluation = -1;
                std::cin >> evaluation;
                if (evaluation == 1 || evaluation == 2) {
                    std::cout << evaluation << "の楽曲を出力します。\n";
                    break;
                }
                else {
                    std::cout << "正しい数字を入力してください\n";
                }

            } while (1);
            break;
        }
        else {
            std::cout << "それぞれの楽曲に点数をつけてください。\n";
            std::cout << "楽曲No.1の採点\n";
            std::cin >> evaluation;
            std::cout << "楽曲No.2の採点\n";
            std::cin >> evaluation;
            std::cout << "楽曲をもう一度作成します\n";
        }
    } while (1);

    mPrac->printResult();
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
