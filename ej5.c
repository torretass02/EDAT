#define MAX_ROOMS 20
#define MAX_GUESTS 3
#define MAX_NAME 124

typedef struct _Guest Guest; 
typedef struct _Hotel Hotel;
typedef struct _Room Room;

typedef enum {
    ERROR=0,
    OK=1     
} Status;


typedef enum {
    FALSE=0,
    TRUE=1
} Bool;

typedef enum{
    SINGLE = 1,
    DOUBLE = 2,
    TRIPLE = 3
}TYPE_OF_ROOM;

struct _Hotel{
    int num_rooms;
    Room * rooms[MAX_ROOMS];
};

struct _Room{
    TYPE_OF_ROOM type;
    int num_guests;
    Guest * guests[MAX_GUESTS];
};

struct _Guest{
    char name[MAX_NAME];
    int ccn;
};

Bool room_isEmpty(Room *r);
Bool hotel_accommodateGuests(Hotel *h, Guest *g, int n);

Bool room_isEmpty(Room *r){
    if(!r) return FALSE; 
    if(r->num_guests == 0) return TRUE;
    else return FALSE;
}

Bool hotel_accommodateGuests(Hotel *h, Guest * g, int n){
    if(!h || !g || !n) return FALSE;

    if(n > 3) return FALSE;

    s

}