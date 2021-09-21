import socket

class Socket:
    def __init__(self) :
        #Servidor
        #Creamos el objeto para socket
        objSocket=socket.socket()
        #Pasamos los parametros de un host y el puerto donde se abrirá
        objSocket.bind(('localhost',8000))
        #Cuantos clientes va a tener
        objSocket.listen(5)
        print("Esperando conexión")

        while True:
            #Cuando alguien se conecte tomamos la direccion y abrimos conexion
            conexion,direccion=objSocket.accept()
            print("Cliente C++: ",direccion)
            #Enviamos datos codificados al cliente en formato UTF-8
            mensaje="Alegria"
            conexion.send(mensaje.encode(encoding='UTF-8',errors='strict'))
            #Cerramos conexion
            conexion.close()
    