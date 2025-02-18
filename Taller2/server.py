import socket
import threading


# Función para manejar la conexión con el cliente
def handle_client(client_socket, client_address):
    client_socket.send("Conexión establecida con el servidor".encode())
    print(
        f"Conexión establecida con {client_address} en el hilo {threading.current_thread().name}"
    )

    while True:
        message = client_socket.recv(1024)
        if not message:
            break
        print(f"Cliente dice: {message.decode()}")
        response = f"Recibido: {message.decode()}"
        client_socket.send(response.encode())

    client_socket.close()
    print(f"Conexión cerrada con {client_address}")


# Configuración del servidor
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 3022))  # Escuchar en localhost en el puerto 3022
server.listen(5)  # Permitir hasta 5 conexiones en cola
print("Servidor escuchando en el puerto 3022...")

while True:
    client_socket, client_address = server.accept()
    client_handler = threading.Thread(
        target=handle_client, args=(client_socket, client_address)
    )
    client_handler.start()
