import AnalisisFacial


def main():
    entrada=input("Entrada video:")
    objetoAnalisisFacial=AnalisisFacial.AnalisisFacial(entrada)
    

#Buena practica de programacion en python (Python ejecuta todos los modulos cargados en orden descendente y declara variables internas __name__ se le declara como main al modulo que se encarga de "correr", al trabajar con esta condicional )
if __name__ == "__main__":
    main()