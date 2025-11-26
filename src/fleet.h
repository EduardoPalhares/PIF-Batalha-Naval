//Frota de navios (definição, posicionamento, status)

#ifndef FLEET_H
#define FLEET_H

typedef enum{
    ORIENT_H,
    ORIENT_V

}Orientation;

typedef struct{
    char name[20];
    int length;
    int hits;
    int placed;
}Ship;


typedef struct {
    Ship *ships;
    int count;
} Fleet;

#endif
