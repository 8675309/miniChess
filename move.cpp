//Jennifer Solman hw1
#include "classes.h"

move::move(){
    square fromSquare;
    square toSquare;
    fromSquare.x = -1;
    fromSquare.y = -1;
    toSquare.x = -1;
    toSquare.y = -1;
    states child;
}

move::move(int q,int r,int z,int w){
    square fromSquare(q,r);
    square toSquare(z,w);
   // fromSquare.x = q;
   // fromSquare.y = r;
   // toSquare.x = z;
   // toSquare.y = w;
   states child;
}

move::~move(){

}
