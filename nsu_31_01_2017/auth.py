from __future__ import print_function

import os



audit_filename = 'audit'

password_filename = 'passwd'


def audit_message(message):
    os.system('date/T >> {audit} && time /T >> {audit} && echo {message} >> {audit}'.format(message = message, audit = audit_filename))
    return


def on_login_success(username):
    audit_message('login for user [{username}] was succeeded'.format(username = username))
    return


def on_login_failure(username):
    audit_message('login for user [{username}] was failed'.format(username = username))
    return

def on_user_added(username):
    audit_message('added user [{username}]'.format(username = username))
    return

def on_user_removed(username):
    audit_message('removed user [{username}]'.format(username = username))
    return


def login(user, password):
    with open(password_filename, 'r') as passwd_file:
        for line in passwd_file:
            entry = line.split(':')
            if (entry[0].strip() == user) and (entry[1].strip() == password):
                on_login_success(user)
                return True

    on_login_failure(user)
    return False


def add_user(username, password):
    os.system('echo {username}:{password} >> {passwd}'.format(username = username, password = password, passwd = password_filename))
    on_user_added(username)
    return

def delete_user(username):
    users = list()
    with open(password_filename, 'r') as passwd_file:
        for line in passwd_file:
            entry = line.split(':')
            if entry[0].strip() != username:
                users.append(line)

    with open(password_filename, 'w') as passwd_file:
        for line in users:
            passwd_file.write(line)

    on_user_removed(username)
    return


def show_audit():
    os.system('type {filename}'.format(filename = audit_filename))
    return    


