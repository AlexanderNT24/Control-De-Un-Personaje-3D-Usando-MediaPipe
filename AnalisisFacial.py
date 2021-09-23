import cv2 #Opencv
import mediapipe as mp #Google
import math 
import pafy 

class AnalisisFacial:

    def __init__(self,entrada) :  
        captura=self.getCaptura(entrada)

        #Creamos un objeto donde almacenar los puntos faciales de mediapipe
        mediapDibujoPuntos=mp.solutions.drawing_utils
        #Asignamos valores a los puntos 
        configuracionDibujoPuntos=mediapDibujoPuntos.DrawingSpec(thickness=1,circle_radius=1,color=(0,255,255))
        #Creamos un objeto donde almacenar la malla facial
        mediapMallaFacial=mp.solutions.face_mesh
        #Creamos el objeto de la malla facial
        mallaFacial=mediapMallaFacial.FaceMesh()

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
                    mediapDibujoPuntos.draw_landmarks(frame,rostros,mediapMallaFacial.FACEMESH_CONTOURS,configuracionDibujoPuntos,configuracionDibujoPuntos)
                    #Puntos rostro detectado
                    for puntoID,puntos in enumerate (rostros.landmark):
                        #Alto y ancho de la ventana
                        altoVentana, anchoVentana,variable=frame.shape
                        posx=int(puntos.x*anchoVentana)
                        posy=int(puntos.y*altoVentana)
                        #print (puntoID,posx,posy)
                        #print(f"{altoVentana},{anchoVentana}, {c}")
                        #Apilamos los puntos faciales en una lista con sus coordenadas
                        listaPuntosFaciales.append([puntoID,posx,posy])
                        if len(listaPuntosFaciales)==468:
                            longitudes=self.getLongitudes(listaPuntosFaciales)
                            print(f"Longitudes: Boca({longitudes[0]})  Ojo Izquierdo({longitudes[1]})  Ojo Derecho({longitudes[2]})")
        
            cv2.imshow("Frame",frame)
            #Escape para cerrar frame
            tecla=cv2.waitKey(1)
            if tecla==27:
                break
        #Destruimos cada ventana creada por opencv 
        cv2.destroyAllWindows()   
    
    def getCaptura(self,entrada):
        if entrada=="1":        
            #Capturo el streaming de la webcam de el puerto de la webcam (0 para la nativa y 1,2.. para externas)
            captura=cv2.VideoCapture(0)
            return captura
        else: 
            #Se usa para hacer video streaming de una url de youtube
            url="https://www.youtube.com/watch?v=j6eGHROLKP8&t=17s&ab_channel=RingaTech"
            #Consigue metadatos de un video de youtube (url, vistas, usuario etc)
            video=pafy.new(url)
            datosVideo=video.getbest(preftype="mp4")
            #Iniciamos captura
            captura =cv2.VideoCapture()
            #Abrimos la ubicacion del video
            captura.open(datosVideo.url)
            #print(datosVideo.url)
            return captura
            
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
        return longitudes
        