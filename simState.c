#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct State
{
    char letter;
    int zeroState;
    int finalState;
    int deleted;
    int reachable;
};

void print(struct State array[])
{
    for (int i = 0; i < 8; i++)
    {
        if (!array[i].deleted)
            printf(" %c %c %c \n", array[i].letter, array[array[i].zeroState].letter, array[array[i].finalState].letter);
    }
}

void checkReach(struct State array[], struct State currentt, int n)
{
    int id;
    for (int j = 0; j < 8; j++)
    {
        if (array[j].letter == currentt.letter)
        {
            id = j;
        }
    }
    if (n == 1)
    {
        array[id].reachable = 1;
        for (int k = 0; k < 8; k++)
        {
            array[k].reachable = 0;
        }
    }
    if (n < 20)
    {
        array[id].reachable = 1;
        array[array[id].finalState].reachable = 1;
        array[array[id].zeroState].reachable = 1;
        checkReach(array, array[array[id].zeroState], n + 2);
        checkReach(array, array[array[id].finalState], n + 2);
    }
}

int main(int argc, char *argv[])
{
    int x = 0;
    int id1;
    struct State newState;
    int index;
    int id;
    // a b c d e f g h
    // 0 1 2 3 4 5 6 7
    struct State arrSt[8];
    arrSt[0].letter = 'A';
    arrSt[0].zeroState = 6;
    arrSt[0].finalState = 1;

    arrSt[1].letter = 'B';
    arrSt[1].zeroState = 2;
    arrSt[1].finalState = 1;

    arrSt[2].letter = 'C';
    arrSt[2].zeroState = 5;
    arrSt[2].finalState = 7;

    arrSt[3].letter = 'D';
    arrSt[3].zeroState = 1;
    arrSt[3].finalState = 4;

    arrSt[4].letter = 'E';
    arrSt[4].zeroState = 0;
    arrSt[4].finalState = 3;

    arrSt[5].letter = 'F';
    arrSt[5].zeroState = 3;
    arrSt[5].finalState = 7;

    arrSt[6].letter = 'G';
    arrSt[6].zeroState = 4;
    arrSt[6].finalState = 5;

    arrSt[7].letter = 'H';
    arrSt[7].zeroState = 6;
    arrSt[7].finalState = 0;

    for (int i = 0; i < 8; i++)
    {
        arrSt[i].deleted = 0;
        arrSt[i].reachable = 0;
    }
    struct State current = arrSt[7];
    print(arrSt);
    char input[30];
    printf("your current stae is H ");
    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0';

            if (input[0] == 'E')
                break;

            switch (input[0])
            {
            case 'p':
            case 'P':
                print(arrSt);
                break;
            case '1':
                current = arrSt[current.finalState];
                printf(" %c ", current.letter);
                break;
            case '0':
                current = arrSt[current.zeroState];
                printf(" %c ", current.letter);
                break;
            case 'c':
            case 'C':
                for (int i = 0; i < 8; i++)
                {
                    if (arrSt[i].letter == current.letter)
                        id = i;
                    if (arrSt[i].letter == input[4])
                    {
                        newState = arrSt[i];
                        index = i;
                    }
                }
                if (newState.deleted)
                    printf("Error: this state is delted");
                else
                {
                    if (input[2] == '1')
                    {
                        arrSt[id].finalState = index;
                    } // the end of input '1'

                    if (input[2] == '0')
                    {
                        arrSt[id].zeroState = index;
                    } // the end of input '0'
                }
                break;

            case 'g':
                checkReach(arrSt, current, 1);
                for (int i = 0; i < 8; i++)
                {
                    if (arrSt[i].reachable == 0)
                    {
                        x = 10;
                    }
                }
                if (x == 10)
                {
                    printf("\nGarbage:");
                    for (int i = 0; i < 8; i++)
                    {
                        if (arrSt[i].reachable == 0 && arrSt[i].deleted != 1)
                        {

                            printf(" %c ", arrSt[i].letter);
                        }
                    }
                }
                else
                    printf("\n No Garbage");
                break;

            case 'd':
                if (input[2] == '\0')
                {
                    checkReach(arrSt, current, 1);
                    for (int i = 0; i < 8; i++)
                    {
                        if (arrSt[i].reachable == 0)
                        {
                            x = 10;
                        }
                    }
                    if (x == 10)
                    {
                        printf("\n Deleted:");
                        for (int i = 0; i < 8; i++)
                        {
                            if (arrSt[i].reachable == 0)
                            {
                                arrSt[i].deleted = 1;
                                printf(" %c ", arrSt[i].letter);
                            }
                        }
                    }
                    else
                        printf("\n Nothing Deleted\n");
                    break;
                }
                else
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if (input[2] == arrSt[i].letter)
                            id1 = i;
                    }
                    if (arrSt[id1].reachable == 1)
                    {
                        printf("this state is reachable");
                    }
                    else
                    {
                        printf("dleted");
                        arrSt[id1].deleted = 1;
                    }
                }
            } // switch close

        } // if condition closed scanner
    }

    exit(0);
}
