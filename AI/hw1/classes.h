//hw1 Jennifer Solman
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;


class square{
    public:
	square();
        square(int q,int r);
        ~square();
        int x; // 0 to 5
        int y; // 0 to 4
};

class move{
    public:
	    move();
            move(int x,int y,int z, int w);
            ~move();
	    square toSquare;
	    square fromSquare;

};

class states{
    public:
	states();
        ~states();
        int moveGen(char color, move *moves);
        int inBounds(int x, int y);
	int checkEmpty(int x, int y, char color);
	int findPieces(char color, square *pieces);
	void scan(int x, int y, move *moves, int &movesIndex, int dx, int dy, int single, char color);
	void checkNSEW(int x, int y, move *moves, int &movesIndex, int single, char color);
	void checkDiag(int x, int y, move *moves, int &movesIndex, int single, char color);
	void queenMoves(int x, int y, move *moves, int &movesIndex, char color);
	void kingMoves(int x, int y, move *moves, int &movesIndex, char color);
	void bishopMoves(int x, int y, move *moves, int &movesIndex, char color);
	void rookMoves(int x, int y, move *moves, int &movesIndex, char color);
	void knightMoves(int x, int y, move *moves, int &movesIndex, char color);
	void wPawnMoves(int x, int y, move *moves, int &movesIndex);
	void bPawnMoves(int x, int y, move *moves, int &movesIndex);
	void pawnAttacks(int x, int y, move *moves, int &movesIndex, int dx, int dy, char color);
        char board[6][5];
        char onMove;
        int count;
};

