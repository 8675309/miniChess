//Jennifer Solman hw1

#include "classes.h"


square::square(){
   x = -1;
   y = -1;
}

square::square(int q,int r){
     x = q;
     y = r;
}

square& square::operator= (const square &original){
    x = original.x;
    y = original.y;
    return *this;
}

square::~square(){

}


