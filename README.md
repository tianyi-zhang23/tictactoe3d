# tictactoe3d
A 3D tic-tac-toe game in command line written in C++
### Rules of the Game
The rule of the game is identical to that of a regular tic-tac-toe, other than the fact that now the board is 3d. This means that a party wins when it 
- (1) Has three dots along one line (including diagonal) in one of the three boards or across the three boards
- (2) Has three dots at the same position in all of three boards
The player always starts first. The reason is that there is always a way for the first player to win in 3D tic-tac-toe; thus the computer would always win if it played first.

### How to Run
If you are using Linux on an Intel x64 machine, simply download, chmod +x, and run the executable file `tictactoe3d`. This executable has been compiled in Ubuntu 19.04 on an Intel x64 machine with G++. To run on other platforms, simply compile `main.cpp` and `functions.cpp` with a C++ compiler.
 ```
 g++ main.cpp functions.cpp -o tictactoe3d
 ```

Done as part of COMP322 at McGill University
