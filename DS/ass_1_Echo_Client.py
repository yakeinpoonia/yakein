import socket

c = socket.socket()
c.connect(('localhost', 5000))

while True:
    msg = input("You: ")
    c.send(msg.encode())
    if msg == 'exit':
        break
    print(c.recv(1024).decode())

c.close()
