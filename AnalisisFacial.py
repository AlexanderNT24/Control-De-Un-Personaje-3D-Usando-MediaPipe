import cv2 #Opencv
import mediapipe as mp #Google
import math 

from Captura import Captura
from MallaFacial import MallaFacial


class AnalisisFacial:

    def __init__(self,tipoEntrada) :  
        objetoCaptura=Captura()
        objetoCaptura.setTipoEntrada(tipoEntrada)
        captura=objetoCaptura.getCaptura()
        objetoMallaFacial=MallaFacial()
        mediapMallaFacial,mallaFacial=objetoMallaFacial.getMallaFacial()
        mediapDibujoPuntos,dibujoPuntos=objetoMallaFacial.getPuntosMallaFacial()
        self.analisisVideo(captura,mediapDibujoPuntos,dibujoPuntos,mediapMallaFacial,mallaFacial)

    def analisisVideo(self,captura,mediapDibujoPuntos,dibujoPuntos,mediapMallaFacial,mallaFacial):
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
                            self.getLongitudes(listaPuntosFaciales)
        
            cv2.imshow("Frame",frame)
            #Codigo Ascii ESC es 27 para cerrar frame
            if cv2.waitKey(1)==27:
                break
        #Destruimos cada ventana creada por opencv 
        cv2.destroyAllWindows() 

    def getLongitudes(self,listaPuntosFaciales):
        #Segun el identificador tomamos coordenadas en x,y ([n:] desde la posicion n en adelante)
        x1Boca,y1Boca=listaPuntosFaciales[13][1:]
        x2Boca,y2Boca=listaPuntosFaciales[14][1:]
        #Devuelve la norma de un vector es decir distancia entre dos puntos
        longitudBoca=math.hypot(x2Boca-x1Boca,y2Boca-y1Boca)
        #print(f"Longitud Boca:{longitudBoca}")
        x1OjoIzquierdo,y1OjoIzquierdo=listaPuntosFaciales[159][1:]
        x2OjoIzquierdo,y2OjoIzquierdo=listaPuntosFaciales[145][1:]
        #Devuelve la norma de un vector es decir distancia entre dos puntos
        longitudOjoIzquierdo=math.hypot(x2OjoIzquierdo-x1OjoIzquierdo,y2OjoIzquierdo-y1OjoIzquierdo)
        #print(f"Longitud Ojo Izquierdo:{longitudOjoIzquierdo}")
        x1OjoDerecho,y1OjoDerecho=listaPuntosFaciales[374][1:]
        x2OjoDerecho,y2OjoDerecho=listaPuntosFaciales[386][1:]
        #Devuelve la norma de un vector es decir distancia entre dos puntos
        longitudOjoDerecho=math.hypot(x2OjoDerecho-x1OjoDerecho,y2OjoDerecho-y1OjoDerecho)
        #print(f"Longitud Ojo Derecho:{longitudOjoDerecho}")
        longitudes=[longitudBoca,longitudOjoIzquierdo,longitudOjoDerecho]
        print(f"Longitudes: Boca({longitudes[0]}) Ojo Izquierdo({longitudes[1]}) Ojo Derecho({longitudes[2]})")
        return longitudes



        