//Jennifer Solman hw1

#include "classes.h"
#define single 1
#define multiple 0
int addPieces(int count,square *pieces);
int eval(char color);
states::states(){
    onMove = 'W';
    count = 0;
}

states::~states(){

}

states& states::operator= (const states &original){
    onMove = original.onMove;
    count = original.count;
    for(int i = 0; i < 6; ++i){
	for(int j = 0; j < 5; ++j){
	    board[i][j] = original.board[i][j];
	}
    }
    return *this;
}

int states::inBounds(int x, int y){
    if(x > -1 && x < 6 && y > -1 && y < 5)
	return 1;
    else
	return 0;
}

//0 if coordinate square is empty 
int states::checkEmpty(int x, int y, char color){
//cout << "\n check empty:\n" << color << '\n' <<" board " <<x <<" "<< y << " " <<  board[x][y] << '\n';

    if(board[x][y] == 120){
//        cout << "returning 0 for empty";
	return 0; //empty
    }

    else if(color == 'W'){
	if(board[x][y] > 97 && board[x][y] < 115){
  //          cout << "returning 1 for opp";
	    return 1;  //opponent
        }
	else{ 
    //        cout << "returning 2 for self";
	    return 2; //self
         }

   }
    else if(color == 'B'){
	if(board[x][y] < 83 && board[x][y] > 65){
  //          cout << "returning 1 for opp";
	    return 1;
        }
	else{ 
    //        cout << "returning 2 for self";
	    return 2;
        }
    }
    else{ 
        cout << "line 39 states very bad";
	return 3; //error (very bad)
    }
}
/*pass this an empty square array and a color, and it will fill 
 the array with squares containing that color piece*/
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
   // cout<< color <<" k: " << k << '\n';
    return k;
}

/*pass this the color of the piece on-move
  returns score for that color*/
int states::eval(char color){
    square piecesB[10];
    square piecesW[10];
    int countB = findPieces('B',piecesB);
    int countW = findPieces('W',piecesW);
    int totalB, totalW;
    totalB = addPieces(countB,piecesB);
    totalW = addPieces(countW,piecesW);
    int score;
    if(color == 'W')
	 score = totalW - totalB;
    else
	 score = totalB - totalW;
//	cout<< "score " << score << '\n';
    return score; 
}

int states::addPieces(int count,square *pieces){
    int score = 0;
//changed from <=...
    for(int i = 0; i < count; ++i){
		switch(board[pieces[i].x][pieces[i].y]){
			case 'k':
			case 'K':
				score += 10000;
				break;
			case 'q':
			case 'Q':
				score += 900;
				break;
			case 'r':
			case 'R':
				score += 500;
				break;
			case 'b':
			case 'B':
				score += 300;
				break;
			case 'n':
			case 'N':
				score += 200;
				break;
			case 'p':
			case 'P':
				score += 100;
				break;
			default:
				cout<< "120 non-valid piece in pieces[i], states.cpp \n";
		}
	}
	return score;
}
	
void states::scan(int x, int y, move *moves, int &movesIndex, int dx, int dy, int movement, char color){
    int toX = x;
    int toY = y;
    while(inBounds(toX + dx, toY + dy)){
         //if square is empty 0 or contains opponent 1
        int CE = checkEmpty(toX + dx, toY + dy,color); 
	if(CE == 0 || CE == 1 ){
	    moves[movesIndex].fromSquare.x = x; // new move(x, y, toX + dx, toY + dy);
	    moves[movesIndex].fromSquare.y = y; 
	    moves[movesIndex].toSquare.x = toX + dx; 
	    moves[movesIndex].toSquare.y = toY + dy;
	    if(CE == 1 || movement == single){
//cout<< "\nsingle or opponent break\n" ;
		++movesIndex;
		break;
            }
	    else{ 
//cout<< "\nsearch farther\n" ;
	        toX = toX + dx;
                toY = toY + dy;
		++movesIndex;
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

    if(inBounds(x-1, y) && checkEmpty(x-1, y,color) == 0)
       scan(x, y, moves, movesIndex, -1, 0, single, color); //north
    if(inBounds(x+1, y) && checkEmpty(x+1, y, color) == 0)
        scan(x, y, moves, movesIndex, 1, 0, single, color); //south

    if(inBounds(x, y+1) && checkEmpty(x, y+1, color) == 0)
        scan(x, y, moves, movesIndex, 0, 1, single, color); //east
    if(inBounds(x, y-1) && checkEmpty(x, y-1, color) == 0)
        scan(x, y, moves, movesIndex, 0, -1, single, color); //west
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
//WHAT THE HELL??
void states::wPawnMoves(int x, int y, move *moves, int &movesIndex){
    if(inBounds(x-1, y) && checkEmpty(x-1, y,'W') == 0){
       scan(x, y, moves, movesIndex, -1, 0, single, 'W'); //north
    }
    //check for diagonal attack NW NE
    pawnAttacks(x, y, moves, movesIndex, -1, -1, 'W');
    pawnAttacks(x, y, moves, movesIndex, -1, 1, 'W');
}

void states::bPawnMoves(int x, int y, move *moves, int &movesIndex){
    if(inBounds(x+1, y) && checkEmpty(x+1, y,'B') == 0){
        scan(x, y, moves, movesIndex, 1, 0, single, 'B'); //south
    }
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
            ++movesIndex;
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
	case 'P':
	    wPawnMoves(pieces[i].x, pieces[i].y, moves, movesIndex);
	    break;
	case 'p':
	    bPawnMoves(pieces[i].x, pieces[i].y, moves, movesIndex);
	    break;
        default:
	    cout<< "259 non-valid piece in pieces[i], states.cpp";
    }

    }
    return movesIndex;
}

