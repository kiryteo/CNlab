
import pxssh
import getpass
try:                                                            
    s = pxssh.pxssh()
    hostname = raw_input('hostname: ')
    username = raw_input('username: ')
    password = getpass.getpass('password: ')
    s.login(hostname, username, password)
    s.sendline ('sudo yum install nasm')   # run a command
    s.prompt()             # match the prompt
    print s.before          # print everything before the prompt.
    k = raw_input("y")
    s.sendline ('k')
    s.prompt()
   # print s.before
   # s.sendline ('df')
  #  s.prompt()
   # print s.before
    s.logout()
except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
