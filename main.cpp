  //Jennifer Solman hw1
  
  #include "classes.h"
  #include <cstdlib>
  #include <time.h>
  void gameOver(char color);
  void createStart(states &state);
  void readBoard();
  void printBoard(states &state);
  void compVsComp(states &state);
  //int negamax(states myState, int depth, int alpha, int beta, int turn, int color);
  int colorMatch(move myMove, char piece, char color);
  int negamax(states &myState, int depth, int alpha, int turn, char color);
  states mainState;
  
  
  int main (){
      createStart(mainState);
      compVsComp(mainState);
      return 0;
  }
  //checks to see if move passed to update board is valid
  bool validMove(move myMove, char piece, char color,states &state){
      int movesIndex = 0;
  //    cout << "creating moves array\n";
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
             (state).kingMoves(myFromX, myFromY, moves, movesIndex, color );
              break;
          case 'q':
          case 'Q':
              (state).queenMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'r':
          case 'R':
             (state).rookMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'b':
          case 'B':
              (state).bishopMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'n':
          case 'N':
              (state).knightMoves(myFromX, myFromY, moves, movesIndex, color);
              break;
          case 'P':
              (state).wPawnMoves(myFromX, myFromY, moves, movesIndex);
          case 'p':
              (state).bPawnMoves(myFromX, myFromY, moves, movesIndex);
              break;
          default:
              cout<< "non-valid piece in pieces[i], states.cpp";
          }
//changed from <= to <
          for(int i = 0; i < movesIndex; ++i){
              if(myFromX == moves[i].fromSquare.x && myFromY == moves[i].fromSquare.y){
                  if(myToX == moves[i].toSquare.x && myToY == moves[i].toSquare.y){
                      return true;
                  }
              }
  //        cout << "i = " << i << '\n';

          }
      }  
       cout << "invalid move \n";
          cout <<" from "  << myMove.fromSquare.x << " " << myMove.fromSquare.y ;
          cout <<" to "  << myMove.toSquare.x << " " << myMove.toSquare.y ;
            
       gameOver('E');
       return false;
  } 

  void gameOver(char color){
      cout << "game over " << color << " wins \n";
      printBoard(mainState);
      exit(0);
  }
  //1 test move, 0 actual move
  void updateBoard(move myMove, char color,bool test, states &state){
      int myFromX = myMove.fromSquare.x;
      int myFromY = myMove.fromSquare.y;
      int myToX = myMove.toSquare.x;
      int myToY = myMove.toSquare.y;
      char piece = 
      (state).board[myFromX][myFromY];
      if(validMove(myMove, piece, color,state)){
          (state).board[myFromX][myFromY] = 'x';

	if(test == 0 &&((state).board[myToX][myToY] == 'k' || (state).board[myToX][myToY] == 'K')){
            
	(state).board[myToX][myToY] = piece;
        printBoard(state);
	    gameOver(color);
        }
	(state).board[myToX][myToY] = piece;
	if(test == 0)
	    ++((state).count);
	if(state.count >= 80){
	    gameOver('D');
	}
    }
    else
	cout << "update board failed \n";
}
void updateUndo(move myMove, char savePiece, states &state){
      int myFromX = myMove.fromSquare.x;
      int myFromY = myMove.fromSquare.y;
      int myToX = myMove.toSquare.x;
      int myToY = myMove.toSquare.y;
      char piece = (state).board[myFromX][myFromY];
     // char to = state.board[myToX][myToY];
//cout << "update undo \n";
//cout << "105 \n "<<"from x " << myFromX << "\n";
//cout << "from y " << myFromY << "\n";
//cout << " to x " << myToX << "\n";
//cout << "to y " << myToY << "\n";
//cout << "piece " << piece << "\n";
      (state).board[myFromX][myFromY] = savePiece;
      (state).board[myToX][myToY] = piece;
//printBoard();
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


void undoMove(move myMove, char savePiece,states &state){
 //   move reverse(myMove.toSquare.x,myMove.toSquare.y,myMove.fromSquare.x,myMove.fromSquare.x);
    move reverse;
    reverse.fromSquare.x = myMove.toSquare.x;
    reverse.fromSquare.y = myMove.toSquare.y;
    reverse.toSquare.x = myMove.fromSquare.x;
    reverse.toSquare.y = myMove.fromSquare.y;
    //1 means test move
    updateUndo(reverse, savePiece,state);   
}

move chooseMove(move *moves, char color, int count, states &state){
    cout << "Choosing move " << color << '\n';
    char opponent;
    int i;
    move myMove = moves[0];
    if(color == 'W')
	opponent = 'B';
    else
	opponent = 'W';

    int bestScore = 10000;
    int bestMove = 0;
    int score;
    for(i = 0; i < count; ++i){
	//1 is for test move
        char savePiece = (state).board[moves[i].toSquare.x][moves[i].toSquare.y];
	updateBoard(moves[i],color,1,state);
	score = (state).eval(opponent);
	if(score < bestScore){
	    bestScore = score;
	    bestMove = i;
	}
	undoMove(moves[i], savePiece,state);
    }
    myMove = moves[bestMove];
cout << "final chose move 179\n";
cout << "from x " << myMove.fromSquare.x << "\n";;
cout << "from y " << myMove.fromSquare.y << "\n";;
cout << "to x " << myMove.toSquare.x << "\n";;
cout << "to y " << myMove.toSquare.y << "\n";;
    return myMove;
}

move chooseMove2(move *moves, char color, int count, states &state){
    cout << "Choosing move via negamax " << color << '\n';
    char opponent;
    int i;
    int turn = 1;
    int depth = 4;
    move myMove = moves[0];
    if(color == 'W')
	opponent = 'B';
    else
	opponent = 'W';

    int bestScore = 10000;
    int bestMove = 0;
    int score;
    for(i = 0; i < count; ++i){
	//1 is for test move
        char savePiece = (state).board[moves[i].toSquare.x][moves[i].toSquare.y];
	updateBoard(moves[i],color,1,state);
       //(state, depth,alpha,turn,color)
	score = negamax(state, depth, bestScore, turn, opponent);
	if(score < bestScore){
	    bestScore = score;
	    bestMove = i;
	}
	undoMove(moves[i], savePiece,state);
    }
    myMove = moves[bestMove];
cout << "final chose move 214\n";
cout << "from x " << myMove.fromSquare.x << "\n";;
cout << "from y " << myMove.fromSquare.y << "\n";;
cout << "to x " << myMove.toSquare.x << "\n";;
cout << "to y " << myMove.toSquare.y << "\n";;
    return myMove;
}

//generates random computer move
void compMove(char color, states &state){
    move moves[290];
    int count = (state).moveGen(color, moves);
    if(count==0)
    {
      cout << "in if 149:no possible moves \n";
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
    move myMove = chooseMove(moves,color,count,state);
    //0 means real move
    updateBoard(myMove, color, 0, state);   
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
    // 0 for real move
    updateBoard(myMove, color, 0, mainState);   
}

void printBoard( states &state){
    int i,j;
    for(i=0; i<=5; ++i){
	for(j=0; j<=4; ++j){
	    cout << (state).board[i][j];
	}
	cout << "\n" ;
    }
    cout << '\n' << '\n';
}

void readBoard(){
    cin >> mainState.count >> mainState.onMove;
    char newState[36];
    cin >> newState;
    int i,j;
    int k=0;
    for(i=0; i<=5; ++i){
	for(j=0; j<=4; ++j){
	    mainState.board[i][j] = newState[k];
	    ++k;
	}
	++k; //skip the newline in input
    }
}

void createStart(states &state){
    int i;
    (state).board[0][0] = 'k';     
    (state).board[0][1] = 'q';     
    (state).board[0][2] = 'b';     
    (state).board[0][3] = 'n';     
    (state).board[0][4] = 'r';     
    (state).board[5][0] = 'R';     
    (state).board[5][1] = 'N';     
    (state).board[5][2] = 'B';     
    (state).board[5][3] = 'Q';     
    (state).board[5][4] = 'K';
    for (i=0; i<=4; ++i){
	    (state).board[1][i] = 'p';
	    (state).board[4][i] = 'P';
	    (state).board[2][i] = 'x';
	    (state).board[3][i] = 'x';
    }     

}

void compVsComp(states &state){
  while(1){
    compMove('W',state);
//    state.eval('W');
    printBoard(state);
    compMove('B',state);
//    state.eval('B');
    printBoard(state);
  }
}

int negamax(states &myState, int depth, int alpha, int turn, char color){
    if((myState).eval(color) > 9000 || (myState).eval(color) < 9000 || depth == 0 || (myState).count >= 80)
	return(turn * (myState).eval(color));
    else{
	move moves[290];
	int numMoves = (myState).moveGen(color,moves);
	for(int i = 0; i < numMoves ; ++i){
            char savePiece = (myState).board[moves[i].toSquare.x][moves[i].toSquare.y];
           //1 means "test" so we don't think we won while searching, etc
	     updateBoard(moves[i],color,1,myState);
	    moves[i].child = myState; 
	    undoMove(moves[i],savePiece,myState);
	    if(color == 'W')
		color = 'B';
	    else if(color == 'B')
		color = 'W';
	    if(alpha < -negamax(moves[i].child, depth-1, -alpha,-turn,color)){
		alpha = -negamax(moves[i].child, depth-1, -alpha,-turn,color);
		break;
	    }
        }
	return alpha;
      }
}



