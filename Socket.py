import socket

class SocketServidor:
    def __init__(self,mensaje) :
        #Servidor
        #Creamos el objeto para socket
        objSocket=socket.socket()
        #Pasamos los parametros de un host y el puerto donde se abrirá
        objSocket.bind(('localhost',8000))
        #Cuantos clientes va a tener
        objSocket.listen(5)
        print("Esperando conexión")
        #Bucle para esperar la conexion de clientes
        while True:
            #Cuando alguien se conecte tomamos la direccion y abrimos conexion
            conexion,direccion=objSocket.accept()
            print("Cliente C++: ",direccion)
            #Enviamos datos codificados al cliente en formato UTF-8 y con un controlador de errores
            conexion.send(mensaje.encode(encoding='UTF-8',errors='strict'))
            #Cerramos conexion
            conexion.close()

class SocketCliente:
    def __init__(self,mensaje) :
        #Cliente
        #Creamos el objeto para socket
        objSocket=socket.socket()
        #Inicamos conexion con el servidor mandando host y puerto
        objSocket.connect(('localhost',8000))
        #Enviamos datos codificados al servidor en formato UTF-8 y con un controlador de errores
        objSocket.send(mensaje.encode(encoding='UTF-8',errors='strict'))
        #Cerramos conexion
        objSocket.close()