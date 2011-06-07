  //Jennifer Solman hw1
  #include "classes.h"
  #include <cstdlib>
  #include <time.h>
  #include <algorithm>
  #include <fstream>
  using namespace std;
   int queenv = 900;
   int knightv = 200;
   int bishv = 300;
   int rookv = 500;
   int py0v = 0;
   int py1v = 0;
   int py2v = 0;
   int py3v = 0;
   int py4v = 0;
   int seconds = 1;
  bool endGame;
  void gameOver(char color);
  void createStart(states &state);
  void readBoard();
  void printBoard(states &state);
  void compVsComp(states &state);
  int colorMatch(move &myMove, char piece, char color);
  int negamax(states &myState, int depth, int alpha, int beta, char color,int time);
  int transToChessNum(int num);
  void transToChess(char *moveCode, move &myMove);
  char transToChar(int num);
  void networkPlay(char myColor,states &mainState);
  char run();
  void setPieceValues(int pieceValues[9]);
  void setToStandard();
  states mainState;
  //set this to false during a real game
  bool debug = false;  
  bool liveGame;
  char winner;
 /////////////////////////////////////////////////TEST!
  int numRuns = 2;
  
  int main (int argc, const char** argv){
    fstream myfile;
    int pieceVals[9];
    myfile.open ("chessData.txt");
    myfile << " 0 queen, 1 knight, 2 bish, 3 rook, 4 py0, 5 py1, 6 py2, 7 py3, 8 py4 \n"; 
    myfile.close();
    int bestValue;
    int testValue;
    int bestW;
    int tempW;
    int origW = 0;
  
  for(int j = 0; j < numRuns; ++j){ 
        char result = run();
	if(result == 'W')
	    ++origW;	   
    }   
  myfile.open ("chessData.txt", ios::app);
  myfile << " \n white normally wins " << origW << " of " << numRuns; 
  myfile.close();
    
     //for each piece
//////////////////////////////////////////////TEST!
     for(int i = 0; i < 2; ++i){
	setToStandard();
	setPieceValues(pieceVals);
	bestValue = pieceVals[i];
	testValue = -200;
	bestW = origW;
        tempW = 0;
        //play numRuns games and see if we win more for each test value
	while(testValue <= 900){
cout << "\n test value " << testValue << "\n";
	    time_t sec;
	    time(&sec);
	    srand((unsigned int)sec);
	    //seconds = (rand() % 7) + 1;
	    pieceVals[i] = testValue;
            mainState.setPieceValues(pieceVals);
            for(int j = 0; j < numRuns; ++j){ 
        	char result = run();
		if(result == 'W')
	           ++tempW;	   
            }
 	myfile.open ("chessData.txt", ios::app);
	myfile << "\n piece number " << i << " test value: " << testValue << "\n won: " << tempW << " of " << numRuns;
        myfile.close();
            if(tempW > bestW){
		bestW = tempW;
		bestValue = testValue;
	    }   
	    testValue += 100;
	}
        //set value of that piece to best value
 	myfile.open ("chessData.txt", ios::app);
	myfile << "\n piece number " << i << " best value: " << bestValue << "\n won: " << bestW << " of " << numRuns;
        myfile.close();
     }

    return 0;
}

char run(){
      endGame = false;
      createStart(mainState);
      compVsComp(mainState);
      return winner;
}

//resets pieces before next evaluation run
void setToStandard(){
    queenv = 900;
    knightv = 200;
    bishv = 300;
    rookv = 500;
    py0v = 0;
    py1v = 0;
    py2v = 0;
    py3v = 0;
    py4v = 0;
}


  void setPieceValues(int pieceValues[9]){
    pieceValues[0] = queenv;
    pieceValues[1] = knightv;
    pieceValues[2]= bishv;
    pieceValues[3] = rookv;
    pieceValues[4] = py0v;
    pieceValues[5] = py1v;
    pieceValues[6] = py2v;
    pieceValues[7] = py3v;
    pieceValues[8] = py4v;
  }

  //checks to see if move passed to update board is valid
  bool validMove(move &myMove, char piece, char color,states &state){
      //if we're playing a real game, don't validate
      if (debug == false)
	return true;
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
	      break;
          case 'p':
              (state).bPawnMoves(myFromX, myFromY, moves, movesIndex);
              break;
          default:
              cout<< "non-valid piece in pieces[i], states.cpp";
          }
          for(int i = 0; i < movesIndex; ++i){
              if(myFromX == moves[i].fromSquare.x && myFromY == moves[i].fromSquare.y){
                  if(myToX == moves[i].toSquare.x && myToY == moves[i].toSquare.y){
                      return true;
                  }
              }
          }
      }  
       cout << "invalid move \n";
          cout <<" from "  << myMove.fromSquare.x << " " << myMove.fromSquare.y ;
          cout <<" to "  << myMove.toSquare.x << " " << myMove.toSquare.y << '\n';
            
       gameOver('E');
       return false;
  } 

  void gameOver(char color){
      endGame = true;
      printBoard(mainState);
      winner = color;
      if(color == 'D')
	cout << "  = Draw";
      else if(color == 'E')
	cout << "  = Game over. Ended due to Error";
      else
        cout <<  color << " =  wins \n";
      return;
  }

  //1 test move, 0 actual move
  void updateBoard(move &myMove, char color,bool test, states &state){
      int myFromX = myMove.fromSquare.x;
      int myFromY = myMove.fromSquare.y;
      int myToX = myMove.toSquare.x;
      int myToY = myMove.toSquare.y;
      char piece = (state).board[myFromX][myFromY];
      if(validMove(myMove, piece, color,state)){
        (state).board[myFromX][myFromY] = 'x';
	if(test == 0 &&((state).board[myToX][myToY] == 'k' || (state).board[myToX][myToY] == 'K')){   
            (state).board[myToX][myToY] = piece;
            printBoard(state);
	    gameOver(color);
            return;
        }
        //if test == zero and pawn reaches other side, promote to queen
	if(color == 'W' && test == 0 && piece == 'P' && myToX == 0 ){
	    piece = 'Q';
	}
	if(color == 'B' && test == 0 && piece == 'p' && myToX == 5 ){
	    piece = 'q';
	}
	(state).board[myToX][myToY] = piece;
	if(test == 0)
	    ++((state).count);
	if(state.count >= 80 && test == 0){
	    gameOver('D');
            state.count = 0;
            return;
	}
    }
    else
	cout << "update board failed \n";
}

void updateUndo(move &myMove, char savePiece, states &state){
      int myFromX = myMove.fromSquare.x;
      int myFromY = myMove.fromSquare.y;
      int myToX = myMove.toSquare.x;
      int myToY = myMove.toSquare.y;
      char piece = (state).board[myFromX][myFromY];
      (state).board[myFromX][myFromY] = savePiece;
      (state).board[myToX][myToY] = piece;
}

int colorMatch(move &myMove, char piece, char color){
    if(color == 'W' && (piece < 83 && piece > 65)){
	return true;
    }
    else if(color == 'B'&& (piece < 115 && piece > 97)){
	return true;
    }
    return false;
}


void undoMove(move &myMove, char savePiece,states &state){
    move reverse;
    reverse.fromSquare.x = myMove.toSquare.x;
    reverse.fromSquare.y = myMove.toSquare.y;
    reverse.toSquare.x = myMove.fromSquare.x;
    reverse.toSquare.y = myMove.fromSquare.y;
    updateUndo(reverse, savePiece,state);   
}
 
int pieceValue(char piece){
	int value;
	switch(piece){
		case 'k':
		case 'K':
			value = 10000;
			break;
		case 'q':
		case 'Q':
			value = 900;
			break;
		case 'r':
		case 'R':
			value = 500;
			break;
		case 'b':
		case 'B':
			value = 300;
			break;
		case 'n':
		case 'N':
			value = 200;
			break;
		case 'p':
		case 'P':
			//this is now average-ish but it's just for the sort, so it's ok
			value = 300;
			break;
	        default:
		    cout << "pieceValue was given an invalid piece \n";
         }
	return value;
}

//code stolen from www.fredosaurus.com/notes-cpp/misc/random-shuffle.htm
void shuffle(move *moves, int count){
     for (int i = 0; i < count; i++) {
            int r = rand() % count;  // generate a random position
            move temp = moves[i]; moves[i] = moves[r]; moves[r] = temp;
        }
}
//sorts moves in ascending order for value of color passed in (value)
void sortMoves(move *moves, int count, states &state, int value){
    for(int i = 0; i < count; ++i){
        char savePiece = (state).board[moves[i].toSquare.x][moves[i].toSquare.y];
	if(savePiece == 'x')
            moves[i].value = value;
	else 
	    moves[i].value = value + pieceValue(savePiece);
    }
    //sort moves from zero to count-1
    sort(moves, moves+count);
}

move chooseMove2(move *moves, char color, int count, states &state){
    char opponent;
    int i;
    int depth = 1;
    int test = 1;
    int alpha = -13000;
    int beta = 13000;
    int value = state.eval(color);
    shuffle(moves,count);
    sortMoves(moves, count, state, value);
    int time = clock() + seconds*CLOCKS_PER_SEC;
    cout << "Choosing move via negamax " << color << '\n';
    move myMove = moves[0];
    if(color == 'W')
	opponent = 'B';
    else
	opponent = 'W';

    int bestScore = -5000;
    int bestMove = 0;
    int score;
  while(clock() < time){
    if(count == 0 || endGame)
	break;
    for(i = 0; i < count; ++i){
        if(endGame)
	   break;
        char savePiece = (state).board[moves[i].toSquare.x][moves[i].toSquare.y];
	updateBoard(moves[i],color,test,state);
	score = -negamax(state, depth, alpha, beta, opponent,time);
	if(score > bestScore){
	    bestScore = score;
	    bestMove = i;
	}
	undoMove(moves[i], savePiece,state);
   }
    cout<< " finished depth " << depth << '\n';
    ++depth;
 }

    myMove = moves[bestMove];
//cout << "final chose move 214\n";
//cout << "from x " << myMove.fromSquare.x << "\n";;
//cout << "from y " << myMove.fromSquare.y << "\n";;
//cout << "to x " << myMove.toSquare.x << "\n";;
//cout << "to y " << myMove.toSquare.y << "\n";;
cout << opponent << " " ;
cout << (state).board[myMove.toSquare.x][myMove.toSquare.y] << " captured \n";
    return myMove;
}

//generates random computer move
void compMove(char color, states &state){
    move moves[290];
    int count = (state).moveGen(color, moves);
    if(count==0){
      cout << "in if 320:no possible moves \n";
	if(color == 'W')
	       gameOver('B');
	else
	       gameOver('W');
      return;
    }
   if(endGame)
        return;
    move myMove = chooseMove2(moves,color,count,state);
    //0 means real move
    updateBoard(myMove, color, 0, state);   
    if(liveGame){
	char moveCode[6];
	transToChess(moveCode,myMove);
	cout << moveCode;
    }
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
	myMove.fromSquare.x = transNum(chess[2]);
	myMove.fromSquare.y = transChar(chess[1]);
	myMove.toSquare.x = transNum(chess[5]);
	myMove.toSquare.y = transChar(chess[4]);
}

//translates matrix coord into chess coords
void transToChess(char *moveCode, move &myMove){
	moveCode[0] = '!';
	moveCode[3] = '-';
	moveCode[2] = transToChessNum(myMove.fromSquare.x);
	moveCode[1] = transToChar(myMove.fromSquare.y);
	moveCode[5] = transToChessNum(myMove.toSquare.x);
	moveCode[4] = transToChar(myMove.toSquare.y);
}


//matrix coord to chess char
char transToChar(int num){
    switch(num){
	case '0':
	    return 'a';
	case '1':
	    return 'b';
	case '2':
	    return 'c';
	case '3':
	    return 'd';
	case '4':
	    return 'e';
	default:
	    return -1;
    }
}

//matrix coord to chess coord # 
int transToChessNum(int num){
    switch(num){
	case '5':
	    return 1;
	case '4':
	    return 2;
	case '3':
	    return 3;
	case '2':
	    return 4;
	case '1':
	    return 5;
	case '0':
	    return 6;
	default:
	    return -1;
    }
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
    liveGame = false;
  while(!endGame){
    compMove('W',state);
//    state.eval('W');
    printBoard(state);
    compMove('B',state);
//    state.eval('B');
    printBoard(state);
  }
}

int negamax(states &myState, int depth, int alpha, int beta, char color, int time){
    char opposite;
   // int max = -5000;
    int value = myState.eval(color);
    if(value > 5000 || value < -5000 || depth == 0 || (myState).count >= 80)
	return(value);
    else{
	move moves[290];
	int numMoves = myState.moveGen(color,moves);
	if(color == 'W')
	    opposite = 'B';
	else if(color == 'B')
	    opposite = 'W';
	//HERE: shuffle then sort first numMoves-1 indexes of moves
    	shuffle(moves,numMoves);
    	sortMoves(moves, numMoves, myState, value);
	//the for loop is the breadth part, negamax is the depth
	for(int i = 0; i < numMoves ; ++i){
          if(clock() < time){
            char savePiece = myState.board[moves[i].toSquare.x][moves[i].toSquare.y];
           //1 means "test" so we don't think we won while searching, etc
	     updateBoard(moves[i],color,1,myState);
	     int temp = -negamax(myState, depth-1, -beta, -alpha, opposite, time);
	    if(alpha < temp){
	   	alpha = temp;
	    }
	    undoMove(moves[i],savePiece,myState);
	    if(alpha >= beta)
		return alpha;
          }
         //if we're out of time, set return value to rediculusly bad so we reject it
         else{
	    return 50000;
	 }
        }
	return alpha;
      }
}



