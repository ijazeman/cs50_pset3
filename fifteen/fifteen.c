/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
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
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
     int a = (d*d)-1;
    int i,j;
 
    // TODO
    for( i=0; i< d; i++)
    {
      for( j=0; j<d; j++)
      {  board[i][j] = a;
         a--;
      }
     
        
    }
     if(d % 2 == 0 )             // even dimensions  // swapping last two numbered tiles
     {
         int temp = board[d-1][d-2];     
         board[d-1][d-2] = board[d-1][d-3];
         board[d-1][d-3] = temp;
     }
    board[d-1][d-1] = 0;           // just placing a negative at empty space
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //  printf("\033[%d;%dH", 3, 6);
    printf("\033[3B");
     printf("\033[01;31m");
    for(int i=0; i<d ;i++)
    {
      for(int j=0 ;j<d; j++)
      {
          
          if(board[i][j]!= 0)           // take care to not print empty space 
            printf("%i", board[i][j]);
          else
             printf(" ");
          if(j<d-1)
          {
              int a = board[i][j], space = 0;
              a = a/10;
              if(a ==0)
                space  =1;
              for(int k=1; k<(3+space); k++)
                   printf(" ");
          }
         
         
      }
      for(int l=0;l<3;l++)
           printf("\n");
    
     
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
     for(int i=0;i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            if(board[i][j] == 0)         // if empty tile spotted 
            {
                if( i == 0)           // if empty tile is in 1st row
                {
                    if(j == 0)           // for 1st column
                    {
                        if(board[i][j+1] == tile )
                        {
                            int temp = board[i][j+1];              // moving tiles
                            board[i][j+1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        }
                        else if(board[i+1][j] == tile )
                        {
                            int temp = board[i+1][j];
                            board[i+1][j] = board[i][j];
                            board[i][j] = temp;  
                            return true;
                        }
                        return false;
                    }
                    else if( j == (d-1))           // last column
                    {
                         if(board[i][j-1] == tile )
                        {
                            int temp = board[i][j-1];              // moving tiles
                            board[i][j-1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        }
                        else if(board[i+1][j] == tile )
                        {
                            int temp = board[i+1][j];
                            board[i+1][j] = board[i][j];
                            board[i][j] = temp;  
                            return true;
                        }
                        return false;

                    }
                    else if(board[i][j+1] == tile)
                    {
                            int temp = board[i][j+1];              // moving tiles
                            board[i][j+1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                    }
                    else if(board[i][j-1] == tile)
                    {
                           int temp = board[i][j-1];              // moving tiles
                            board[i][j-1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        
                    }
                    else if(board[i+1][j] == tile )
                    {
                            int temp = board[i+1][j];
                            board[i+1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                    }
                    return false;
                }
                else if(i == (d-1)) // if empty tile is in last row
                {
                    if(j == 0)           // for 1st column
                    {
                        if(board[i][j+1] == tile )
                        {
                            int temp = board[i][j+1];              // moving tiles
                            board[i][j+1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        }
                        else if(board[i-1][j] == tile )
                        {
                            int temp = board[i-1][j];
                            board[i-1][j] = board[i][j];
                            board[i][j] = temp;  
                            return true;
                        }
                        return false;
                    }
                    else if( j == (d-1))           // last column
                    {
                        if(board[i][j-1] == tile )
                        {
                            int temp = board[i][j-1];              // moving tiles
                            board[i][j-1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        }
                        else if(board[i-1][j] == tile )
                        {
                            int temp = board[i-1][j];
                            board[i-1][j] = board[i][j];
                            board[i][j] = temp;  
                            return true;
                        }
                        return false;
                    }
                    else if(board[i][j+1] == tile)
                    {
                            int temp = board[i][j+1];              // moving tiles
                            board[i][j+1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                    }
                    else if(board[i][j-1] == tile)
                    {
                           int temp = board[i][j-1];              // moving tiles
                            board[i][j-1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        
                    }
                    else if(board[i-1][j] == tile )
                    {
                            int temp = board[i-1][j];
                            board[i-1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                    }
                    return false;
                    
                }
                else if(j == 0)
                {
                    if(board[i-1][j] == tile )
                    {
                            int temp = board[i-1][j];
                            board[i-1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                    }
                    else if(board[i+1][j] == tile )
                    {
                            int temp = board[i+1][j];
                            board[i+1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                    }
                    else if(board[i][j+1] == tile)
                    {
                            int temp = board[i][j+1];              // moving tiles
                            board[i][j+1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                    }
                    return false;
                }
                else if( j == (d-1))
                {
                     if(board[i-1][j] == tile )
                    {
                            int temp = board[i-1][j];
                            board[i-1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                    }
                    else if(board[i+1][j] == tile )
                    {
                            int temp = board[i+1][j];
                            board[i+1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                    }
                     else if(board[i][j-1] == tile)
                    {
                           int temp = board[i][j-1];              // moving tiles
                            board[i][j-1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        
                    }
                    return false;
                }
                else if(board[i-1][j] == tile )
                {
                            int temp = board[i-1][j];
                            board[i-1][j] = board[i][j];
                            board[i][j] = temp;  
                            return true;
                }
                else if(board[i+1][j] == tile )
                {
                            int temp = board[i+1][j];
                            board[i+1][j] = board[i][j];             // moving tiles
                            board[i][j] = temp;  
                            return true;
                }
                else if(board[i][j-1] == tile)
                {
                           int temp = board[i][j-1];              // moving tiles
                            board[i][j-1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                        
                }
                 else if(board[i][j+1] == tile)
                {
                            int temp = board[i][j+1];              // moving tiles
                            board[i][j+1] = board[i][j];
                            board[i][j] = temp;                       
                            return true;
                }
                    return false;
            }
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
     int check=1;
    for(int i=0; i<d; i++)
    {
        for(int j=0; j< d; j++)
        {
            if(i == (d-1) && j ==(d-1))
                  break;                    // break when empty space comes
            if(board[i][j] != check)
                 return false;
          
            check++;
        }
    }
      return true;
}
