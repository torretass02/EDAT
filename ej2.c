#include <string.h>

#define MAX_TRACKS 100

typedef struct _Position Position;
typedef struct _Track Track;
typedef struct _Gps Gps;

typedef enum {
    ERROR=0,
    OK=1     
} Status;


typedef enum {
    FALSE=0,
    TRUE=1
} Bool;

struct _Position{
    int latitud;
    int longitud;
};

struct _Track{
    Position * origen;
    Position * Destino;
};

struct _Gps{
    Track * tracks[MAX_TRACKS];
    int num_tracks;
};

Position * position_init(int latitud, int longitud);
void position_free(Position * p);

Track * track_init(Position * origen, Position * destino);
Status track_print (FILE * f, Track * t);
void track_free(Track * t);

Gps * gps_init();
int gps_getNumTracks(Gps * g);
Status gps_print (FILE * f, Gps * g);
Status gps_addTrack(Gps * g, Track * t);
void gps_free(Gps * g);

Status gps_print (FILE * f, Gps * g){
    if(!f || !g) return ERROR;
    int n, i;

    n = gps_getNumTracks(g);

    fprintf(f, "%d\n", n);

    for(i=0; i<n; i++){
        track_print(f, g->tracks[i]);
    }

    return OK;
}

Status gps_addTrack(Gps * g, Track * t){
    g->tracks[g->num_tracks] = t;
    g->num_tracks++;
}

int main(){
    Gps * g;
    Track * t;
    Position * origen, * destino;

    g = gps_init();

    origen = position_init(34, 58);
    destino = position_init(41, 71);

    t = track_init(origen, destino);

    gps_addTrack(g, t);

    gps_print(stdout, g);

    position_free(origen);
    position_free(destino);
    track_free(t);
    gps_free(g);
}