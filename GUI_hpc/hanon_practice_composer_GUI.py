import PySimpleGUI as sg


#変数
ans = ''#ユーザの答えを入れるやつ
Opt = ['基礎練習(1~20)', 'スケール(39)', 'アルペジオ(41~43)', 'オクターブ(51,53,57)', '半音階(40)']

sg.theme('BlueMono')

top = [ [sg.Text('Hanon Practice Composer')],
           [sg.Button('始める'), sg.Button('やめる')]]

sele1 = [ [sg.Text('練習したい楽曲を選択してください')],
          [sg.Text('書式:項目名(ハノン曲番号)')],
          [sg.Text('現在選択中の項目:'), sg.Text(size = (20,1), key = '-OUTPUT-')],#sizeの第一引数で文字数、第二引数で行数を作ってるっぽい
          [sg.Button(Opt[0], key = "0"), sg.Button(Opt[1], key = "1"),
          sg.Button(Opt[2], key = "2"),sg.Button(Opt[3], key = "3"),
          sg.Button(Opt[4], key = "4")],
          [sg.Button('決定'), sg.Button('やめる')]]


#処理
window = sg.Window('Hanon Practice Composer',top)

while True:
    event,values = window.read()
    if event == sg.WIN_CLOSED or event == 'やめる':
        break
    elif event == '始める':
        window.close()
        window = sg.Window('Hanon Practice Composer', sele1)
        break

while True:
    event, values = window.read()
    #print(event)
    if event == sg.WIN_CLOSED or event == 'やめる':
        break
    elif event == '決定':#次のページへ
        pass
    else:#選択処理
        ans = event
        ans = int(ans)
        #print(type(ans))#型確認
        window['-OUTPUT-'].update(Opt[ans])




window.close()
