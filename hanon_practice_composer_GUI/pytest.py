import PySimpleGUI as sg
import subprocess
from subprocess import PIPE

page = [ [sg.Text('hanon practice composer Test')],
       [sg.Button('start'), sg.Button('quit')] ]



#inpline = ["0", "y", "10", "y", "n", "1", "2", "3", "4", "5", "y", "4", "y"]

#exe起動
#inpline : str = "0 y 10 y n 1 2 3 4 5 y 4 y"

#window = sg.Window('hanon_practice_composer', page)

#while True:
#    event,values = window.read()
#    if(event == sg.WIN_CLOSED or event == 'quit'):
#        break
#    elif event == 'start':
#        with subprocess.Popen("..\\hpc\\hanon_practice_composer.exe", shell=True, stdin=PIPE, stdout=PIPE,stderr=PIPE,universal_newlines=True)as pipe:
#            out,err = pipe.communicate(inpline)
#            for line in out.splitlines():
#                print(line)

#        break
        #stdout = subprocess.PIPE, 
        #Pro = subprocess.Popen(["..\\hpc\\hanon_practice_composer.exe"], encoding = 'utf8', universal_newlines = True)までなら動く
#        Pro = subprocess.Popen(["..\\hpc\\hanon_practice_composer.exe"], stdin = subprocess.PIPE, universal_newlines = True, encoding = 'utf8')
 #       res = Pro.communicate(inpline.encode())[0].decode()
  #      print(res)

window.close()

#sg.theme('Dark Blue 3')  # please make your windows colorful

#layout = [[sg.Text('Your typed chars appear here:'), sg.Text(size=(12,1), key='-OUTPUT-')],
#          [sg.Input(key='-IN-')],
#          [sg.Button('Show'), sg.Button('Exit')]]

#window = sg.Window('Window Title', layout)

#while True:  # Event Loop
#    event, values = window.read()
#    print(event, values)
#    if event == sg.WIN_CLOSED or event == 'Exit':
#        break
#    if event == 'Show':
        # change the "output" element to be the value of "input" element
#        window['-OUTPUT-'].update(values['-IN-'])

#window.close()


#case2
#text = sg.popup_get_text('inputer', 'Window title', 'Please input something')
#sg.popup_animated('', 'wait', 'white', 'black')
#sg.popup('Results','The value returned from PopupGetText', text)


#case1
#sg.theme('Dark Grey 13')

#layout = [[sg.Text('Filename')],
#          [sg.Input(), sg.FileBrowse()],#FileBrowseってのを使うだけでPC内をブラウズできる
#          [sg.OK(), sg.Cancel()]]

#window = sg.Window('Get filename example', layout)

#event,values = window.read()
#window.close()