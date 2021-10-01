import mediapipe as mp

class MallaFacial:
    def __init__(self):    
        pass
    
    def setMallaFacial(self,mallaFacial):
        self.mallaFacial=mallaFacial

    def getMallaFacial(self):
        #Creamos un objeto donde almacenar la malla facial
        mediapMallaFacial=mp.solutions.face_mesh
        #Creamos el objeto de la malla facial
        mallaFacial=mediapMallaFacial.FaceMesh()
        return mediapMallaFacial,mallaFacial

    def setPuntosMallaFacial(self,puntosMallaFacial):
        self.puntosMallaFacial=puntosMallaFacial

    def getPuntosMallaFacial(self):
        #Creamos un objeto donde almacenar los puntos faciales de mediapipe
        mediapDibujoPuntos=mp.solutions.drawing_utils
        #Asignamos valores a los puntos 
        puntosMalla=mediapDibujoPuntos.DrawingSpec(thickness=1,circle_radius=1,color=(0,255,255))
        return mediapDibujoPuntos,puntosMalla        