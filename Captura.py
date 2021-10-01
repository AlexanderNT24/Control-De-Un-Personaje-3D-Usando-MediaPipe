import cv2 #Opencv
import pafy 

class Captura:

    def __init__(self):   
        pass

    def setTipoEntrada(self,tipoEntrada):
        self.tipoEntrada=tipoEntrada

    def getTipoEntrada(self):
        return self.tipoEntrada

    def setCaptura(self,captura):
        self.captura=captura

    def getCaptura(self):
        if self.getTipoEntrada()=="webcam":        
            #Capturo el streaming de la webcam de el puerto de la webcam (0 para la nativa y 1,2.. para externas)
            self.captura=cv2.VideoCapture(0)
            return self.captura
        elif self.getTipoEntrada()=="streaming": 
            #Se usa para hacer video streaming de una url de youtube
            #Hardcodear 
            url="https://www.youtube.com/watch?v=j6eGHROLKP8&t=17s&ab_channel=RingaTech"
            #Consigue metadatos de un video de youtube (url, vistas, usuario etc)
            video=pafy.new(url)
            datosVideo=video.getbest(preftype="mp4")
            #Iniciamos captura
            self.captura =cv2.VideoCapture()
            #Abrimos la ubicacion del video
            self.captura.open(datosVideo.url)
            #print(datosVideo.url)
            return self.captura   
        else:
            print("NO VALIDA")

