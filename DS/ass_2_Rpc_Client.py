import socket
import pickle

def rpc_call(func_name, args):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(('127.0.0.1', 6000))
    client.send(pickle.dumps((func_name, args)))
    result = pickle.loads(client.recv(1024))
    client.close()
    return result

print("Available functions: add, sub, mul, div")

while True:
    f = input("Enter function name (or 'exit' to quit): ")
    if f.lower() == "exit":
        break
    a = int(input("Enter first number: "))
    b = int(input("Enter second number: "))
    print("Result:", rpc_call(f, (a, b)))
