
import pxssh
import getpass
try:                                                           
    s = pxssh.pxssh()
    hostname = raw_input('hostname: ')
    username = raw_input('username: ')
    password = getpass.getpass('password: ')
    s.login (hostname, username, password)


    s.sendline ('echo "ddns-update-style interim;" > /etc/dhcp/dhcpd.conf')   # run a command
    s.prompt()             # match the prompt
    print s.before          # print everything before the prompt.

    s.sendline ('echo "authoritative;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before

    s.sendline ('echo "default-lease-time 600;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "max-lease-time 7200;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "subnet 192.168.2.0 netmask 255.255.255.0 { " >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "option subnet-mask 255.255.255.0;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "option broadcast-address 192.168.2.255;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "option routers 192.168.2.1;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "option domain-name-servers 8.8.8.8, 192.168.2.1;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "range 192.168.2.51 192.168.2.100;" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
    s.sendline ('echo "}" >> /etc/dhcp/dhcpd.conf')
    s.prompt()
    print s.before
   
   
    # Assign Interfaces to /etc/default/isc-dhcp-server file
    s.sendline ('echo "INTERFACES=eth0" > /etc/default/isc-dhcp-server')
    s.prompt()
    print s.before
   
    s.sendline ('route add -net 192.168.2.0 netmask 255.255.255.0 gw 192.168.2.1')
    s.prompt()
    print s.before
   
    s.sendline ('dhcpd -cf /etc/dhcp/dhcpd.conf -pf /var/run/dhcpd.pid eth0')
    s.prompt()
    print s.before
   
    s.sendline ('/etc/init.d/isc-dhcp-server start')
    s.prompt()
    print s.before
   
    s.logout()

except pxssh.ExceptionPxssh, e:
    print "pxssh failed on login."
    print str(e)
