  //Jennifer Solman hw1
  
  #include "classes.h"
  #include <cstdlib>
  #include <time.h>
  void gameOver(char color);
  void createStart();
  void readBoard();
  void printBoard();
  void compVsComp();
  int colorMatch(move myMove, char piece, char color);
  states state;
  
  int main (){
      createStart();
      compVsComp();
      return 0;
  }
  //next: figure out why we're hitting line 71
  //set up git
  //checks to see if move passed to update board is valid
  bool validMove(move myMove, char piece, char color){
      int movesIndex = 0;
      move moves[30];
      if(colorMatch(myMove,piece,color)){
          int myFromX = myMove.fromSquare.x;
          int myFromY = myMove.fromSquare.y;
          int myToX = myMove.toSquare.x;
          int myToY = myMove.toSquare.y;
          //search the possible moves for a match
          switch(piece){
          case 'k':
          case 'K':
              state.kingMoves(myFromX, myFromY, moves, movesIndex, color );
              break;
          case 'q':
          case 'Q':
              state.queenMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'r':
          case 'R':
             state.rookMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'b':
          case 'B':
              state.bishopMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'n':
          case 'N':
              state.knightMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'p':
              state.wPawnMoves(myFromX, myFromY, moves, movesIndex);
          case 'P':
              state.bPawnMoves(myFromX, myFromY, moves, movesIndex);
              break;
          default:
              cout<< "non-valid piece in pieces[i], states.cpp";
          }
          for(int i = 0; i <= movesIndex; ++i){
              if(myFromX == moves[i].fromSquare.x && myFromY == moves[i].fromSquare.y){
                  if(myToX == moves[i].toSquare.x && myToY == moves[i].toSquare.y){
                      return true;
                  }
              }
          }
      }  
       gameOver(color);
       return false;
  } 
  void gameOver(char color){
      cout << "game over " << color << " wins";
      exit(0);
  }
  
  void updateBoard(move myMove, char color){
      int myFromX = myMove.fromSquare.x;
      int myFromY = myMove.fromSquare.y;
      int myToX = myMove.toSquare.x;
      int myToY = myMove.toSquare.y;
      char piece = state.board[myFromX][myFromY];
      if(validMove(myMove, piece, color)){
          state.board[myFromX][myFromY] = 'x';

	if(state.board[myToX][myToY] == 'k' || state.board[myToX][myToY] == 'K'){
	    gameOver(color);
        }
	state.board[myToX][myToY] = piece;
	++state.count;
	if(state.count >= 80){
	    gameOver('D');
	}
    }
}

int colorMatch(move myMove, char piece, char color){
    if(color == 'W' && (piece < 83 && piece > 65)){
	return true;
    }
    else if(color == 'B'&& (piece < 115 && piece > 97)){
	return true;
    }
    return false;
}


void undoMove(move myMove,char color){
    move reverse;
    reverse.fromSquare.x = myMove.toSquare.x;
    reverse.fromSquare.y = myMove.toSquare.y;
    reverse.toSquare.x = myMove.fromSquare.x;
    reverse.toSquare.y = myMove.fromSquare.y;
    updateBoard(reverse, color);   
}

move chooseMove(move *moves, char onMove, int count){
    char color;
    int i;
    move myMove;
    if(onMove == 'W')
	color = 'B';
    else
	color = 'W';

    int bestScore = 10000;
    int bestMove = 0;
    int score;
    for(i = 0; i < count; ++i){
	updateBoard(moves[i],color);
	score = state.eval(color);
	if(score < bestScore){
	    bestScore = score;
	    bestMove = i;
	}
	undoMove(moves[i],color);
    }
    myMove = moves[i];
    return myMove;
}

//generates random computer move
void compMove(char color){
    cout << "line 108 color: " << color << '\n';
    move moves[290];
    int count = state.moveGen(color, moves);
  //  cout << "111 i " << i << '\n';
    if(count==0)
    {
      cout << "in if 114 \n";
	if(color == 'W')
	       gameOver('B');
	else
	       gameOver('W');
    }
   // time_t seconds;
   // time(&seconds);
   // srand((unsigned int) seconds) ; 
   // int random = rand() % i;
   // move myMove = moves[random];
    move myMove = chooseMove(moves,color,count);
    updateBoard(myMove, color);   
}


//chess coord char to matrix coord
int transChar(char letter){
    switch(letter){
	case 'a':
	    return 0;
	case 'b':
	    return 1;
	case 'c':
	    return 2;
	case 'd':
	    return 3;
	case 'e':
	    return 4;
	default:
	    return -1;
    }
}

//chess coord # to matrix coord
int transNum(char num){
    switch(num){
	case '1':
	    return 5;
	case '2':
	    return 4;
	case '3':
	    return 3;
	case '4':
	    return 2;
	case '5':
	    return 1;
	case '6':
	    return 0;
	default:
	    return -1;
    }
}
//translates chess coords into matrix coords
void translate(char *chess, move &myMove){
	myMove.fromSquare.x = transNum(chess[1]);
	myMove.fromSquare.y = transChar(chess[0]);
	myMove.toSquare.x = transNum(chess[4]);
	myMove.toSquare.y = transChar(chess[3]);
    }

//take human chess coordinates and make move
void humanMove(char color){
    char coord[6];
    cout<< "please enter coorinates in format a1-a2";
    cin >> coord;
    move myMove;
    translate(coord, myMove);
    updateBoard(myMove, color);   
}

void printBoard(){
    int i,j;
    for(i=0; i<=5; ++i){
	for(j=0; j<=4; ++j){
	    cout << state.board[i][j];
	}
	cout << "\n" ;
    }
    cout << '\n' << '\n';
}

void readBoard(){
    cin >> state.count >> state.onMove;
    char newState[36];
    cin >> newState;
    int i,j;
    int k=0;
    for(i=0; i<=5; ++i){
	for(j=0; j<=4; ++j){
	    state.board[i][j] = newState[k];
	    ++k;
	}
	++k; //skip the newline in input
    }
}

void createStart(){
    int i;
    state.board[0][0] = 'k';     
    state.board[0][1] = 'q';     
    state.board[0][2] = 'b';     
    state.board[0][3] = 'n';     
    state.board[0][4] = 'r';     
    state.board[5][0] = 'R';     
    state.board[5][1] = 'N';     
    state.board[5][2] = 'B';     
    state.board[5][3] = 'Q';     
    state.board[5][4] = 'K';
    for (i=0; i<=4; ++i){
	    state.board[1][i] = 'p';
	    state.board[4][i] = 'P';
	    state.board[2][i] = 'x';
	    state.board[3][i] = 'x';
    }     

}

void compVsComp(){
  while(1){
    compMove('W');
    state.eval('W');
    printBoard();
    compMove('B');
    state.eval('B');
    printBoard();
  }
}
