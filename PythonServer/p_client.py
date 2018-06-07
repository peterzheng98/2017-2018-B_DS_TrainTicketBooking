import socket
st = ''
st = input()
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# s.connect(('101.132.131.164', 10774))
s.connect(('127.0.0.1', 10774))
s.send(b''.join(st))

buffer = []
while True:
    d = s.recv(1024)
    if d:
        buffer.append(d)
    else:
        break

data = b''.join(buffer)

s.close()
print(data)
