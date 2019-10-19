import socket
import sys
import struct

port = 4242
#host = 'z1r8p1.le-101.fr'
host = '127.0.0.1'
  
try: 
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    print "Socket successfully created"
except socket.error as err: 
    print "socket creation failed with error %s" %(err) 
try: 
    host_ip = socket.gethostbyname('127.0.0.1') 
except socket.gaierror: 
    print "there was an error resolving the host"
    sys.exit() 
sock.connect((host_ip, port)) 
#print "the socket has successfully connected to google on port == %s" %(host_ip)

#def connect(host, port)


def send_msg(msg):
    # Prefix each message with a 4-byte length (network byte order)
    msg = struct.pack('>I', len(msg)) + msg
    sock.sendall(msg)

def recv_msg():
    # Read message length and unpack it into an integer
    raw_msglen = recvall(4)
    if not raw_msglen:
        return None
    msglen = struct.unpack('>I', raw_msglen)[0]
    # Read the message data
    print "yo"
    return recvall(msglen)

def recvall(n):
    # Helper function to recv n bytes or return None if EOF is hit
    print "bonjour"
    data = bytearray()
    #data = ""
    while len(data) < n:
        packet = sock.recv(n - len(data))
        if not packet:
            return None
        data.extend(packet)
        #data = data + packet.decode('utf-8')
    #print "omg: " + data
    return data

def recvall2():
    BUFF_SIZE = 4096 # 4 KiB
    data = b''
    while True:
        part = sock.recv(BUFF_SIZE)
        data += part
        print "len: " + str(len(part))
        if len(part) < BUFF_SIZE:
            # either 0 or end of data
            print "break"
            break
    return data

#while (True)
#print "received: " + s.recv(1024)
#s.send('ls') 
#print "received: " + s.recv(1024)
#s.send('ls') 
#print "received: " + s.recv(1024)
#print "received: " + s.recv(1024)
#print "received: " + s.recv(1024)

#send_msg("ls")
#msg = recv_msg()
#print "hoho: " + "".join(map(chr, msg))

print "yes!! " + recvall2()
sock.send("ls -l")
print "yes!! " + recvall2()
sock.send("ls -gmadec")
print "yes!! " + recvall2()


sock.close()