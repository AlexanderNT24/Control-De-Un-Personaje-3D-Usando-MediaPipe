#include<GL/glut.h>
#include <stdio.h>
#include<vector>
#include<string>
#include<math.h>
#include <iostream>
#include <fstream>
#include "myheader.h"
#include "RgbImage.h"
using namespace std;

//Camara
GLfloat camaraX=6;
GLfloat camaraY=5;
GLfloat camaraZ=5;

//Mouse
float alfa=0, beta=0;
float alfa2, beta2;
float angulo=0;
int  boton=-1;
float xc=0,zc=8, lx=0, lz=-1;
GLint x_0, y_0;
GLint x_2, y_2;

//Analisis Facial
float aspecto;
bool reconocerRostro;

//Texturas
GLuint listaModelos[10];

GLuint listaEscenario;

GLuint texture[5];
class data p;

//Menu
typedef enum {cieloAzul,cieloBlanco,cieloNegro,menuAvatar1,menuAvatar2,menuAvatar4,menuAdd0,menuAdd1,menuComp0,menuComp1,menuComp2} opcionesmenu;

//Dibujo
int avatar;

//MoverObj
double objx=0;
double objy=0;
//PrimerAvatar
double radio = 2;
double tamanioBoca=0.7;
double tamanioOjoIzq=0.5;
double tamanioOjoDer=0.5;
double rotacionCabeza=0;
double rotacionCabezaY=0;
double levantamientoCejaDer=2.35;
double levantamientoCejaIzq=2.5;

//LeerArchivo
int valorBoca;
int valorOjoDer;
int valorOjoIzq;
int valorCejaDer;
int valorCejaIzq;
int valorEmocion;
int valorRotacion;

//Addicionales
int adicional;

//Complementos
int complemento;

//Leer Archivo
void leerArchivo() {
    char cadena[128];
    string estadoBoca;
    string estadoOjoDer;
    string estadoOjoIzq;
    string estadoCejaDer;
    string estadoCejaIzq;
    string estadoEmocion;
    string estadoRotacion;
    try {
        ifstream fichero("D:/Avatar/Datos/DatosLongitudes.txt");

        while (!fichero.eof()) {
            fichero >> cadena;
            estadoBoca=cadena;
            fichero >> cadena;
            estadoOjoIzq=cadena;
             fichero >> cadena;
             estadoOjoDer=cadena;
             fichero>>cadena;
             estadoCejaIzq=cadena;
             fichero>>cadena;
             estadoCejaDer=cadena;
             fichero>>cadena;
             estadoEmocion=cadena;
             fichero>>cadena;
             estadoRotacion=cadena;

        }
        fichero.close();


        if(estadoBoca=="boca_cerrada") valorBoca=0;
        else if(estadoBoca=="boca_abierta") valorBoca=1;

        if(estadoOjoIzq=="ojoI_cerrado") valorOjoIzq=0;
        else if(estadoOjoIzq=="ojoI_abierto") valorOjoIzq=1;

        if(estadoOjoDer=="ojoD_cerrado") valorOjoDer=0;
        else if(estadoOjoDer=="ojoD_abierto") valorOjoDer=1;

         if(estadoCejaDer=="cejaD_normal") valorCejaDer=0;
        else if(estadoCejaDer=="cejaD_levantada") valorCejaDer=1;

        if(estadoCejaIzq=="cejaI_normal") valorCejaIzq=0;
        else if(estadoCejaIzq=="cejaI_levantada") valorCejaIzq=1;

        if(estadoEmocion=="emocion_neutro") valorEmocion=0;
        else if(estadoEmocion=="emocion_feliz") valorEmocion=1;
        else if(estadoEmocion=="emocion_enojo") valorEmocion=2;
        else if(estadoEmocion=="emocion_asombro") valorEmocion=3;

        if(estadoRotacion=="rotacion_nula") valorRotacion=0;
        else if(estadoRotacion=="rotacion_izquierda") valorRotacion=1;
        else if(estadoRotacion=="rotacion_derecha") valorRotacion=2;

        if(valorBoca==0)tamanioBoca=0.7;
        else tamanioBoca=0.9;

        if (valorOjoIzq==0)tamanioOjoIzq=0.1;
        else tamanioOjoIzq=0.5;

       if (valorOjoDer==0)tamanioOjoDer=0.1;
       else tamanioOjoDer=0.5;

       if(valorRotacion==2){rotacionCabeza=6;rotacionCabezaY=1;}
       else if(valorRotacion==0){rotacionCabeza=0;rotacionCabezaY=0;}
       else if(valorRotacion==1){rotacionCabeza=-6;rotacionCabezaY=1;}

    }
    catch (int valor) {
        cout << "Error codigo: " << valor;
    }
    cout <<"Boca: "<< estadoBoca<<" Ojo Izquierdo:" <<estadoOjoIzq<<" Ojo Derecho: "<<estadoOjoDer<< "Ceja Izquierda: "<<estadoCejaIzq<<" Ceja Derecha:"<<estadoCejaDer<<" Emocion: "<<estadoEmocion<<" Rotacion: "<<estadoRotacion<<endl;
    cout <<"Valor Boca: "<< valorBoca<<" Valor Ojo Izquierdo:" <<valorOjoIzq<<" Valor Ojo Derecho: "<<valorOjoDer<<" Valor Ceja Izquierda: "<<valorCejaDer<<" Valor Ceja Derecha: "<<valorCejaIzq<<" Valor Emocion: "<<valorEmocion<<" Valor Rotacion: "<<valorRotacion<<endl;
}

void exportarModelos() {

    cargarModelo("Modelos/cubo.obj");
    cargarNormalModelo("Modelos/cubo.obj",1);
    optimizarModelo(1);
    limpiarData();

    cargarModelo("Modelos/Escritorio.obj");
    cargarNormalModelo("Modelos/Escritorio.obj",2);
    optimizarModelo(2);
    limpiarData();

     cargarModelo("Modelos/Cuerpo.obj");
    cargarNormalModelo("Modelos/Cuerpo.obj",3);
    optimizarModelo(3);
    limpiarData();

    cargarModelo("Modelos/Gorro.obj");
    cargarNormalModelo("Modelos/Gorro.obj",4);
    optimizarModelo(4);
    limpiarData();

     cargarModelo("Modelos/Mano.obj");
    cargarNormalModelo("Modelos/Mano.obj",5);
    optimizarModelo(5);
    limpiarData();

    cargarModelo("Modelos/Sombrero.obj");
    cargarNormalModelo("Modelos/Sombrero.obj",6);
    optimizarModelo(6);
    limpiarData();


    cargarEscenario("Modelos/LetrasMain.obj");
    cargarNormalEscenario("Modelos/LetrasMain.obj");
    optimizarEscenario();


}

void desabilitarTexturas(){
   glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

}
//Texturas
void tomarTexturas(const char* fileName, int index) {
    RgbImage theTexMap(fileName);
    glGenTextures(1, &texture[index]);
    glBindTexture(GL_TEXTURE_2D, texture[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

}

void cargarTexturas() {
    tomarTexturas("Texturas/piel.bmp", 0);
    tomarTexturas("Texturas/rojo.bmp", 1);
    tomarTexturas("Texturas/pielRobot.bmp", 2);
    tomarTexturas("Texturas/Madera.bmp", 3);
    tomarTexturas("Texturas/Naranja.bmp", 4);
}

void insertarTexturas(int codigo) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[codigo]);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
}

//Luces
void cargarLucesyMaterial() {
    GLfloat objcolor[] = { 0.5f,0.5f,0.5f,1.f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float LightPosition[] = { 0.0f, 20.0f, 2.0f, 1.0f };
    GLfloat light0_position[] = { 0,0,1.0, 0.0 };
    // --------------- LIGHTING
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    // Set up the material information for objects
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, objcolor);
    glMateriali(GL_FRONT, GL_SHININESS, 50);
}

//Luces
void luces(float r, float g, float b, float posx, float posy, float posz) {
    glEnable(GL_LIGHT0);
    float light0_position[] = { posx,posy,posz,0 };
    float light0_diffuso_color[] = { r, g, b };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuso_color);

    ///MATERIAL
    float brillo = 2;
    float material_especular[] = { 0.2,0.2,0.2,1 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);

}

//Primer Avatar
void dibujarPlano() {
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(5, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 5, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, 5);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
}

void dibujarCejas(){

    if(valorCejaDer==1)levantamientoCejaDer=2.35+0.1;
    else levantamientoCejaDer=2.35;
    if(valorCejaIzq==1)levantamientoCejaIzq=2.5+0.1;
    else levantamientoCejaIzq=2.5;

    glPushMatrix();
    glTranslatef(2.2, levantamientoCejaIzq, -0.6);
    glRotatef(95, 1, 1, 1);

    glBegin(GL_POLYGON);
    for (float i = 0; i < 1000; i += 0.1)
    {
        float x = 0.05 * cos(i);
        float y = 0.47 * sin(i);
        glVertex2f(x - 1, y + 2.2);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, levantamientoCejaDer, 1.4);
    glRotatef(70, 1, 0, 0);
    glBegin(GL_POLYGON);
    for (float i = 0; i < 1000; i += 0.1)
    {
        float x = 0.15 * cos(i);
        float y = 0.57 * sin(i);
        glVertex2f(x + 0.29, y - 0.33);
    }
      glEnd();
    glPopMatrix();


}

void dibujarCabeza() {

    glutSolidSphere(radio, 50, 50);

    glPopMatrix();


}

void dibujarCuello() {
    glPushMatrix();
     glRotatef(90, 1, 0, 0);
    luces(0.980, 0.647, 0.447, 1, 1, 0);
    glTranslated(0, 0, 1);
    GLUquadricObj* objetoQ;
    objetoQ = gluNewQuadric();
    gluCylinder(objetoQ, 1, 1, 1.5, 50, 50);
    glTranslated(0, 0, 1.5);
    gluCylinder(objetoQ, 1, 2, 1, 25, 25);
    glPopMatrix();
}

void dibujarOjosCerrados(){
   glPushMatrix();
    if (valorOjoIzq==0){
    //OjoIZQ
    glTranslatef(2.2, 1.7, -0.6);
    glRotatef(90, 1, 1, 1);

    glBegin(GL_POLYGON);
    for (float i = 0; i < 1000; i += 0.1)
    {
        float x = 0.1 * cos(i);
        float y = 0.4 * sin(i);
        glVertex2f(x - 1, y + 2.2);
    }
    glEnd();
    glPopMatrix();
    }

    if (valorOjoDer==0){
    ///OjoDER
    glPushMatrix();
    glTranslatef(2, 1.8, 1.4);
    glRotatef(70, 1, 0, 0);
    glBegin(GL_POLYGON);
    for (float i = 0; i < 1000; i += 0.1)
    {
        float x = 0.2 * cos(i);
        float y = 0.5 * sin(i);
        glVertex2f(x + 0.29, y - 0.33);
    }
    glEnd();
    glPopMatrix();}
    glPopMatrix();

}

void dibujarOjos() {
    glPushMatrix();
    if(valorOjoIzq==0)dibujarOjosCerrados();
    else{
    //OjoIZQ
    glTranslatef(2.2, 1.6, -0.6);
    glRotatef(90, 1, 1, 1);

    glBegin(GL_POLYGON);
    for (float i = 0; i < 1000; i += 0.1)
    {
        float x = 0.5 * cos(i);
        float y = 0.4 * sin(i);
        glVertex2f(x - 1, y + 2.2);
    }
    glEnd();
    glPopMatrix();
    }

 if(valorOjoDer==0)dibujarOjosCerrados();
    else{
    ///OjoDER
    glPushMatrix();
    glTranslatef(2, 2, 1.4);
    glRotatef(20, 1, 1, 1);
    glBegin(GL_POLYGON);
    for (float i = 0; i < 1000; i += 0.1)
    {
        float x = 0.5 * cos(i);
        float y = 0.4 * sin(i);
        glVertex2f(x + 0.29, y - 0.33);
    }
    glEnd();
    glPopMatrix();
    }

}

void dibujarIris() {

    glPushMatrix();
    if(valorOjoIzq==0)dibujarOjosCerrados();
    else{
    ///irisIZQ
    glPushMatrix();
    glScalef(0.21, 0.21, 0.21);
    glTranslatef(8.4, 8.4, 8.5);
    glutSolidSphere(0.4, 50, 50);
    glPopMatrix();
    }
    if(valorOjoDer==0)dibujarOjosCerrados();
    else{
    ///irisDER
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(11.1, 9.2, 7);
    glutSolidSphere(0.4, 50, 50);
    glPopMatrix();
    }
    glPopMatrix();
}

void dibujarBoca() {
    glPushMatrix();
    glRotatef(1, 0, 1, 0);
    glScalef(tamanioBoca, tamanioBoca, 0.255);
    glTranslatef(1.9, 1.5, -1.2);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
}

void dibujar_dientes() {
    glPushMatrix();
    glPushMatrix();
    glRotatef(35, 0, 0, 1);
    glScalef(0.0077, 0.011, 0.022);
    glTranslatef(329, 40.8, -33.8);
    glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(35, 0, 0, 1);
    glScalef(0.0077, 0.022, 0.0244);
    glTranslatef(329, 11.9, -31);
    glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(35, 0, 0, 1);
    glScalef(0.0077, 0.022, 0.0244);
    glTranslatef(329, 1, -29.8);
    glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(35, 0, 0, 1);
    glScalef(0.0077, 0.011, 0.022);
    glTranslatef(329, -15, -32);
    glutSolidCube(10);
    glPopMatrix();
    glPopMatrix();
}

void validarColisiones(){
    if(rotacionCabeza>=6)rotacionCabeza=6;
    if(rotacionCabeza<=-3.5)rotacionCabeza=-3.5;

    if(rotacionCabezaY>=8)rotacionCabezaY=8;
    if(rotacionCabezaY<=-3.5)rotacionCabezaY=-3.5;
}

void dibujarCuerpo(){
glPushMatrix();
 luces(1, 1, 1, 10, 10, 10);
 insertarTexturas(4);
    glCallList(listaModelos[3]);
 glPopMatrix();
 desabilitarTexturas();
}

void dibujarAvatar1(){
    validarColisiones();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    luces(0.980, 0.647, 0.447, 1, 1, 0);
    //dibujarCuello();
    glPopMatrix();

    glRotated(rotacionCabeza,0,1,0);
    glRotated(rotacionCabezaY,0,0,1);
    if(valorEmocion==2) {
            radio=2.01;
           luces(1, 0, 0, 1, 1, 0);
    }
    else {
            radio=2;
            luces(0.980, 0.647, 0.447, 1, 1, 0);
    }

    glPushMatrix();
    dibujarCabeza();
    glPopMatrix();



    glPushMatrix();
    glPushMatrix();
    luces(0, 0, 0, 0, 0, 0);
    dibujarIris();
    glPopMatrix();

    //OJOS
    glPushMatrix();

    luces(1, 1, 1, 0.2, 0, 0.2);
    dibujarOjos();
    glPopMatrix();

    glPushMatrix();
    luces(0, 0, 0, 0, 0, 0);
    glRotatef(90, 1, 0, 0);
    dibujarBoca();
    glPopMatrix();

    if(tamanioBoca>=0.9 && valorEmocion==1){
    glPushMatrix();
    luces(1, 1, 1, 1, 1, 1);
    glRotatef(90, 1, 0, 0);
    dibujar_dientes();
    glPopMatrix();
    }

    //Cejas
    glPushMatrix();
    dibujarCejas();
    glPopMatrix();
    dibujarCuerpo();

    glPopMatrix();


}

//Dibujar Avatar 2
void ojosRobot(){
    ///ojo izquierdo
    if(valorOjoDer==1){
    glPushMatrix();
    if (valorEmocion==1) luces(0,1,0,1,0,1);
    else if(valorEmocion==2)luces(1,0,0,1,0,1);
    else if(valorEmocion==3)luces(1, 1, 0,1,0,1);
    else  luces(0,0,1,1,0,1);

    glRotatef(10, 0, 1, 0);
    glScalef(0.7, 1, 0.3);
    glTranslatef(1.144, 0.8, -1.2);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
    }
    if(valorOjoDer==1){
    /// derecho
    glPushMatrix();
    if (valorEmocion==1) luces(0,1,0,1,0,1);
    else if(valorEmocion==2)luces(1,0,0,1,0,1);
    else if(valorEmocion==3)luces(1, 1, 0,1,0,1);
    else  luces(0,0,1,1,0,1);
    glRotatef(10, 0, 1, 0);
    glRotatef(-25, 0, 0, 1);
    glScalef(0.7, 1.1, 0.3);
    glTranslatef(-1.7, 0.033, 1.2);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
    }
}

void bocaRobot(){
    if(valorBoca==1){
    glPushMatrix();
    if (valorEmocion==1) luces(0,1,0,1,0,1);
    else if(valorEmocion==2)luces(1,0,0,1,0,1);
    else if(valorEmocion==3)luces(1, 1, 0,1,0,1);

    glRotatef(37,0,1,0);
    glRotatef(3,0,0,1);
    glScalef(1.9,0.7,0.5);
    glTranslatef(-0.2,-1.8,-0.166);
    glutSolidCube(0.8);
    glPopMatrix();
    }
}

void dibujarAvatar2(){
         glPushMatrix();
         luces(0.7,1,1,1,1,1);
         insertarTexturas(2);
         glTranslatef(0,-2.2,-0.2);
         glRotatef(55,0,1,0);
         glRotatef(-25,1,0,0);
         glRotatef(-25,0,1,0);
         glScalef(0.02, 0.02, 0.02);
         glRotated(rotacionCabeza,0,1,0);
         glRotated(rotacionCabezaY,0,0,1);
         glCallList(listaModelos[1]);
         glPopMatrix();
         ojosRobot();
         bocaRobot();
}

//Sala
void dibujarSala(){
        glClearColor(1, 1, 1, 1.0);
        beta=0.88;
        alfa= 1.58;
        glTranslatef(-1.2, 0, 0);
       cargarLucesyMaterial();
       insertarTexturas(1);
       glPushMatrix();
       glScalef(1, 1, 1);
       glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
       glCallList(listaEscenario);
       glPopMatrix();
       desabilitarTexturas();

}

void dibujarEscritorio(){
     insertarTexturas(3);
     glPushMatrix();
     cargarLucesyMaterial();
     glTranslatef(objx,objy,0);
     cout<<"x:"<<objx<<"y:"<<objy;
     glScalef(1, 1, 1);
    glCallList(listaModelos[2]);
    glPopMatrix();

}

void dibujarAdicionales(){
      switch(adicional){
    case 1:
        dibujarEscritorio();
        ;break;
    default: ;break;

    }
    desabilitarTexturas();
}

void dibujarManos(){
insertarTexturas(0);
     glPushMatrix();
     cargarLucesyMaterial();
     glScalef(1, 1, 1);
glCallList(listaModelos[5]);
glPopMatrix();
}

void dibujarGorro(){
insertarTexturas(0);
     glPushMatrix();
     cargarLucesyMaterial();
     glScalef(1, 1, 1);
glCallList(listaModelos[4]);
glPopMatrix();

}

void dibujarSombrero(){



insertarTexturas(2);
     glPushMatrix();
     cargarLucesyMaterial();
     glScalef(1, 1, 1);
glCallList(listaModelos[6]);
glPopMatrix();
}

void dibujarComplementos(){

    switch(complemento){
    case 1:
        dibujarGorro();
        ;break;

    case 2:dibujarSombrero();break;
    default:;break;

    }


}

//Dibujar Principal
void dibujar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camaraX, camaraY, camaraZ,
       -beta/50, alfa/50, 0,
        0, 1, 0);
        cout<<beta<<" ";
    switch (avatar){
     case 1:
         glCallList(listaEscenario);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          dibujarAvatar1();
          dibujarAdicionales();
          dibujarComplementos();
          break;
     case 2:
         dibujarAdicionales();
         dibujarAvatar2();
         break;
     default:
         dibujarSala();
         break;
    }





   desabilitarTexturas();
   glutSwapBuffers();
}

void menu(int opcion){
    switch(opcion){
    case cieloAzul:
          glClearColor(0, 1.0, 0, 1.0);
    break;
    case cieloBlanco:
         glClearColor(1, 1, 1, 1.0);
    break;
    case cieloNegro:
         glClearColor(0, 0, 0, 1.0);
    break;
    case menuAvatar1:
        avatar=1;
    break;
    case menuAvatar2:
       avatar=2;
    break;
     case menuAvatar4:
       avatar=4;
    break;
     case menuAdd1:
       adicional=1;
     break;
     case menuAdd0:
        adicional=0;
        break;
    case menuComp0:
        complemento=0;
        break;
    case menuComp1:
        complemento=1;
        break;
    case menuComp2:
        complemento=2;
        break;
    }
 glutPostRedisplay();
}

void creacionmenu () {
        int menuPrincipal, menuFondo, menuAvatar,menuAdicional,menuComplementos;

        menuFondo=glutCreateMenu(menu);
            glutAddMenuEntry("VERDE", cieloAzul);
            glutAddMenuEntry("BLANCO", cieloBlanco);
            glutAddMenuEntry("NEGRO", cieloNegro);

        menuAvatar=glutCreateMenu(menu);
            glutAddMenuEntry("DIBUJO ANIMADO", menuAvatar1);
            glutAddMenuEntry("ROBOT", menuAvatar2);
            glutAddMenuEntry("PRINCIPAL", menuAvatar4);

        menuAdicional=glutCreateMenu(menu);
        glutAddMenuEntry("ESCRITORIO", menuAdd1);
        glutAddMenuEntry("NINGUNO", menuAdd0);

        menuComplementos=glutCreateMenu(menu);
        glutAddMenuEntry("GORRA", menuComp1);
        glutAddMenuEntry("SOMBRERO", menuComp2);
        glutAddMenuEntry("NINGUNO", menuComp0);


        menuPrincipal=glutCreateMenu(menu);
            glutAddSubMenu("COLOR DE FONDO", menuFondo);
            glutAddSubMenu("AVATAR", menuAvatar);
            glutAddSubMenu("AGREGAR OBJETOS AL ESCENARIO",menuAdicional);
            glutAddSubMenu("AGREGAR COMPLEMENTOS AL AVATAR",menuComplementos);


        glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void timer(int i){
    if(reconocerRostro){
    leerArchivo();

    glutPostRedisplay();
    }


    glutTimerFunc(100/30,timer,i);


}

void iniciar(){
    glClearColor(1.0, 1.0, 1.0, 0.0); //fondo negro
}

void redimensionar(int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    aspecto = (float)x / (float)y;
    glLoadIdentity();
    gluPerspective(50, aspecto, 1, 50);

    glMatrixMode(GL_MODELVIEW);

}

void onMouse(int button, int state , int x, int y){
    if ((button==GLUT_LEFT_BUTTON) & (state==GLUT_DOWN)){
       x_0=x;
       y_0=y;
       boton=1;
    }
    else{
        x_2=x;
       y_2=y;
        boton=0;
    }
    if(button==3){
        camaraZ+=0.1;

    }
    else
    if(button==4){
        camaraZ-=0.1;
    }


}

void onMotion (int x, int y){
    if (boton==1){
       alfa= (alfa+(y-y_0));
       beta= (beta+  (x-x_0));
        x_0=x;
       y_0=y;
    }
    else{
        alfa2= (alfa2+(y-y_2));
       beta2= (beta2+  (x-x_2));
        x_2=x;
       y_2=y;

    }
    glutPostRedisplay();
}

void tecladoEspecial(int key, int x, int y){
   if(key==GLUT_KEY_RIGHT) camaraX+=0.1;
   else if (key==GLUT_KEY_LEFT) camaraX-=0.1;
   else if (key==GLUT_KEY_UP) camaraY+=0.1;
   else if (key==GLUT_KEY_DOWN) camaraY-=0.1;
   else if (key==GLUT_KEY_F1) reconocerRostro=true;
   else if (key==GLUT_KEY_F2) reconocerRostro=false;
   if (key==GLUT_KEY_F3) {
       alfa=0;
      beta=0;
      camaraX=6;
      camaraY=5;}
      camaraZ=5;
    glutPostRedisplay();
}

void tecladoNormal(unsigned char key, int x, int y){


     if (key=='w')objy+=0.5;
     else if (key=='s')objy-=0.5;
     else if (key=='a')objx+=0.5;
     else if (key=='d')objx-=0.5;



glutPostRedisplay();



}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("JAEL");
    iniciar();
    cargarTexturas();
    exportarModelos();
    glutDisplayFunc(dibujar);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(redimensionar);
    glutSpecialFunc(tecladoEspecial);
    glutKeyboardFunc(tecladoNormal);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutTimerFunc(100, timer, 0 );
    creacionmenu ();
    glutMainLoop();

}
