from socket import socket
import cv2 #Opencv
import mediapipe as mp #Google
import math 
import pafy 
import Socket

class AnalisisFacial:
    def __init__(self,entrada) :
        if entrada=="1":        
            #Capturo el streaming de la webcam de el puerto de la webcam (0 para la nativa y 1,2.. para externas)
            captura=cv2.VideoCapture(1)
        else: 
            #Se usa para hacer video streaming de una url de youtube
            url="https://www.youtube.com/watch?v=j6eGHROLKP8&t=17s&ab_channel=RingaTech"
            video=pafy.new(url)
            best=video.getbest(preftype="mp4")

            captura =cv2.VideoCapture()
            captura.open(best.url)
        objetoSocket=Socket.Socket()
        #Iniciamos la funcion de dibujo de la mallafacial de mediapipe
        mediapDibujo=mp.solutions.drawing_utils
        #Asignamos grosor a las lineas de la mallafacial
        configuracionDibujo=mediapDibujo.DrawingSpec(thickness=1,circle_radius=1,color=(0,255,255))

        #Creamos un objeto donde almacenar la malla facial
        mediapMallaFacial=mp.solutions.face_mesh
        #Creamos el objeto de la malla facial
        mallaFacial=mediapMallaFacial.FaceMesh()

        while True:

            #Lectura de frame y el estado
            estado,frame=captura.read()
            
            #Procesa el fotograma para entreganos la malla facial
            resultados=mallaFacial.process(frame)

            vectorPuntosFaciales=[]

            #Si encuentra un rostro        
            if resultados.multi_face_landmarks:
                #Para todos los rostros detectados
                for rostros in resultados.multi_face_landmarks:
                    #Dibujamos las conecciones de la malla
                    mediapDibujo.draw_landmarks(frame,rostros,mediapMallaFacial.FACEMESH_CONTOURS,configuracionDibujo,configuracionDibujo)
                    #Puntos rostro detectado
                    for punto,puntos in enumerate (rostros.landmark):
                        #Alto y ancho de la ventana
                        altoVentana, anchoVentana,variable=frame.shape
        
                        posx=int(puntos.x*anchoVentana)
                        posy=int(puntos.y*altoVentana)
                        #print("--------")
                        #print(f"{altoVentana},{anchoVentana}, {c}")
                        #print(f"{x}, {y}")
                        
                        vectorPuntosFaciales.append([punto,posx,posy])
                        #print(len(lista))
                        if len(vectorPuntosFaciales)==468:
                            x1Boca,y1Boca=vectorPuntosFaciales[13][1:]
                            x2Boca,y2Boca=vectorPuntosFaciales[14][1:]
                            #Devuelve la norma de un vector es decir distancia entre dos puntos
                            longitudBoca=math.hypot(x2Boca-x1Boca,y2Boca-y1Boca)
                            print(f"Longitud Boca:{longitudBoca}")
                            x1OjoIzquierdo,y1OjoIzquierdo=vectorPuntosFaciales[159][1:]
                            x2OjoIzquierdo,y2OjoIzquierdo=vectorPuntosFaciales[145][1:]
                            #Devuelve la norma de un vector es decir distancia entre dos puntos
                            longitudOjoIzquierdo=math.hypot(x2OjoIzquierdo-x1OjoIzquierdo,y2OjoIzquierdo-y1OjoIzquierdo)
                            print(f"Longitud Ojo Izquierdo:{longitudOjoIzquierdo}")
                            x1OjoDerecho,y1OjoDerecho=vectorPuntosFaciales[374][1:]
                            x2OjoDerecho,y2OjoDerecho=vectorPuntosFaciales[386][1:]
                            #Devuelve la norma de un vector es decir distancia entre dos puntos
                            longitudOjoDerecho=math.hypot(x2OjoDerecho-x1OjoDerecho,y2OjoDerecho-y1OjoDerecho)
                            print(f"Longitud Ojo Derecho:{longitudOjoDerecho}")
                                       
            cv2.imshow("Frame",frame)
            t=cv2.waitKey(1)
            if t==27:
                break

        captura.relase()
        cv2.destroyAllWindows()   
