import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

p = input()
st = str.encode(p)
# for data in [b'Michael', b'Tracy', b'Sarah']:
s.sendto(st, ('127.0.0.1', 10774))
print(s.recv(1024).decode('utf-8'))

s.close()