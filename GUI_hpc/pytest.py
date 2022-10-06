import PySimpleGUI as sg

sg.theme('Dark Grey 13')

layout = [[sg.Text('Filename')],
          [sg.Input(), sg.FileBrowse()],#FileBrowseってのを使うだけでPC内をブラウズできる
          [sg.OK(), sg.Cancel()]]

window = sg.Window('Get filename example', layout)

event,values = window.read()
window.close()