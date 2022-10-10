import PySimpleGUI as sg

sg.theme('Dark Blue 3')  # please make your windows colorful

layout = [[sg.Text('Your typed chars appear here:'), sg.Text(size=(12,1), key='-OUTPUT-')],
          [sg.Input(key='-IN-')],
          [sg.Button('Show'), sg.Button('Exit')]]

window = sg.Window('Window Title', layout)

while True:  # Event Loop
    event, values = window.read()
    print(event, values)
    if event == sg.WIN_CLOSED or event == 'Exit':
        break
    if event == 'Show':
        # change the "output" element to be the value of "input" element
        window['-OUTPUT-'].update(values['-IN-'])

window.close()


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