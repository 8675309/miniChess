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
    int value = -1;
}

move::move(int q,int r,int z,int w){
    square fromSquare(q,r);
    square toSquare(z,w);
   // fromSquare.x = q;
   // fromSquare.y = r;
   // toSquare.x = z;
   // toSquare.y = w;
   states child;
   int value = -1;
}

move& move::operator= (const move &original){
    fromSquare = original.fromSquare;
    toSquare = original.toSquare;
    child = original.child;
    value = original.value;
    return *this;
}

bool move::operator< (const move& other) const{
    return (value < other.value) ;
}

move::~move(){

}
