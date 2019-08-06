#include <iostream>
#include <conio.h> 
#include<windows.h>

using namespace std;

bool gameOver;
const int height = 25;
const int width = 50;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void play ( );

void setup ( )
{
    nTail = 0;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand ( ) % width;
    fruitY = rand ( ) % height;
    score = 0;
}


void isGameOver ( )
{
    system ("cls");
    char answer;
    cout << "#_#_#_#_#_#_#_#_#_#__#_#_#" << endl;
    cout << "\tGame Over" << endl;
    cout << "#_#_#_#_#_#_#_#_#_#__#_#_#" << endl;

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "Your score is: " << score << nTail << endl ;
    cout << "\nRestart game(y/n)?";
    cin >> answer;
    if ( answer == 'n' || answer == 'N' )
    {
        gameOver = true;
    }
    else
    {
        gameOver = false;
        play ( );
    }
}

void draw ( )
{
    // Use double quotes, shows error for single quotes;
    // clear the screen so that the game stays in one place
    system ("cls");
    for ( int i = 0; i < width + 1; i++ )
    {
        cout << "#";
    }
    cout << endl;
    for ( int i = 0; i < height; i++ )
    {
        for ( int j = 0; j < width; j++ )
        {
            if ( j == 0 )
                cout << "#";
            else if ( i == y && j == x )
                cout << "O";
            else if ( i == fruitY && j == fruitX )
                cout << "F";
            else
            {
                bool print = false;
                for ( int k = 0; k < nTail; k++ )
                {
                    if ( tailX[k] == j && tailY[k] == i )
                    {
                        print = true;
                        cout << "o";
                    }
                }
                if ( !print )
                    cout << " ";
            }
            if ( j == ( width - 1 ) )
                cout << "#";
        
                
        }
        cout << endl;
    }
    for ( int i = 0; i < width + 1; i++ )
    {
            cout << "#";
    }
    cout << endl;
    cout << "\nScore:" << score;
}
// w - up
//a - left
// d - right
// s - down


void input ( )
{
    if ( _kbhit() )
    {
        switch ( _getch() )
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            break;
        }
    }
}

void logic ( ){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for ( int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch ( dir )
    {
    case UP:
        y--;
        break;

    case LEFT:
        x--;
        break;

    case DOWN:
        y++; // top is 0, so y++ goes down
        break;

    case RIGHT:
        x++;
        break;
    default:
        break;

    }
    if ( x >= width || x <= 0 || y >= height || y <= 0 )
        isGameOver ();
    if ( x == fruitX && y == fruitY )
    {
        score += 10;
        nTail++;
        fruitX = rand ( ) % width;
        fruitY = rand ( ) % height;
    }
}
void play ( )
{
    setup ( );
    while ( !gameOver )
    {
        draw ( );
        input ( );
        logic ( );
    }
}

int main ()
{
    char answer;
    cout << "Want to start the game(y/n)?";
    cin >> answer;
    if ( answer == 'y' || answer == 'Y' )
        gameOver = false;
    else
        gameOver = true;
    play ( );
    
    return 0;
}