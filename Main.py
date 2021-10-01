from AnalisisFacial import AnalisisFacial

def main():
    tipoEntrada=input("Entrada video:")
    objetoAnalisisFacial=AnalisisFacial(tipoEntrada)

#Buena practica de programacion en python (Python ejecuta todos los modulos cargados en orden descendente y declara variables internas __name__ se le declara como main al modulo que se encarga de "correr", al trabajar con esta condicional )
if __name__ == "__main__":
    main()