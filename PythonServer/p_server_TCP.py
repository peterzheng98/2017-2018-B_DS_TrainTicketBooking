import socket
import threading
import time


def tcplink(sock, addr):
    print('Accept new connection from %s:%s...' % addr)
    sock.send(b'Welcome!')
    while True:
        data = sock.recv(1024)
        time.sleep(1)
        if data == 'exit' or not data:
            break
        sock.send(b'Hello,%s!' % data)
        print('Accpeted : %s' % data)
    sock.close()
    print('Connection from %s:%s closed.' % addr)


s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

if __name__ == '__main__':
    s.bind(('127.0.0.1' , 10774))
    s.listen(5)
    print('Waiting for connection...')

    while True:
        sock, addr = s.accept()
        t = threading.Thread(target=tcplink(sock, addr))

