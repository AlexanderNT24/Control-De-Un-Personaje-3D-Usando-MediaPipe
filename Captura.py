import cv2 #Opencv
import pafy 

class Captura():
    tipoEntrada = 'webcam'
    data = ''
    url = ''
    type = "mp4"
    captura= None

    def __init__(self, tipoEntrada, url):   
        self.tipoEntrada = tipoEntrada
        self.url = url


    def getData(self):
        if self.tipoEntrada=="webcam":        
            #Capturo el streaming de la webcam de el puerto de la webcam (0 para la nativa y 1,2.. para externas)
            self.captura=cv2.VideoCapture(0)
        elif self.tipoEntrada=="streaming": 
            #Se usa para hacer video streaming de una url de youtube
            #Consigue metadatos de un video de youtube (url, vistas, usuario etc)
            video=pafy.new(self.url)
            datosVideo=video.getbest(preftype=self.type)
            #Iniciamos captura
            self.captura =cv2.VideoCapture()
            #Abrimos la ubicacion del video
            self.captura.open(datosVideo.url)
            #print(datosVideo.url)
        else:
            self.captura = None
        return self.captura
