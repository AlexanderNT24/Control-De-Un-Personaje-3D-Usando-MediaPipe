import cv2 #Opencv
import pafy 

class Captura:

    tipoEntrada=""
    captura=None
    tipo="mp4"
    url=""

    def __init__(self,tipoEntrada,url="https://www.youtube.com/watch?v=j6eGHROLKP8&t=17s&ab_channel=RingaTech"):   
        self.tipoEntrada=tipoEntrada
        self.url=url

    def getCaptura(self):
        if self.tipoEntrada=="webcam":        
            #Capturo el streaming de la webcam de el puerto de la webcam (0 para la nativa y 1,2.. para externas)
            self.captura=cv2.VideoCapture(0)
        elif self.tipoEntrada=="streaming": 
            #Se usa para hacer video streaming de una url de youtube
            #Hardcodear 
            #Consigue metadatos de un video de youtube (url, vistas, usuario etc)
            video=pafy.new(self.url)
            datosVideo=video.getbest(preftype="mp4")
            #Iniciamos captura
            self.captura =cv2.VideoCapture()
            #Abrimos la ubicacion del video
            self.captura.open(datosVideo.url)
            #print(datosVideo.url)
        else:
            print("NO VALIDA")
            self.captura = None
        return self.captura    

