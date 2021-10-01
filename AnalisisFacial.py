import math 

class AnalisisFacial:
     
    longitudes=None
    listaPuntosFaciales=None

    def __init__(self,listaPuntosFaciales) :  
       self.listaPuntosFaciales=listaPuntosFaciales

    def getLongitudes(self):
        #Segun el identificador tomamos coordenadas en x,y ([n:] desde la posicion n en adelante)
        x1Boca,y1Boca=self.listaPuntosFaciales[13][1:]
        x2Boca,y2Boca=self.listaPuntosFaciales[14][1:]
        #Devuelve la norma de un vector es decir distancia entre dos puntos
        longitudBoca=math.hypot(x2Boca-x1Boca,y2Boca-y1Boca)
        #print(f"Longitud Boca:{longitudBoca}")
        x1OjoIzquierdo,y1OjoIzquierdo=self.listaPuntosFaciales[159][1:]
        x2OjoIzquierdo,y2OjoIzquierdo=self.listaPuntosFaciales[145][1:]
        #Devuelve la norma de un vector es decir distancia entre dos puntos
        longitudOjoIzquierdo=math.hypot(x2OjoIzquierdo-x1OjoIzquierdo,y2OjoIzquierdo-y1OjoIzquierdo)
        #print(f"Longitud Ojo Izquierdo:{longitudOjoIzquierdo}")
        x1OjoDerecho,y1OjoDerecho=self.listaPuntosFaciales[374][1:]
        x2OjoDerecho,y2OjoDerecho=self.listaPuntosFaciales[386][1:]
        #Devuelve la norma de un vector es decir distancia entre dos puntos
        longitudOjoDerecho=math.hypot(x2OjoDerecho-x1OjoDerecho,y2OjoDerecho-y1OjoDerecho)
        #print(f"Longitud Ojo Derecho:{longitudOjoDerecho}")
        longitudes=[longitudBoca,longitudOjoIzquierdo,longitudOjoDerecho]
        print(f"Longitudes: Boca({longitudes[0]}) Ojo Izquierdo({longitudes[1]}) Ojo Derecho({longitudes[2]})")
        return longitudes



        