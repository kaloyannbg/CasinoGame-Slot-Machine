#include "includes.h"

void printCover()
{
    printf("%s", STARS_ROW);
    printf("   *      CASINO KALOYAN GAMING      *\n");
    printf("%s", STARS_ROW);
    printf("   *         SLOT MACHINE #21        *\n");
    printf("%s", STARS_ROW);
}

char **setMemForTwoDArray(int rows, int cols)
{
    char **twoDArr = (char **)calloc(rows, sizeof(char *));

    for (int i = 0; i < rows; i++)
    {
        twoDArr[i] = (char *)calloc(cols, sizeof(char));

        for (int j = 0; j < cols; j++)
        {
            twoDArr[i][j] = 'O';
        }
    }
    return twoDArr;
}

void putRandomNumbersInArr(char **gameBoard, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            gameBoard[i][j] = (rand() % MAX_ROLLING_NUMBER) + '0';
        }
    }
}

double currProfit(char **gameBoard, int rows, int cols, double bet)
{
    double totalProfit = 0;
    int j = 0;
    int k = 0;
    for (int i = 0; i < rows; i++)
    { //(gameBoard[i][j] == gameBoard[i+1][j+1]) && (i != (rows-1)) && (j != (cols-1))) )
        if (gameBoard[0][0] == gameBoard[1][1] && i == 0)
        {
            totalProfit = totalProfit + (bet * 1.3);

            for (k = 1; (k != (rows - 1)) && (k != (cols - 2)) && (gameBoard[k][k] == gameBoard[k + 1][k + 1]); k++)
            {
                totalProfit = totalProfit + (bet * 1.5);
            }
        }

        if (gameBoard[i][0] == gameBoard[i][1])
        {
            totalProfit = totalProfit + (bet * 1.18);

            for (j = 1; (j != (cols - 1) && (gameBoard[i][j] == gameBoard[i][j + 1])); j++)
            {
                totalProfit = totalProfit + (bet * 1.28);
            }

            if (j == (cols - 2))
            {
                totalProfit = totalProfit + (bet * 4.50);
            }
            else if (j == (cols - 1))
            {
                totalProfit = totalProfit + (bet * 6.80);
            }
        }
    }
    return totalProfit;
}

void printDisplayOfNumberGame(char **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("   *  ");
        for (int j = 0; j < cols; j++)
        {
            switch (arr[i][j])
            {
            case '0':
                printf(COLOR_LIGHT_YELLOW "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '1':
                printf(COLOR_LIGHT_WHITE "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '2':
                printf(COLOR_LIGHT_BLUE "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '3':
                printf(COLOR_LIGHT_GREEN "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '4':
                printf(COLOR_LIGHT_CYAN "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '5':
                printf(COLOR_LIGHT_GRAY "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '6':
                printf(COLOR_LIGHT_RED "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case '7':
                printf(COLOR_LIGHT_MAGENTA "| %c | " ANSI_COLOR_RESET, arr[i][j]);
                break;
            case 'O':
                printf("| %c | ", arr[i][j]);
            default:
                break;
            }
        }
        printf(" *\n");
    }
    printf("%s", STARS_WITH_SPACE_BETWEEN);
    printf("%s", STARS_ROW);
}

void clearScreen()
{
    system("clear");
}

void printMenu()
{
    printf("   * Press \'ENTER\' to PLAY           * \n");
    printf("   * Press \'B\' to update balance     * \n");
    printf("   * Press \'U\' to change your Bet    * \n");
    printf("   * Press \'D\' to draw money         * \n");
    printf("   * Press \'E\' to draw and QUIT      * \n");
    printf("%s", STARS_ROW);
}

double getDouble()
{
    char buffer[128] = {0};
    fgets(buffer, 128, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    double num = atof(buffer);
    if (num >= INT_MAX || num < 0)
    {
        return 0;
    }
    return num;
}

void clearTwoDArr(char **twoDArr)
{
    for (int i = 0; i < MAX_ROWS_NUMBERS_GAME; i++)
    {
        free(twoDArr[i]);
    }
    free(twoDArr);
}

void firstScreenPrintAndLogic(t_player *currPlayer)
{
    clearScreen();
    printf(" -- Welcome in ONLINE CASINO \'Kaloyan Angelov\' -- \n");

    printf(" -- Please add money to your balance: ");
    (*currPlayer).balance = getDouble();

    while ((*currPlayer).balance == 0.00 || (*currPlayer).balance > MAX_BALANCE)
    {
        clearScreen();
        printf("  !! --  BALANCE ERROR -- !!\n");
        printf("  1. CAN BE ONLY NUMBER\n");
        printf("  2. CAN\'T BE ZERO (0) or smaller num.\n");
        printf("  3. BIGGER THAN %.2f EUR !! \n", MAX_BALANCE);
        printf(" -- Please add money to your balance: ");
        (*currPlayer).balance = getDouble();
    }

    printf(" -- Please enter your bet: ");
    (*currPlayer).bet = getDouble();

    while ((*currPlayer).bet == 0.00 || (*currPlayer).bet > (*currPlayer).balance || (*currPlayer).bet > MAX_BET)
    {
        clearScreen();
        printf("  !! -- BET ERROR -- \n");
        printf("  1. BET CAN BE ONLY NUMBER \n");
        printf("  2. CAN\'T BE ZERO (0) or smaller num.\n");
        printf("  3. BIGGER THAN BALANCE: %.2f EUR !! \n", (*currPlayer).balance);
        printf("  4. BIGGER THAN MAX BET: %.2f\n", MAX_BET);
        printf(" -- Please enter your bet: ");
        (*currPlayer).bet = getDouble();
    }
}

void clearScreenPrintCoverPrintGameBoardPrintProfitPrintBet(char **numberGameArr, double userBet, double profitPay, double balance)
{
    clearScreen();
    printCover();
    printDisplayOfNumberGame(numberGameArr, MAX_ROWS_NUMBERS_GAME, MAX_COLS_NUMBERS_GAME);
    printf("   *  You win: %-6.2f    Bet: %6.2f * \n", profitPay, userBet);
    printf("%s", STARS_ROW);
    printf("   *  Balance: %-8.2fCurrency: EUR * \n", balance);
    printf("%s", STARS_ROW);
    printMenu();
}
int main(int argc, char const *argv[])
{
    SET_TIME_SEEDS
    t_player currPlayer;

    firstScreenPrintAndLogic(&currPlayer);

    char c = 0, **numberGameArr = setMemForTwoDArray(MAX_ROWS_NUMBERS_GAME, MAX_COLS_NUMBERS_GAME);
    double profitPay = 0.00;

    while (c != MENU_EXIT_LOWER && c != MENU_EXIT_UPPER)
    {
        clearScreenPrintCoverPrintGameBoardPrintProfitPrintBet(numberGameArr, currPlayer.bet, profitPay, currPlayer.balance);
        profitPay = 0.00;
        c = getch();
        if (c == ENTER)
        {
            if (currPlayer.balance < currPlayer.bet)
            {
                printf(" -- Sorry, you don\'t have enough balance -- \n");
                system("pause");
            }
            else
            {
                profitPay = 0.00;
                putRandomNumbersInArr(numberGameArr, MAX_ROWS_NUMBERS_GAME, MAX_COLS_NUMBERS_GAME);
                profitPay = currProfit(numberGameArr, MAX_ROWS_NUMBERS_GAME, MAX_COLS_NUMBERS_GAME, currPlayer.bet);
                clearScreenPrintCoverPrintGameBoardPrintProfitPrintBet(numberGameArr, currPlayer.bet, profitPay, currPlayer.balance);
                currPlayer.balance = (currPlayer.balance - currPlayer.bet) + profitPay;
            }
        }
        else if (c == 'b' || c == 'B')
        {
            printf(" -- Add balance: ");
            double addBalance = getDouble();
            currPlayer.balance += addBalance;
        }
        else if (c == 'u' || c == 'U')
        {
            printf(" -- Change bet: ");
            double newBet = getDouble();
            currPlayer.bet = newBet;
        }
        else if (c == MENU_EXIT_LOWER || c == MENU_EXIT_UPPER)
        {
            printf("   *   You draw: %-8.2f EUR. Bye!  *\n", currPlayer.balance);
            printf("%s", STARS_ROW);
            break;
        }
        else if (c != ENTER || c != MENU_EXIT_LOWER || c != MENU_EXIT_UPPER)
        {
            printf(" \n  !! INVALID KEY !!  \n");
        }
    }

    clearTwoDArr(numberGameArr);

    return 0;
}
