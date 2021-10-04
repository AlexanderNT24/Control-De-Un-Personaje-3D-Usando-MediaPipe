import cv2 #Opencv
import mediapipe as mp #Google
import time

from Captura import Captura
from MallaFacial import MallaFacial
from AnalisisFacial import AnalisisFacial
from Conexion import Conexion

def main():
    #tipoEntrada=input("Entrada video:")
    tipoEntrada="streaming"
    objetoCaptura=Captura(tipoEntrada)
    captura=objetoCaptura.getCaptura()

    objetoMallaFacial=MallaFacial()
    mediapMallaFacial,mallaFacial=objetoMallaFacial.getMallaFacial()
    mediapDibujoPuntos,dibujoPuntos=objetoMallaFacial.getPuntosMallaFacial()   
    analisisVideo(captura,mediapDibujoPuntos,dibujoPuntos,mediapMallaFacial,mallaFacial) 
    
def analisisVideo(captura,mediapDibujoPuntos,dibujoPuntos,mediapMallaFacial,mallaFacial):
    while True:
        #Lectura de frame y el estado (En Python puedo asignar datos a variables de la siguiente forma var1,var2=1,2) 
        estado,frame=captura.read()
        #Procesa el fotograma para entreganos la malla facial
        resultados=mallaFacial.process(frame)
        listaPuntosFaciales=[]
        #Si encuentra un rostro        
        if resultados.multi_face_landmarks:
            #Para todos los rostros detectados
            for rostros in resultados.multi_face_landmarks:
                #Dibujamos las conecciones de la malla
                mediapDibujoPuntos.draw_landmarks(frame,rostros,mediapMallaFacial.FACEMESH_CONTOURS,dibujoPuntos,dibujoPuntos)
                #Puntos rostro detectado
                for puntoID,puntos in enumerate (rostros.landmark):
                    #Alto y ancho de la ventana
                    altoVentana, anchoVentana,variable=frame.shape
                    posx=int(puntos.x*anchoVentana)
                    posy=int(puntos.y*altoVentana)
                    #Apilamos los puntos faciales en una lista con sus coordenadas
                    listaPuntosFaciales.append([puntoID,posx,posy])
                    if len(listaPuntosFaciales)==468:
                        objetoAnalisisFacial=AnalisisFacial(listaPuntosFaciales)
                        objetoConexion=Conexion(str(objetoAnalisisFacial.getLongitudes()))
                        objetoConexion.enviarDatos()           
                        time.sleep(0.1)      
                                           
        
        #cv2.imshow("Frame",frame)
        #Codigo Ascii ESC es 27 para cerrar frame
        if cv2.waitKey(1)==27:
            break
    #Destruimos cada ventana creada por opencv 
    cv2.destroyAllWindows()            

#Buena practica de programacion en python (Python ejecuta todos los modulos cargados en orden descendente y declara variables internas __name__ se le declara como main al modulo que se encarga de "correr", al trabajar con esta condicional )
if __name__ == "__main__":
    main()
