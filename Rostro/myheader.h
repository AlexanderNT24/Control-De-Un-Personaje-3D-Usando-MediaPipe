//Cargar Modelos
extern GLuint listaModelos[10];
extern GLuint listaEscenario;

void limpiarData();

void cargarEscenario(char[100]);
void cargarNormalEscenario(char[100]);
void optimizarEscenario();

void cargarModelo(char[100]);
void cargarNormalModelo(char[100],int);
void optimizarModelo(int);


class data{
public:
    float v[3];
    float vn[3];


    data(){
            v[0]=0;v[1]=0;v[2]=0;vn[0]=0;vn[1]=0;vn[2]=0;
        }
};
