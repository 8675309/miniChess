//Jennifer Solman hw1
#include "classes.h"

move::move(){
    square fromSquare;
    square toSquare;
    fromSquare.x = -1;
    fromSquare.y = -1;
    toSquare.x = -1;
    toSquare.y = -1;
}

move::move(int q,int r,int z,int w){
    square fromSquare;
    square toSquare;
    fromSquare.x = q;
    fromSquare.y = r;
    toSquare.x = z;
    toSquare.y = w;
}

move::~move(){

}
