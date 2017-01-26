from __future__ import print_function

import os


message_filename = 'msg'




def list_messages():
    os.system('type {filename}'.format(filename = message_filename))
    return

def add_message(message):
    os.system('echo {msg} >> {filename}'.format(msg = message, filename = message_filename))
    return

def delete_messages():
    os.system('del /S /Q {filename}'.format(filename = message_filename))
    return
