import socket
import pickle

def add(a, b): return a + b
def sub(a, b): return a - b
def mul(a, b): return a * b
def div(a, b): return a / b if b != 0 else "Division by zero error"

functions = {
    'add': add,
    'sub': sub,
    'mul': mul,
    'div': div
}

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('127.0.0.1', 6000))
server.listen(5)
print("RPC Server is running...")

while True:
    client, addr = server.accept()
    print(f"Connected to {addr}")
    data = client.recv(1024)
    func_name, args = pickle.loads(data)
    
    if func_name in functions:
        result = functions[func_name](*args)
    else:
        result = "Invalid function name"

    client.send(pickle.dumps(result))
    client.close()
