from __future__ import print_function

import sys

import auth
import message



class CommandContext:
    def __init__(self, username):
        self.username = username
        self.is_admin = (username == 'admin')
        self.is_guest = (username == 'guest')



def list_messages(context):
    print('list messages: ')
    
    message.list_messages()
    return

def add_message(context):
    print('add message: ')

    username = context.username
    if context.is_guest:
        print('type username and press enter: ', end = ' ')
        username = sys.stdin.readline().strip()
        
    
    print('type message and press enter: ', end = ' ')
    msg = sys.stdin.readline().strip()

    full_msg = 'User [{user}] wrote: [{msg}]'.format(user = username, msg = msg)
    
    message.add_message(full_msg)
    return

def delete_messages(context):
    print('delete all messages: ')
    
    message.delete_messages()
    return


def add_user(context):
    print('add user: ')
    print('print user name and press enter: ', end = ' ')
    username = sys.stdin.readline().strip()

    print('print user password and press enter, or leave password blank and press enter: ', end = ' ')
    password = sys.stdin.readline().strip()
    
    auth.add_user(username, password)
    return

def delete_user(context):
    print('delete user: ')
    print('print user name and press enter: ', end = ' ')
    username = sys.stdin.readline().strip()

    auth.delete_user(username)
    return

def show_audit(context):
    print('show audit: ')
    
    auth.show_audit()
    return









commands = {
    '1': list_messages,
    '2': add_message,
    '3': delete_messages,
    '4': add_user,
    '5': delete_user,
    '6': show_audit
    }
