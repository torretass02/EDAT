#define MAX_CONTACTOS 10000
#define MAX_NOMBRE 64
#define MAX_FORMAS 20

typedef struct _Forma Forma;
typedef struct _Contacto Contacto;
typedef struct _Agenda Agenda;
typedef struct _App App;

typedef enum {
    ERROR=0,
    OK=1     
} Status;

typedef enum {
    FALSE=0,
    TRUE=1
} Bool;

typedef enum {
    PERSONAL = 1,
    TRABAJO = 2
}ETIQUETA;

typedef enum {
    DIRECCION_POSTAL = 1,
    NUMERO_DE_TELEFONO = 2,
    CORREO_ELECTRONICO = 3
}FORMA;

struct _Forma{
    FORMA forma;
    ETIQUETA etiqueta;
};

struct _Contacto{
    char nombre[MAX_NOMBRE];
    char apellido[MAX_NOMBRE];
    Forma * forma[MAX_FORMAS];
};

struct _Agenda{
    char * nombre[MAX_NOMBRE];
    Contacto * contactos[MAX_CONTACTOS];
};

struct _App{
    
};