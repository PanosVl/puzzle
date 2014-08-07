/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");//the user enters the tile with number X 
        int tile = GetInt();
        
        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // TODO
    int odd = 0; //indicates d is NOT odd
    if( d%2 == 0 )
        odd = 0;
    else
        odd = 1; //d is odd      
    int fill = d*d-1;//value that fills the board
    for( int i = 0; i<d; i++ )
    {
       for( int j = 0; j<d; j++ )
       {
          board[i][j] = fill;
          fill --;
          //filling the last pieces depending on odd numbers
          if( (i == d-1) && (j == d-3) && (odd == 0) )
          {
             board[d-1][d-3] = 1;
             board[d-1][d-2] = 2;
             board[d-1][d-1] = 0;
             break;
          }
          else if((i == d-1) && (j == d-3) && (odd == 1))
          {  board[d-1][d-3] = 2;
             board[d-1][d-2] = 1;
             board[d-1][d-1] = 0;
             break;
          }
          //end of filling the lasts
       }
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for( int i = 0; i < d; i++ )
    {
       for( int j = 0; j < d; j++ )
       {
          printf("   ");//three spaces before each column
          if( board[i][j] == 0 )
          {
             printf(" _");
          }
          else
          {
              printf("%2d", board[i][j]); 
          }
       }
       printf("\n");//new-line after each row
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    int row, column;
    bool found = false;//tile NOT found
    //search to find the blank tile's position
    for( int i = 0; i < d && !found; i++ )
    {
       for( int j = 0; j < d; j++ )
       {
           if( board[i][j] == tile )
           {
               row = i;
               column = j;
               found = true;
               break;
           }
       }
   }
   //making the move
    // up
    if( row > 0 )
   {
       if( board[row - 1][column] == 0 )
       {
            board[row - 1][column] = tile;
            board[row][column] = 0;
            return true;
       }
   }

   // right
   if( column < d - 1 )
   {
        if( board[row][column + 1] == 0 )
       {
           board[row][column + 1] = tile;
           board[row][column] = 0;
           return true;   
       }    
    }

    // bottom
    if( row < d - 1 )
    {
       if( board[row + 1][column] == 0)
       {
           board[row + 1][column] = tile;
           board[row][column] = 0;
           return true;
       }
    }

    // left
    if( column > 0 )
    {
        if( board[row][column - 1] == 0)
        {
           board[row][column - 1] = tile;
           board[row][column] = 0;
           return true;
        }
    }
    return false;
   
    
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    //iterrate through the array and check the values
    int c = 0;//counter
    int flag = 0;
    bool error = false;//no error, everything looks good.
    for( int i = 0; i < d; i++ )
    {
       for( int j = 0; j < d; j++ )
       {
          c++;
          if( (i == (d-1)) && (j == (d-1)) )
          {
              if( board[i][j] == 0 )
              {
                  return true;
              }
          } 
          if( board[i][j] == c )
          {
             flag = 1;//true
             error = false;
          }
          else
          {
             flag = 0;//false
             error = true;
             break;
          }
       }
    }
    if( error == false )
       return true;
    else
       return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
