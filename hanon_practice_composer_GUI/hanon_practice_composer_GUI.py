import PySimpleGUI as sg
#memo:入力、出力は一回しか呼び出せない。出力を二回呼び出すとかはできないし、入力の時にしか出力を呼び出せない

#変数
ans = ''#ユーザの答えを入れるやつ
line = ''#標準入力に送り付ける文字列
scaleknd = ['和声', '旋律', '自然']
OptIN = ''#セレクト用
Opt = ['基礎練習(1~20)', 'スケール(39)', 'アルペジオ(41~43)', 'オクターブ(51,53,57)', '半音階(40)']
chord = ['C dur', 'G dur', 'D dur', 'A dur', 'E dur', 'H dur', 'F dur', 'B dur', 'Es dur', 'As dur', 'Des dur', 'Ges dur',
        'a moll', 'e moll', 'h moll', 'fis moll', 'cis moll', 'gis moll', 'd moll', 'g moll', 'c moll', 'f moll', 'hes moll', 'es moll']

sg.theme('BlueMono')

top = [ [sg.Text('Hanon Practice Composer', size = (20,3), font = ('Arial', 24))],
        [sg.Push(), sg.Button('始める', size = (8,1)), sg.Button('やめる', size = (8,1)), sg.Push()] ]

sele1 = [ [sg.Text('練習したい楽曲を選択してください')],
          [sg.Text('書式:項目名(ハノン曲番号)')],
          [sg.Text('現在選択中の項目:'), sg.Text(size = (20,1), key = '-OUTPUT-')],#sizeの第一引数で文字数、第二引数で行数を作ってるっぽい
          [sg.Button(Opt[0], key = "0", size = (16,1)), sg.Button(Opt[1], key = "1", size = (16,1)),
          sg.Button(Opt[2], key = "2", size = (16,1)),sg.Button(Opt[3], key = "3", size = (16,1)),
          sg.Button(Opt[4], key = "4", size = (16,1))],
          [sg.Button('決定', size = (8,1)), sg.Button('やめる', size = (8,1))] ]

#基礎練習画面
#1:1~20選択
found1 = [ [sg.Text('練習項目:'), sg.Text(Opt[0])],
           [sg.Text('楽曲番号を選択してください')],
           [sg.Text('現在選択中の項目:'), sg.Text(size = (12,1), key = '-OUTPUT-')],
           [sg.Button('1', key = 1, size = (2,1)), sg.Button('2', key = 2, size = (2,1)),
           sg.Button('3', key = 3, size = (2,1)), sg.Button('4', key = 4, size = (2,1)),
           sg.Button('5', key = 5, size = (2,1)), sg.Button('6', key = 6, size = (2,1)),
           sg.Button('7', key = 7, size = (2,1)), sg.Button('8', key = 8, size = (2,1)),
           sg.Button('9', key = 9, size = (2,1)), sg.Button('10', key = 10, size = (2,1))],
           [sg.Button('11', key = 11, size = (2,1)), sg.Button('12', key = 12, size = (2,1)),
           sg.Button('13', key = 13, size = (2,1)), sg.Button('14', key = 14, size = (2,1)),
           sg.Button('15', key = 15, size = (2,1)), sg.Button('16', key = 16, size = (2,1)),
           sg.Button('17', key = 17, size = (2,1)), sg.Button('18', key = 18, size = (2,1)),
           sg.Button('19', key = 19, size = (2,1)), sg.Button('20', key = 20, size = (2,1))],
           [sg.Button('決定'), sg.Button('やめる')] ]

#スケール練習画面
#1:調選択,3*8の24を表示
scale1 = [ [sg.Text('練習項目:'), sg.Text(Opt[1])],
           [sg.Text('楽曲の調を選択してください')],
           [sg.Text('現在選択中の項目:'), sg.Text(size = (12,1), key = '-OUTPUT-'), sg.Text(size = (6,1), key = '-OUTPUT2-')],
           [sg.Button(chord[0], size = (8,1), key = 0), sg.Button(chord[1], size = (8,1), key = 1), sg.Button(chord[2], size = (8,1), key = 2), sg.Button(chord[3], size = (8,1), key = 3),
           sg.Button(chord[4], size = (8,1), key = 4), sg.Button(chord[5], size = (8,1), key = 5), sg.Button(chord[6], size = (8,1), key = 6), sg.Button(chord[7], size = (8,1), key = 7)],
           [sg.Button(chord[8], size = (8,1), key = 8), sg.Button(chord[9], size = (8,1), key = 9), sg.Button(chord[10], key = 10, size = (8,1)), sg.Button(chord[11], size = (8,1), key = 11),
           sg.Button(chord[12], size = (8,1), key = 12), sg.Button(chord[13], size = (8,1), key = 13), sg.Button(chord[14], size = (8,1), key = 14), sg.Button(chord[15], size = (8,1), key = 15)],
           [sg.Button(chord[16], size = (8,1), key = 16), sg.Button(chord[17], size = (8,1), key = 17), sg.Button(chord[18], size = (8,1), key = 18), sg.Button(chord[19], size = (8,1), key = 19),
           sg.Button(chord[20], size = (8,1), key = 20), sg.Button(chord[21], size = (8,1), key = 21), sg.Button(chord[22], size = (8,1), key = 22), sg.Button(chord[23], size = (8,1), key = 23)],
           [sg.Button('決定'), sg.Button('やめる')]]

#アルペジオ
arpe1 = [ [sg.Text('練習項目:'), sg.Text(Opt[2])], 
           [sg.Text('楽曲の調を選択してください')],
           [sg.Text('現在選択中の項目:'), sg.Text(size = (12,1), key = '-OUTPUT-'), sg.Text(size = (6,1), key = '-OUTPUT2-')],
           [sg.Button(chord[0], size = (8,1), key = 0), sg.Button(chord[1], size = (8,1), key = 1), sg.Button(chord[2], size = (8,1), key = 2), sg.Button(chord[3], size = (8,1), key = 3),
           sg.Button(chord[4], size = (8,1), key = 4), sg.Button(chord[5], size = (8,1), key = 5), sg.Button(chord[6], size = (8,1), key = 6), sg.Button(chord[7], size = (8,1), key = 7)],
           [sg.Button(chord[8], size = (8,1), key = 8), sg.Button(chord[9], size = (8,1), key = 9), sg.Button(chord[10], key = 10, size = (8,1)), sg.Button(chord[11], size = (8,1), key = 11),
           sg.Button(chord[12], size = (8,1), key = 12), sg.Button(chord[13], size = (8,1), key = 13), sg.Button(chord[14], size = (8,1), key = 14), sg.Button(chord[15], size = (8,1), key = 15)],
           [sg.Button(chord[16], size = (8,1), key = 16), sg.Button(chord[17], size = (8,1), key = 17), sg.Button(chord[18], size = (8,1), key = 18), sg.Button(chord[19], size = (8,1), key = 19),
           sg.Button(chord[20], size = (8,1), key = 20), sg.Button(chord[21], size = (8,1), key = 21), sg.Button(chord[22], size = (8,1), key = 22), sg.Button(chord[23], size = (8,1), key = 23)],
           [sg.Button('決定'), sg.Button('やめる')]]

#オクターブ
octa1 = [[]]

#半音階
chro1 = [[]]


#可否選択、採点画面
selection = [ [sg.InputText('' , key = '-OUTPUT-'), sg.Button('表示')],
              [sg.Button('新規楽曲生成'), sg.Button('やめる')]]

#楽譜出力画面


#処理
window = sg.Window('Hanon Practice Composer',top, resizable = True)

#画面1
while True:
    event,values = window.read()
    if event == sg.WIN_CLOSED or event == 'やめる':
        window.close()
        break
    elif event == '始める':
        window.close()
        window = sg.Window('Hanon Practice Composer', sele1, resizable = True)
        break

#画面2練習項目選択画面
while True:
    event, values = window.read()
    #print(event)
    if event == sg.WIN_CLOSED or event == 'やめる':
        window.close()
        break
    elif event == '決定':#次のページへ
        if ans == 0 or ans == 1 or ans == 2 or ans == 3 or ans == 4:
            window.close()
            line += str(ans) + ' y '
            #print(line + 'fin')
            if ans == 0:
                #曲番号選択
                window = sg.Window('Hanon Practice Composer', found1, resizable = True)
                ans = -1
                while True:
                    event, values = window.read()
                    if event == sg.WIN_CLOSED or event == 'やめる':
                        window.close()
                        break
                    elif event == '決定':
                        if ans == -1:
                            sg.popup('曲番号を選択してください')
                        else:
                            window.close()
                            line += str(ans) + ' y '
                            #print(line + 'fin')
                            window = sg.Window('Hanon Practice Composer', selection, resizable = True)
                            break
                    else:#選択処理
                        ans = event
                        ans = int(ans)
                        window['-OUTPUT-'].update(ans)
            elif ans == 1:
                window = sg.Window('Hanon Practice Composer', scale1, resizable = True)
                ans = -1
                #調選択
                while True:
                    event, values = window.read()
                    if event == sg.WIN_CLOSED or event == 'やめる':
                        window.close()
                        break
                    elif event == '決定':
                        if ans == -1:
                            sg.popup('調を選択してください')
                        else:
                            window.close()
                            if OptIN == 2:
                                line += str(ans) + ' y '
                            else:
                                line += str(ans) + ' ' + str(OptIN) + ' y '
                            #print(line + 'fin')
                            window = sg.Window('Hanon Practice Composer', selection, resizable = True)
                            break
                    else:#選択処理
                        ans = event
                        ans = int(ans)
                        #和声旋律選択
                        if 11 < ans and ans < 24:
                            tmp = sg.popup('音階の種類を選んでください', background_color = 'lightblue', button_type = 1, custom_text = (' 和声 ', ' 旋律 '), no_titlebar = True, grab_anywhere = True)
                            if tmp == ' 和声 ':
                                OptIN = 0
                            else:
                                OptIN = 1
                        else:
                            OptIN = 2
                        OptIN = int(OptIN)
                        window['-OUTPUT-'].update(chord[ans])
                        window['-OUTPUT2-'].update(scaleknd[OptIN])
            elif ans == 2:
                window = sg.Window('Hanon Practice Composer', arpe1, resizable = True)
                ans = -1
                #調選択
                while True:
                    event, values = window.read()
                    if event == sg.WIN_CLOSED or event == 'やめる':
                        window.close()
                        break
                    elif event == '決定':
                        if ans == -1:
                            sg.popup('調を選択してください')
                        else:
                            window.close()
                            line += str(ans) + ' y '
                            #print(line + 'fin')
                            window = sg.Window('Hanon Practice Composer', selection, resizable = True)
                            break
                    else:#選択処理
                        ans = event
                        ans = int(ans)
                        window['-OUTPUT-'].update(chord[ans])
            elif ans == 3:
                pass
            elif ans == 4:
                pass
            break
        else:
            sg.popup('練習項目を選択してください')
    else:#選択処理
        ans = event
        ans = int(ans)
        #print(type(ans))#型確認
        window['-OUTPUT-'].update(Opt[ans])

#可否選択、採点画面
while True:
    event,values = window.read()
    if event == '表示':
        window['-OUTPUT-'].update(line)
    if event == sg.WIN_CLOSED or event == 'やめる':
        window.close()
        break
    else:
        pass


window.close()
