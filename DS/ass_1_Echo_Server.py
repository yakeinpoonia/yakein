import socket
import threading

def handle_client(conn, addr):
    print("Connected:", addr)
    while True:
        msg = conn.recv(1024).decode()
        if not msg or msg == 'exit':
            break
        conn.send(("Echo: " + msg).encode())
    conn.close()
    print("Disconnected:", addr)

s = socket.socket()
s.bind(('localhost', 5000))
s.listen()
print("Server started...")

while True:
    c, addr = s.accept()
    threading.Thread(target=handle_client, args=(c, addr)).start()
