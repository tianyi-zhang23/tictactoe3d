//
// Tianyi Zhang 260883657
//
#include <iostream>

using namespace std;
struct rule //data structure that stores a certain rule to check if someone has won
{
    /*someone has won when, for a certain n such that init+n*initInterval < max,
     * init+n*initInterval init+n*initInterval+m*increment has the same value, for m=0,1,2.
     */
    int init;
    int max;
    int initInterval;
    int increment;
};

const rule rules[11] = {{1,25,3,1}, //check each row, on the same table
                         {1,7,3,10}, //check each row, across tables
                         {1,3,1,3}, //check each column, first table
                         {10,12,1,3}, //check each column, second table
                         {19,21,1,3}, //check each column, third table
                        {1,3,1,12}, //check each column, across tables
                         {1,19,9,4}, //check main diagonal, on the same table
                         {3,21,9,2}, //check the other diagonal, on the same table
                         {1,9,1,9}, //check same position across tables
                         {1,1,1,13}, //check main diagonal across table
                         {1,1,3,11}}; //check the other diagonal acorss table
//helper methods for displayBoard
void printBoardLine(char board[],int k) //print a line of the board (across 3 boards)
{
    for(int i=k;i<=k+2;i++)
    {
        if(board[i]=='X'||board[i]=='O')
            cout<<" "<<board[i]<<"  ";
        else {
            cout << " " << i << " ";
            if(i<10)
                cout<<" ";
        }
        if (i!=k+3)
            cout<<"|";
    }
}
void printBorder()
{
    cout<<endl<<"----------------  ----------------  ----------------"<<endl;
}


void displayBoard(char board[])
{
    for(int i=1;i<=7;i+=3) //each line starts with 1, 3, or 7
    {
        for(int j=i;j<=i+18;j+=9)
        {
            printBoardLine(board,j);
            cout<<"   ";
        }
    printBorder();
    }
}
void displayBoard() //overloaded function to print an empty board
{
    char aBoard[28];
    displayBoard(aBoard);
}

void greetAndInstruct()
{
    cout<<"Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer"<<endl<<"The board is numbered from 1 to 27 as per the following:"<<endl;
    displayBoard();
    char inp;
    cout<<"Start?(y/n)"<<endl;
    cin>>inp;
    if(inp=='n')
        exit(0);
    else if (inp!='y')
    {
        cout<<"You did not enter y. The program exits."<<endl;
        exit(0);
    }
}

bool checkIfLegal (int cellNbre, char board[])
{
    if(cellNbre<1 || cellNbre>27) //if out of range
        return false;
    if(board[cellNbre]=='X' ||board[cellNbre]=='O') //if already occupied
        return false;
    return true;
}
bool checkOneType(char board[],char u,rule r)
{
    for(int i=r.init;i<=r.max;i+=r.initInterval)
    {
        if( board[i]==u && board[i]==board[i+r.increment] && board[i+r.increment] == board[i+2*r.increment])
            return true;
    }
    return false;
}

bool checkWinner(char board[],char u)
{
    for(const rule thisRule : rules)
    {
        if (checkOneType(board,u,thisRule))
            return true;
    }
    return false;
}

bool checkWinner(char board[])
{
    if (checkWinner(board,'X')) {
        cout<<"The player has won. The game exits."<<endl;
        return true;
    }
    else if (checkWinner(board,'O'))
    {
        cout<<"The computer has won. The game exits"<<endl;
        return true;
    }
    return false;
}

int checkOneTypeOpponentWillWin(char board[], char u, rule r)
{
    //this function checks if the user is about to win using one rule, and returns the move the computer should make.
    //If the user is not about to win, return -1
    //Assuming that the user has not won.
    for(int i=r.init;i<=r.max;i+=r.initInterval)
    {
        char a = board[i], b = board[i+r.increment], c = board[i+2*r.increment];
        if(a==b && a==u)
        {
            //cout<<"The player has occupied position "<<i<<" position "<<i+r.increment<<endl;
            return i+2*r.increment;
        }
        if(a==c && a==u)
        {
            //cout<<"The player has occupied position "<<i<<" position "<<i+2*r.increment<<endl;
            return i + r.increment;
        }
        if(b==c && b==u)
        {
            //cout<<"The player has occupied position "<<i+r.increment<<" position "<<i+2*r.increment<<endl;
            return i;
        }
    }
    return -1;
}
int userWillWin(char board[])
{
    //return if the opponent will win, by checking against all the rules specified in rules. If none, return -1;
    //assuming that no one has already won. checkWinner() should be called before computerMove() which calls this function.
    for(const rule thisRule: rules)
    {
        int ret = checkOneTypeOpponentWillWin(board,'X',thisRule);
        if( ret !=-1 && board[ret]!='O') //check if the other place has been occupied by computer
            return ret;
    }
    return -1;
}
struct twoNums {int tot; int ind;};
twoNums numOfOccurrence(char chars[],char target, char length)
{
    /*this function is used by checkOneTypePossibleStep(). returns how many occurrences of target in chars
     * and index to an empty space
     */
    int indexToPut;
    int total=0;
    for(int i=0;i<length;i++)
    {
        if(chars[i]==target)
            total++;
        else
            indexToPut=i;
    }
    return {total, indexToPut};
}
struct possibleStepAndPriority  { int place; int priority;}; //priority is the highest at 2, lowest at 0
possibleStepAndPriority checkOneTypePossibleStep(char board[], rule r)
{
    /*check if there is a possible step for the computer according to one rule.
     * if exists permutation of O O _ : return the index of _
     * else if exists permutation of O _ _ : return the index of one of the _s */
    possibleStepAndPriority possiblePlace = {-1,-1};
    for(int i=r.init;i<=r.max;i+=r.initInterval)
    {
        char elements[] = {board[i],board[i+r.increment],board[i+2*r.increment]};
        int indices[] = {i,i+r.increment,i+2*r.increment};
        if(elements[0]!='X' && elements[1]!='X' && elements[2]!='X') //if none of the 3 elements are X, then there has to be an empty space
        {
            //if there are already O O _, then the remaining hole is the place to go
            twoNums totalAndEmpty = numOfOccurrence(elements,'O',3);
            if(totalAndEmpty.tot==2)
                return { indices[totalAndEmpty.ind], 2};
            else if (totalAndEmpty.tot == 1 || possiblePlace.priority<1) //if there is no place with O O _, then try to find O _ _
            {
                possiblePlace.place = indices[totalAndEmpty.ind];
                possiblePlace.priority = totalAndEmpty.tot;
            }
        }

    }
    return possiblePlace; //if no permutations of O O _ have been found, then will return -1. Else will return a place with O _ _ or _ _ _.
}
possibleStepAndPriority checkPossibleSteps(char board[])
{
    possibleStepAndPriority possiblePlace = {-1,-1};
    for(rule r:rules)
    {
        possibleStepAndPriority thisPlace = checkOneTypePossibleStep(board,r);
        if(thisPlace.priority==2)
            return thisPlace;
        else if (thisPlace.priority==1 || (thisPlace.priority>=0 && possiblePlace.priority<0))
            possiblePlace = thisPlace;

    }
    return possiblePlace;
}
void computerMove(char board[])
{
    //this function should only be called after checkWinner() has been called.
    possibleStepAndPriority move = checkPossibleSteps(board);
    if(move.priority==2)
    {
        board[move.place] = 'O'; //if the computer is about to win, then do the winning move
        cout<<"The computer has placed 'O' at "<<move.place<<endl;
    }
    else
    {
        int moveu = userWillWin(board);
        if(moveu!=-1) //if the user is about to win, then do the move to block the user
        {
            board[moveu] = 'O';
            cout<<"The computer has placed 'O' at "<<moveu<<endl;
        }
        else
        {
            board[move.place] = 'O'; //otherwise do any possible move that makes sense
            cout<<"The computer has placed 'O' at "<<move.place<<endl;
        }
    }

    //this game cannot end in a draw so checking a draw is not necessary.
}



