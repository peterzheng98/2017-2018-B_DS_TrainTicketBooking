#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 绑定端口:
s.bind(('127.0.0.1', 10774))

print('Bind UDP on 10774...')

while True:
    # 接收数据:
    data, addr = s.recvfrom(1024)
    print('Received from %s:%s.' % addr)
    reply = 'Hello, %s!' % data.decode('utf-8')
    if data.decode('utf-8') == 'hello':
        reply = 'Hello!'
    else:
        reply = 'Test!'
    print('Reply : %s' % reply)
    s.sendto(reply.encode('utf-8'), addr)
