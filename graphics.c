#include <stdio.h>

// 주사위 숫자 패턴을 정의
const char* dicePatterns[6][5] = {
    {
        "*********",
        "*       *",
        "*   *   *",
        "*       *",
        "*********"
    },
    {
        "*********",
        "* *     *",
        "*       *",
        "*     * *",
        "*********"
    },
    {
        "*********",
        "* *     *",
        "*   *   *",
        "*     * *",
        "*********"
    },
    {
        "*********",
        "* *   * *",
        "*       *",
        "* *   * *",
        "*********"
    },
    {
        "*********",
        "* *   * *",
        "*   *   *",
        "* *   * *",
        "*********"
    },
    {
        "*********",
        "* *   * *",
        "* *   * *",
        "* *   * *",
        "*********"
    }
};

// 주사위를 가로로 출력하는 함수
void displayAllDiceHorizontal(int dice[], int numDice) {
    for (int row = 0; row < 5; row++) { // 각 주사위 패턴의 행을 출력
        for (int i = 0; i < numDice; i++) {
            printf("%s  ", dicePatterns[dice[i] - 1][row]); // 각 주사위의 해당 행 출력
        }
        printf("\n");
    }
}


// 점수판 출력 함수
void displayScoreboard(int scores[], int numCategories) {
    const char *categories[] = {
        "1: Ones", "2: Twos", "3: Threes", "4: Fours", "5: Fives", "6: Sixes",
        "7: Yacht", "8: Four of a Kind", "9: Full House",
        "10: Little Straight", "11: Big Straight", "12: Choice"
    };

    printf("\n======== Scoreboard ========\n");
    for (int i = 0; i < numCategories; i++) {
        printf("%-20s: %d points\n", categories[i], scores[i]);
    }
    printf("============================\n");
}
//시작 할 때 게임 제목 출력
void displayWelcomeScreen() {
    printf("\n                                        .-==-:                          \n");
    printf("                                     -+#*=--=*%%*-.                      \n");
    printf("                                 :=##+:  :--:  :=##+:                   \n");
    printf("                             .-*%%*-.    +@@@@#    .-+#*=.               \n");
    printf("                          :+##=:         .::.         .=*#+-.           \n");
    printf("                        +%%*-. .+#%%#*:            .+#%%#*:  :+%%*.       \n");
    printf("                       #@%%=:  .=*#*+.             =*#*+.  .=#@%%.        \n");
    printf("                      -@..=*%%*-.         :--:          :+##=: #+          \n");
    printf("                      -@     :+##+:     +@@@@#     .=*#+-     #+          \n");
    printf("                      -@  =*=   .-*%%*=.  .::.  .-+#*=.   -+=  #+          \n");
    printf("                      -@  %@@#      :=##+-::-=##+:       *@@@  #+          \n");
    printf("                      -@  -%%@@.         -#@@%%=.        .@@@=  #+         \n");
    printf("                      -@   .-:     .%@*.   #@.  =%@=      -=.   #+          \n");
    printf("                      -@            %@@#   +#  =@@@=     .*%%#  #+         \n");
    printf("                      -@       +#=  :#@#  +#  =@%%=      %@@@%%  #+         \n");
    printf("                      -@       @@@#       +#    -=.     #%@#:  #+          \n");
    printf("                      -@  :=:  -%%@@.      +#  .#@@+      .-:  #+          \n");
    printf("                      -@  %@@*   :.        +#  +@@@:     =@@@  #+          \n");
    printf("                      -@  =@@@:           +#  :*+.     .@@@*  #+          \n");
    printf("                      .%%+  :==      *#+   +#   :*#-     +*=  -@:          \n");
    printf("                       .**#=:      .@@@*  +#  :@@@+       .=**#:         \n");
    printf("                         .-*%%*-.    -%%@%%  +#  +@@#.    -+##=:           \n");
    printf("                             :=##+:   :.  +#   ::  :=##+-                   \n");
    printf("                                .-*%%*=.   +#   .-+#*=.                      \n");
    printf("                                    :=##+-#%%-=##+:                          \n");
    printf("                                        -=++=-.                               \n\n");
    printf("******************************************************************************************\n");
    printf("                             ###        ##                 ###     ## \n");
    printf("                              ##        ##                  ## \n");
    printf("  ##  ##    ####     ####     ##       #####                ##    ###      ####     #### \n");
    printf("  ##  ##       ##   ##  ##    #####     ##               #####     ##     ##  ##   ##  ## \n");
    printf("  ##  ##    #####   ##        ##  ##    ##              ##  ##     ##     ##       ###### \n");
    printf("   #####   ##  ##   ##  ##    ##  ##    ## ##           ##  ##     ##     ##  ##   ## \n");
    printf("      ##    #####    ####    ###  ##     ###             ######   ####     ####     ##### \n");
    printf("  ##### \n");
    printf("******************************************************************************************\n");
    printf("Welcome to the Yacht Dice Game!\n");
    printf("Roll the dice and choose categories to score points.\n\n");
}
