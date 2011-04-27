//Jennifer Solman hw1

#include "classes.h"
#define single 1
#define multiple 0
states::states(){
    onMove = 'W';
    count = 0;
}

//some stuff

states::~states(){

}

int states::inBounds(int x, int y){
    if(x > -1 && x < 6 && y > -1 && y < 5)
	return 1;
    else
	return 0;
}

//0 if coordinate square is empty 
int states::checkEmpty(int x, int y, char color){
    if(board[x][y] == 120)
	return 0; //empty
    else if(color == 'W'){
	if(board[x][y] > 97 && board[x][y] < 115)
	    return 1;  //opponent
	else 
	    return 2; //self
    }
    else if(color == 'B'){
	if(board[x][y] < 83 && board[x][y] > 65)
	    return 1;
	else 
	    return 2;
    }
    else 
        cout << "line 39 states very bad";
	return 3; //error (very bad)
}

int states::findPieces(char color, square *pieces){
    int i,j,lower,upper;
    int k = 0;
    //square pieces[10];
    if(color == 'W'){
	lower = 65; //ascii range for pieces
	upper = 83; //upper case
    }
    else if(color == 'B'){
	lower = 97;
	upper = 115;
    }
    for(i=0; i<=5; ++i){
	 for(j=0; j<=4; ++j){
	    if(board[i][j] > lower && board[i][j] < upper){
		    pieces[k].x = i;
		    pieces[k].y = j;
		    ++k;
	    }
	 }
    }
    return k;
}

void states::scan(int x, int y, move *moves, int &movesIndex, int dx, int dy, int movement, char color){
    int toX = x;
    int toY = y;
    //CHECK BOARD AT VARIOUS POINTS TO FIGURE OUT WHY CHECK EMPTY IS GIVING 1
   //ALSO WRITE PRINT MOVE
    while(inBounds(toX + dx, toY + dy)){
         //if square is empty 0 or contains opponent 1
	if(checkEmpty(toX + dx, toY + dy,color) == 0 || checkEmpty(toX + dx, toY + dy,color) == 1 ){
	  cout << "line 73 "  << " cE " << checkEmpty(toX + dx, toY + dy,color) << '\n'; 
	    moves[movesIndex].fromSquare.x = x; // new move(x, y, toX + dx, toY + dy);
	    moves[movesIndex].fromSquare.y = y; 
	    moves[movesIndex].toSquare.x = toX + dx; 
	    moves[movesIndex].toSquare.y = toY + dy;
	    //if an opponents piece is on the square or we are collecting single moves
	    if(checkEmpty(toX + dx, toY + dy,color) == 1 || movement == single){
		cout << "line 79 movement " << movement << " cE " << checkEmpty(toX + dx, toY + dy,color)<< '\n'; 
		++movesIndex;
                cout << "line 81 movesIndex " << movesIndex << '\n';
           
		break;
            }
	    else{ 
	        toX = toX + dx;
                toY = toY + dy;
		++movesIndex;
                cout << "line 86 movesIndex " << movesIndex << '\n';
	    }
        }
	else{   //self is on the square
	    break;
        }
    }
}

void states::checkNSEW(int x, int y, move *moves, int &movesIndex, int movement, char color){
    scan(x, y, moves, movesIndex, -1, 0, movement, color); //north
    scan(x, y, moves, movesIndex, 1, 0, movement, color); //south
    scan(x, y, moves, movesIndex, 0, 1, movement, color); //east
    scan(x, y, moves, movesIndex, 0, -1, movement, color); //west
}

void states::checkDiag(int x, int y, move *moves, int &movesIndex, int movement, char color){
    scan(x, y, moves, movesIndex, -1,1, movement,color); //north east
    scan(x, y, moves, movesIndex, 1, 1, movement,color); //south east
    scan(x, y, moves, movesIndex, -1, -1, movement,color); //north west
    scan(x, y, moves, movesIndex, 1, -1, movement,color); //south west
}

void states::queenMoves(int x, int y, move *moves, int &movesIndex, char color){
    checkNSEW(x, y, moves, movesIndex, multiple, color); 
    checkDiag(x, y, moves, movesIndex, multiple, color); 
}

void states::kingMoves(int x, int y, move *moves, int &movesIndex, char color){
    checkNSEW(x, y, moves, movesIndex, single, color); 
    checkDiag(x, y, moves, movesIndex, single, color); 
}

void states::bishopMoves(int x, int y, move *moves, int &movesIndex, char color){
    checkDiag(x, y, moves, movesIndex, multiple, color); 
}

void states::rookMoves(int x, int y, move *moves, int &movesIndex, char color){
    checkNSEW(x, y, moves, movesIndex, multiple, color); 
}

void states::knightMoves(int x, int y, move *moves, int &movesIndex, char color){
    
    scan(x, y, moves, movesIndex, -1, 2, single,color); 
    scan(x, y, moves, movesIndex, -1, -2, single,color); 
    scan(x, y, moves, movesIndex, 1, 2, single,color); 
    scan(x, y, moves, movesIndex, 1, -2, single,color); 
    scan(x, y, moves, movesIndex, -2, 1, single,color); 
    scan(x, y, moves, movesIndex, -2, -1, single,color); 
    scan(x, y, moves, movesIndex, 2, 1, single,color); 
    scan(x, y, moves, movesIndex, 2, -1, single,color); 
}

void states::wPawnMoves(int x, int y, move *moves, int &movesIndex){
    scan(x, y, moves, movesIndex, -1, 0, single, 'W'); //north
    //check for diagonal attack NW NE
    pawnAttacks(x, y, moves, movesIndex, -1, -1, 'W');
    pawnAttacks(x, y, moves, movesIndex, -1, 1, 'W');
}

void states::bPawnMoves(int x, int y, move *moves, int &movesIndex){
    scan(x, y, moves, movesIndex, 1, 0, single, 'B'); //south
    //check for diagonal attack SW SE
    pawnAttacks(x, y, moves, movesIndex, 1, -1, 'B');
    pawnAttacks(x, y, moves, movesIndex, 1, 1, 'B');
}

void states::pawnAttacks(int x, int y, move *moves, int &movesIndex, int dx, int dy, char color){
    if(inBounds(x + dx, y + dy)){
         //if square contains opponent
	if(checkEmpty(x + dx, y + dy,color) == 1 ){
	    //moves[movesIndex] = new move(x, y, x + dx, y + dy);
	    moves[movesIndex].fromSquare.x = x; // new move(x, y, toX + dx, toY + dy);
	    moves[movesIndex].fromSquare.y = y; 
	    moves[movesIndex].toSquare.x = x + dx; 
	    moves[movesIndex].toSquare.y = y + dy;
        }
    }
}
//moves should be 290 slots, this function collects all possible moves for a color
int states::moveGen(char color, move *moves){
    int movesIndex = 0;
    //move moves[290];
    square pieces[10];
    //k = number of slots filled in pieces array
    int k = findPieces(color,pieces);
    cout << "171 k " << k << '\n';
    for(int i = 0; i < k; ++i){
    switch(board[pieces[i].x][pieces[i].y]){
	case 'k':
	case 'K':
	    kingMoves(pieces[i].x, pieces[i].y, moves, movesIndex, color );
	    break;
	case 'q':
	case 'Q':
	    queenMoves(pieces[i].x, pieces[i].y, moves, movesIndex, color);
	    break;
	case 'r':
	case 'R':
	    rookMoves(pieces[i].x, pieces[i].y, moves, movesIndex, color);
	    break;
	case 'b':
	case 'B':
	    bishopMoves(pieces[i].x, pieces[i].y, moves, movesIndex, color);
	    break;
	case 'n':
	case 'N':
	    knightMoves(pieces[i].x, pieces[i].y, moves, movesIndex, color);
	    break;
	case 'p':
	    wPawnMoves(pieces[i].x, pieces[i].y, moves, movesIndex);
	case 'P':
	    bPawnMoves(pieces[i].x, pieces[i].y, moves, movesIndex);
	    break;
        default:
	    cout<< "non-valid piece in pieces[i], states.cpp";
    }

    }
    return movesIndex;
}
