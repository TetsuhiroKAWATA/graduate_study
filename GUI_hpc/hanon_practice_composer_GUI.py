import PySimpleGUI as sg


#変数
ans = ''#ユーザの答えを入れるやつ
Opt = ['基礎練習(1~20)', 'スケール(39)', 'アルペジオ(41~43)', 'オクターブ(51,53,57)', '半音階(40)']

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
           [sg.Button('1', size = (2,1)), sg.Button('2', size = (2,1)),
           sg.Button('3', size = (2,1)), sg.Button('4', size = (2,1)),
           sg.Button('5', size = (2,1)), sg.Button('6', size = (2,1)),
           sg.Button('7', size = (2,1)), sg.Button('8', size = (2,1)),
           sg.Button('9', size = (2,1)), sg.Button('10', size = (2,1))],
           [sg.Button('11', size = (2,1)), sg.Button('12', size = (2,1)),
           sg.Button('13', size = (2,1)), sg.Button('14', size = (2,1)),
           sg.Button('15', size = (2,1)), sg.Button('16', size = (2,1)),
           sg.Button('17', size = (2,1)), sg.Button('18', size = (2,1)),
           sg.Button('19', size = (2,1)), sg.Button('20', size = (2,1))],
           [sg.Button('決定'), sg.Button('やめる')] ]



#可否選択、採点画面

#楽譜出力画面


#処理
window = sg.Window('Hanon Practice Composer',top, resizable = True)

while True:
    event,values = window.read()
    if event == sg.WIN_CLOSED or event == 'やめる':
        window.close()
        break
    elif event == '始める':
        window.close()
        window = sg.Window('Hanon Practice Composer', sele1, resizable = True)
        break

while True:
    event, values = window.read()
    #print(event)
    if event == sg.WIN_CLOSED or event == 'やめる':
        window.close()
        break
    elif event == '決定':#次のページへ
        if ans == 0 or ans == 1 or ans == 2 or ans == 3 or ans == 4:
            window.close()
            if ans == 0:
                window = sg.Window('Hanon Practice Composer', found1, resizable = True)
            break
        else:
            sg.popup('練習項目を選択してください')
    else:#選択処理
        ans = event
        ans = int(ans)
        #print(type(ans))#型確認
        window['-OUTPUT-'].update(Opt[ans])

while True:
    event, values = window.read()
    if event == sg.WIN_CLOSED or event == 'やめる':
        window.close()
        break
    elif event == '決定':
        pass
    else:
        pass


window.close()
