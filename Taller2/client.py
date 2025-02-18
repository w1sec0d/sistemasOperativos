import socket

# Configuración del cliente
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 3022))

message = client.recv(1024)
print(f"Servidor dice: {message.decode()}")

while True:
    user_input = input(
        "Escribe un mensaje para el servidor (o 'salir' para desconectar): "
    )
    if user_input.lower() == "salir":
        break
    client.send(user_input.encode())
    response = client.recv(1024)
    print(f"Servidor dice: {response.decode()}")

client.close()
print("Conexión cerrada.")
