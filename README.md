# miniChess

This miniChess bot was created for an AI course I took a Portland State back in 2011. Below is the write up for the features in the project. When I last downloaded the code, I had to add some curly braces to my case statements to get it to compile in my current environment.

Final Project Write Up

	This  write up is designed for easy grading of the project. Starting with lesson 6 on the tutorial it tells you where to find the code and gives a basic description of my implementation (everything before lesson 6 is basic to getting started.):

6) Build a mini chess state evaluator:
	states.cpp line 94. I create an array of 10 for white and black to hold all possible pieces on the board. findPieces(color, square *) fills this array and returns an int stating how may pieces it placed in the array. addPieces(int, square *) adds up the values of each of the pieces. One score is subtracted from the other. The result is returned. 

7) Depth Limited Negamax
main.cpp lines 514-550

8)Do Iterative Deepening Timed Search:
    main.cpp lines 281-293 and 532. In chooseMove2, while we have time, we keep running the search and increasing the depth. In negamax itself, each time we make a new recursive call to negamax, we first check to see if we have time.

9) Build a MiniChess Player
        main.cpp lines 503-512 allow me to play against myself. All seems well.

10) Alpha-Beta Pruning
         lines 536-543 of main.cpp

11) Order Moves for Alpha-Beta
        main.cpp lines 240-257. At 267, chooseMove2 calls these to shuffle and sort in ascending order for the color passed in. This is because negamax then gets called for opponent.

12) Do/ Un-do
         Negamax calls at line 540 of main.cpp. Implementation line 161-168 and 140-148. undoMove(move &myMove, char savePiece, states &state) creates a move that is the reverse of the move passed to it. It passes this move to updateUndo, which executes the move including replacing a captured piece.

13) Some Improvements:  
	states.cpp lines 136-161: pawns are now encouraged to advance aggressively and prevent the opponent from doing so, by adding value to the pawns as they approach promotion.

Network Play:
      main.cpp lines 480-501. Also code to translate back and forth between chess notation and the matrix notation my code used is found on lines 329-421.

Git Repository: https://github.com/8675309/miniChess

Grad Student Portion:
Learned Evaluator:
     The learned evaluator was made by copying my chess game and making a new file. I then altered the file so that I could run all of the learning commands from main. When learning, black uses the evaluation method from my old chess game and white makes changes, comparing its results against black. Each piece has an associated index in an int array. This also includes each pawn by y position. One at a time each array index runs through values -100 (on the off chance that a piece is actually in our way) to 900. The piece value is incremented by 100 each run. The initial values for the pieces are simply guesses. Each time a set of 10 games is played, the number of games one by white is compared to the current best number of wins. If it is highest, the "bestValue"  for that piece is stored. To prevent the same game from being played out repeatedly, the first 3 moves of each player is generated randomly. The code can be reviewed in the "learnAI" file.

    While test conditions were not ideal (self play, small number of games), the evaluator still yielded some interesting results:
    queen = 900
    knight = 600
    bishop = 100 (hmm...maybe I forgot the code to change square colors)
    rook = 900
    Pawns:
    These turned out to have VERY high values. I did not expect interesting results here because my baseline evaluator already incorporates high pawn values (200) with rapid increases for advancing. One move forward and a pawn is worth 400. Next square 500. Next 600 and then promotion to queen. In my learned evaluator, I added points for each pawns Y value on the board. While I did not collect enough data to conclude that one pawn is worth more than another, each pawn did want additional points added to it.
   from left to right facing player:
    pawn1: add  300 (so this starts it at a total of 500 and it is up to 1100 before it gets promoted. Oops. That's more than a queen. It won't want to promote. Interesting.)
    pawn2: add 800 (starts off at total of 1000)
    pawn3: add 400 (starts off at total of 600)
    pawn4: add 100 (total 300)
    pawn5: add 900 (total 1100)

INTERESTING TEST RESULTS:
What I find interesting about the pawn results, is that I accidentally allowed the ending value of the pawns right before promotion to consistently be worth more than a queen for higher starting pawn values. This means that none of my pawns got promoted during play on the pawn values resulting in wins (unless they were capturing, or going to be captured). This means that even without pawn promotion, very high pawn values are preferred, even MORE than the option of having promotion available and sought after. This distinction is something I would not have thought to test for, so I am glad that I made this oversight in not encouraging pawn promotion at the end.

It is also interesting that the rook is worth almost as much as the queen, and the bishop is not worth much. This tells us that diagonal movement is not very helpful. Of course I would like to do better tests with more games played. The differences were slight. Almost all matches tied all games. The winning values generally only won one game. 

I then ran a test comparing the baseline against a game where all white pieces were set to calculated optimal values:
Before:
White: wins 0, loses 1, draws 9
After:
White: wins 2, loses 1,draws 7




