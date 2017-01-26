from __future__ import print_function

import sys

import auth
import commands



def process_command(context):
    print('Select command (press number):')
    print('')
    
    print('  1. Add message')
    
    if not context.is_guest:
        print('  2. List messages')
        
    if context.is_admin:
        print('  3. Delete all messages')
        print('  4. Add user')
        print('  5. Delete user')
        print('  6. show audit')

    print('')
    print('Select your command: ', end = ' ')
    commandId = sys.stdin.readline().strip()
    print('You`ve chosen command {commandId}'.format(commandId = commandId))
    print('')

    commands.commands[commandId](context)
    
    


def main(args):

    print('Super guest book')
    print('')
    user = args[1]
    password = ''

    if len(args) == 3:
        password = args[2]

    if not auth.login(user, password):
        print('cannot login with given credentials')
        return 1

    context = commands.CommandContext(user)
    
    print('You are logged in as [{who}]'.format(who = user))
    process_command(context)
    return 0



if __name__ == '__main__':
    sys.exit(main(sys.argv))
