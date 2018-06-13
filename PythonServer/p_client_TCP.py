import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(('59.78.22.153', 10774))

print(s.recv(1024).decode())

for data in ['register name name name name','query_profile 2018','add_train 1 1 1 1 \n 12121 \n 313']:
    s.send(data.encode())
    print(s.recv(1024).decode())

s.send(b'exit')
s.close()

