#define MAX_NAME 124
#define MAX_LISTAS 50
#define MAX_PRODUCTS

typedef struct _Product Product;
typedef struct _List List;
typedef struct _User User;

struct _Product{
    char nombre[MAX_NAME];
    int cantidad;
};

struct _List{
    char nombre[MAX_NAME];
};

struct _User{
    char nombre[MAX_NAME];
    char contraseña[MAX_NAME];
    List * lista[MAX_LISTAS];
};