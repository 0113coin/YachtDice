#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "graphics.c"

#define NUM_DICE 5
#define NUM_CATEGORIES 12
//키보드 입력값
#define ARROW 224
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32
#define ENTER 13
#define ESC 27
//출력되는 글자 색
#define SELECTED_COLOR 10 // 녹색
#define CURSOR_COLOR 9    // 파란색
#define DEFAULT_COLOR 15  // 기본 색상


// 함수 선언
void rollDice(int dice[], int keep[]);
void displayDice(int dice[]);

int calculateScore(int category, int dice[]);
int checkYacht(int dice[]);
int checkFourOfAKind(int dice[]);
int checkFullHouse(int dice[]);
int checkLittleStraight(int dice[]);
int checkBigStraight(int dice[]);
int calculateSum(int dice[], int num);

int chooseBestCategory(int scores[], int dice[]);
void decideKeepDice(int dice[], int keep[], int targetCategory);
void recordComputerScore(int scores[], int dice[]);

void printPlayerScores(int scores[]);
void printComputerScores(int scores[]);

// UI 함수

// 텍스트 색상 설정 함수
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 주사위 출력 함수 (커서와 선택 상태 표시)
void displayDiceWithCursor(int dice[], int keep[], int cursor) {
    system("cls"); // 화면 초기화
    printf("Use arrow keys to move, SPACE to toggle selection, ENTER to confirm, ESC to exit.\n");

    for (int i = 0; i < NUM_DICE; i++) {
        if (i == cursor) {
            setColor(CURSOR_COLOR); // 커서에 위치한 주사위는 파란색
        }
        else if (keep[i]) {
            setColor(SELECTED_COLOR); // 선택된 주사위는 녹색
        }
        else {
            setColor(DEFAULT_COLOR); // 기본 색상
        }

        printf(" %d ", dice[i]);
        setColor(DEFAULT_COLOR); // 색상 초기화
    }
    printf("\n");
}

// 최종 선택 상태 확인 함수
int confirmSelection(int dice[], int keep[]) {
    system("cls");
    printf("Confirm your selection:\n");

    for (int i = 0; i < NUM_DICE; i++) {
        if (keep[i]) {
            setColor(SELECTED_COLOR); // 선택된 주사위는 녹색
        }
        else {
            setColor(DEFAULT_COLOR); // 기본 색상
        }
        printf(" %d ", dice[i]);
    }
    setColor(DEFAULT_COLOR); // 색상 초기화
    printf("\nPress ENTER to confirm or ESC to go back.\n");

    while (1) {
        int key = _getch();
        if (key == ENTER) {
            return 1;
        }
        else if (key == ESC) {
            return 0;
        }
    }
}


// 화살표 키로 주사위를 선택하거나 유지/해제 처리
void handleDiceSelection(int dice[], int keep[]) {
    int cursor = 0; // 커서 초기 위치
    int running = 1;

    while (running) {
        displayDiceWithCursor(dice, keep, cursor); // 주사위 출력

        int key = _getch(); // 키 입력 처리
        if (key == ARROW) {
            key = _getch();
            if (key == LEFT) {
                cursor = (cursor == 0) ? NUM_DICE - 1 : cursor - 1; // 왼쪽 이동
            }
            else if (key == RIGHT) {
                cursor = (cursor == NUM_DICE - 1) ? 0 : cursor + 1; // 오른쪽 이동
            }
        }
        else if (key == SPACEBAR) {
            keep[cursor] = !keep[cursor]; // 선택 상태 토글
        }
        else if (key == ENTER) {
            if (confirmSelection(dice, keep)) {
                printf("Selection confirmed. Re-rolling dice...\n");
                Sleep(1000); // 1초 대기 후 종료
                running = 0;
            }
        }
        else if (key == ESC) {
            printf("Exiting dice selection...\n");
            Sleep(1000); // 1초 대기 후 종료
            running = 0;
        }
    }
}

// 메인 함수
int main() {
    displayWelcomeScreen();   // 시작 화면을 표시
    int dice[NUM_DICE];       // 현재 주사위 눈
    int keep[NUM_DICE] = { 0 }; // 유지할 주사위 표시
    int playerScores[NUM_CATEGORIES];
    int computerScores[NUM_CATEGORIES];
    int category, rolls, i, mode;

    // 점수 배열 초기화
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        playerScores[i] = -1;    // -1로 초기화
        computerScores[i] = -1;  // -1로 초기화
    }

    srand(time(0)); // 랜덤 시드 설정

    printf("Welcome to Yacht Dice!\n");
    printf("\nEnter a number to select a mode (1: Single play, 2: VS Computer): ");
    scanf("%d", &mode);

    // Easter Egg!
    if (mode == 123456) {
    system("cls");
    printf("Easter egg found!\n\n");
    printf("================================\n");
    printf("  _     _     _     _     _     \n");
    printf(" | |   | |   | |   | |   | |    \n");
    printf(" | |   | |   | |   | |   | |    \n");
    printf(" | |   | |   | |   | |   | |    \n");
    printf(" |_____|_____|_____|_____|____| \n");
    printf("          YACHT DICE           \n");
    printf("================================\n");
    Sleep(1000);
    printf("\nMade by HyeonSeok Song, EunSu Kim, SeongJun Park\n");
    Sleep(2000);
    printf("\n^_^\n");
    Sleep(2000);

    return 0;
}

    for (int turn = 0; turn < NUM_CATEGORIES; turn++) {
        printf("\n--- Turn %d ---\n", turn + 1);

        // 플레이어 턴
        if (mode == 2) {
            printf("\nYour turn!\n");
        }

        for (i = 0; i < NUM_DICE; i++) {
            keep[i] = 0;
        }

        // 주사위 굴리기 최대 3번
        for (rolls = 0; rolls < 3; rolls++) {
            rollDice(dice, keep);
            printf("\nPress any key to continue...\n");
            _getch(); // 사용자가 키를 누를 때까지 대기
            printf("\nRoll %d: \n", rolls + 1);

            if (rolls < 2) {
                printf("You can choose which dice to keep or re-roll.\n");
                handleDiceSelection(dice, keep); // 화살표 키를 사용해 주사위 선택
            }
        }

        int chosen = 1;
        while (chosen) {
            displayDice(dice);
            printPlayerScores(playerScores); // 플레이어 점수 출력
            printf("Choose a category (1:Ones, 2:Twos, 3:Threes, 4:Fours, 5:Fives, 6:Sixes, 7:Yacht, 8:Four of a Kind, 9:Full House, 10:Little Straight, 11:Big Straight, 12:Choice): ");
            scanf("%d", &category);
            category--; // 배열 인덱스 맞추기

            if (playerScores[category] == -1) { // 아직 선택되지 않은 카테고리
                playerScores[category] = calculateScore(category, dice);
                printf("You scored %d points in this category.\n", playerScores[category]);
                chosen = 0;
            }
            else {
                printf("Category already chosen, try another category.\n");
            }
        }

        // 컴퓨터 턴
        if (mode == 2) {
            printf("\nComputer's turn!\n");

            // 컴퓨터 주사위 유지 여부 초기화
            for (i = 0; i < NUM_DICE; i++) {
                keep[i] = 0;
            }

            // 컴퓨터 주사위 굴리기 (3회)
            for (rolls = 0; rolls < 3; rolls++) {
                rollDice(dice, keep);
                printf("\nComputer's Roll %d: \n", rolls + 1);


                // 첫 번째와 두 번째 굴림에서는 주사위 선택 로직 수행
                if (rolls < 2) {
                    int targetCategory = chooseBestCategory(computerScores, dice);
                    if (targetCategory >= 0 && targetCategory < NUM_CATEGORIES) {
                        decideKeepDice(dice, keep, targetCategory);
                    }
                }
            }

            displayAllDiceHorizontal(dice, NUM_DICE);

            // 컴퓨터 점수 기록
            recordComputerScore(computerScores, dice);

            // 컴퓨터 점수 출력
            printComputerScores(computerScores);
        }

    }

    // 최종 점수 출력
    printf("\nFinal Scores:\n");
    printPlayerScores(playerScores);
    if (mode == 2) {
        printComputerScores(computerScores);

        int totalPlayerScore = 0, totalComputerScore = 0;
        for (i = 0; i < NUM_CATEGORIES; i++) {
            if (playerScores[i] != -1) totalPlayerScore += playerScores[i];
            if (computerScores[i] != -1) totalComputerScore += computerScores[i];
        }

        printf("Your total score: %d\n", totalPlayerScore);
        printf("Computer's total score: %d\n", totalComputerScore);

        if (totalPlayerScore > totalComputerScore) {
            printf("You Won!\n");
        }
        else if (totalPlayerScore < totalComputerScore) {
            printf("You Lost!\n");
        }
        else {
            printf("It's a Draw!\n");
        }
    }
    else {
        int totalPlayerScore = 0;
        for (i = 0; i < NUM_CATEGORIES; i++) {
            if (playerScores[i] != -1) totalPlayerScore += playerScores[i];
        }
        printf("Your total score: %d\n", totalPlayerScore);
    }

    printf("\nPlayer");
    displayScoreboard(playerScores, NUM_CATEGORIES);

    if (mode == 2) {
        printf("\nComputer");
        displayScoreboard(computerScores, NUM_CATEGORIES);
    }


    return 0;
}


// 주사위 굴리기
void rollDice(int dice[], int keep[]) {
    for (int i = 0; i < NUM_DICE; i++) {
        if (keep[i] == 0) {
            dice[i] = rand() % 6 + 1; // 1 ~ 6
        }
    }
    displayDice(dice); // 주사위 출력
}



// 주사위 출력
void displayDice(int dice[]) {
    printf("Current dice:\n");
    displayAllDiceHorizontal(dice, NUM_DICE); // 주사위 배열과 주사위 개수 전달
    printf("\n");
}

// 점수 계산 함수
int calculateScore(int category, int dice[])
{
    switch (category)
    {
    case 0:
        return calculateSum(dice, 1); // Ones
    case 1:
        return calculateSum(dice, 2); // Twos
    case 2:
        return calculateSum(dice, 3); // Threes
    case 3:
        return calculateSum(dice, 4); // Fours
    case 4:
        return calculateSum(dice, 5); // Fives
    case 5:
        return calculateSum(dice, 6); // Sixes
    case 6:
        return checkYacht(dice) ? 50 : 0; // Yacht
    case 7:
        return checkFourOfAKind(dice); // Four of a Kind
    case 8:
        return checkFullHouse(dice) ? 25 : 0; // Full House
    case 9:
    {
        return checkLittleStraight(dice) ? 30 : 0; // Little Straight
    }
    case 10:
    {
        return checkBigStraight(dice) ? 40 : 0; // Big Straight
    }
    case 11:
    {
        return calculateSum(dice, 0); // Choice
    }
    default:
        return 0;
    }
}
// 특정 숫자 합산
int calculateSum(int dice[], int num)
{
    int sum = 0;
    for (int i = 0; i < NUM_DICE; i++)
    {
        if (num == 0 || dice[i] == num)
        {
            sum += dice[i];
        }
    }
    return sum;
}
// Yacht 점수 계산 : 모든 눈이 같을 때
int checkYacht(int dice[])
{
    for (int i = 1; i < NUM_DICE; i++)
    {
        if (dice[i] != dice[0])
        {
            return 0;
        }
    }
    return 1;
}
// Four of a Kind 점수 계산 : 4개의 눈이 같을 때
int checkFourOfAKind(int dice[])
{
    int counts[6] = { 0 };
    for (int i = 0; i < NUM_DICE; i++)
    {
        counts[dice[i] - 1]++;
    }
    for (int i = 0; i < 6; i++)
    {
        if (counts[i] >= 4)
        {
            return i * 4;
        }
    }
    return 0;
}
// Full House 점수 계산 : 3개,2개
int checkFullHouse(int dice[])
{
    int counts[6] = { 0 };
    int two = 0, three = 0;
    for (int i = 0; i < NUM_DICE; i++)
    {
        counts[dice[i] - 1]++;
    }
    for (int i = 0; i < 6; i++)
    {
        if (counts[i] == 3)
            three = 1;
        if (counts[i] == 2)
            two = 1;
    }
    return two && three;
}
// Little Straight 점수 계산 : 4개가 연속수일 때
int checkLittleStraight(int dice[])
{
    int counts[6] = { 0 };
    for (int i = 0; i < NUM_DICE; i++)
    {
        counts[dice[i] - 1]++;
    }
    for (int i = 0; i < 4; i++)
    {
        int result = counts[i] * counts[i + 1] * counts[i + 2] * counts[i + 3];
        if (result != 0)
            return counts[i] && counts[i + 1] && counts[i + 2] && counts[i + 3];
    }
}
// Big Straight 점수 계산 : 5개가 연속수일 때
int checkBigStraight(int dice[])
{
    int counts[6] = { 0 };
    for (int i = 0; i < NUM_DICE; i++)
    {
        counts[dice[i] - 1]++;
    }
    for (int i = 0; i < 2; i++)
    {
        int result = counts[i] * counts[i + 1] * counts[i + 2] * counts[i + 3] * counts[i + 4];
        if (result != 0)
            return counts[i] && counts[i + 1] && counts[i + 2] && counts[i + 3] && counts[i + 4];
    }
}

// 컴퓨터 최적 카테고리 선택
int chooseBestCategory(int scores[], int dice[]) {
    int maxScore = -1;
    int bestCategory = -1;

    // 가장 높은 점수를 기록할 카테고리 선택
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (scores[i] != -1) continue; // 이미 사용된 카테고리 건너뛰기
        int currentScore = calculateScore(i, dice);
        if (currentScore > maxScore) {
            maxScore = currentScore;
            bestCategory = i;
        }
    }

    // 유효한 카테고리가 없으면 -1 반환
    return bestCategory;
}


void decideKeepDice(int dice[], int keep[], int targetCategory) {
    // targetCategory에 따른 주사위 유지 로직을 결정
    switch (targetCategory) {
    case 0: // Ones
        for (int i = 0; i < NUM_DICE; i++) {
            if (dice[i] == 1) {
                keep[i] = 1; // 1이 나온 주사위는 유지
            }
            else {
                keep[i] = 0; // 다른 주사위는 다시 굴림
            }
        }
        break;

    case 1: // Twos
        for (int i = 0; i < NUM_DICE; i++) {
            if (dice[i] == 2) {
                keep[i] = 1;
            }
            else {
                keep[i] = 0;
            }
        }
        break;

    case 2: // Threes
        for (int i = 0; i < NUM_DICE; i++) {
            if (dice[i] == 3) {
                keep[i] = 1;
            }
            else {
                keep[i] = 0;
            }
        }
        break;

    case 3: // Fours
        for (int i = 0; i < NUM_DICE; i++) {
            if (dice[i] == 4) {
                keep[i] = 1;
            }
            else {
                keep[i] = 0;
            }
        }
        break;

    case 4: // Fives
        for (int i = 0; i < NUM_DICE; i++) {
            if (dice[i] == 5) {
                keep[i] = 1;
            }
            else {
                keep[i] = 0;
            }
        }
        break;

    case 5: // Sixes
        for (int i = 0; i < NUM_DICE; i++) {
            if (dice[i] == 6) {
                keep[i] = 1;
            }
            else {
                keep[i] = 0;
            }
        }
        break;

    case 6: // Yacht
        if (checkYacht(dice)) {
            for (int i = 0; i < NUM_DICE; i++) {
                keep[i] = 1; // 모두 동일하면 모두 유지
            }
        }
        break;

    case 7: // Four of a Kind
        if (checkFourOfAKind(dice)) {
            // 4개 이상 동일한 눈이 있을 경우, 해당 눈 유지
            int counts[6] = { 0 };
            for (int i = 0; i < NUM_DICE; i++) {
                counts[dice[i] - 1]++;
            }
            for (int i = 0; i < 6; i++) {
                if (counts[i] >= 4) {
                    for (int j = 0; j < NUM_DICE; j++) {
                        if (dice[j] == i + 1) {
                            keep[j] = 1;
                        }
                    }
                }
            }
        }
        break;

    case 8: // Full House
        if (checkFullHouse(dice)) {
            // 3개와 2개 유지
            int counts[6] = { 0 };
            for (int i = 0; i < NUM_DICE; i++) {
                counts[dice[i] - 1]++;
            }
            for (int i = 0; i < 6; i++) {
                if (counts[i] == 3 || counts[i] == 2) {
                    for (int j = 0; j < NUM_DICE; j++) {
                        if (dice[j] == i + 1) {
                            keep[j] = 1;
                        }
                    }
                }
            }
        }
        break;

    case 9: // Little Straight
        if (checkLittleStraight(dice)) {
            // 연속된 4개 숫자 유지
            for (int i = 0; i < NUM_DICE; i++) {
                if (dice[i] == 1 || dice[i] == 2 || dice[i] == 3 || dice[i] == 4) {
                    keep[i] = 1;
                }
                if (dice[i] == 2 || dice[i] == 3 || dice[i] == 4 || dice[i] == 5) {
                    keep[i] = 1;
                }
                if (dice[i] == 3 || dice[i] == 4 || dice[i] == 5 || dice[i] == 6) {
                    keep[i] = 1;
                }
            }
        }
        break;

    case 10: // Big Straight
        if (checkBigStraight(dice)) {
            // 연속된 5개 숫자 유지
            for (int i = 0; i < NUM_DICE; i++) {
                if (dice[i] == 1 || dice[i] == 2 || dice[i] == 3 || dice[i] == 4 || dice[i] == 5) {
                    keep[i] = 1;
                }
                if (dice[i] == 2 || dice[i] == 3 || dice[i] == 4 || dice[i] == 5 || dice[i] == 6) {
                    keep[i] = 1;
                }
            }
        }
        break;

    case 11: // Choice
        for (int i = 0; i < NUM_DICE; i++) {
            keep[i] = 1;
        }
        break;

    default:
        printf("Invalid category!\n");
        break;
    }
}

// 컴퓨터 점수 기록
void recordComputerScore(int scores[], int dice[]) {
    int chosenCategory = chooseBestCategory(scores, dice);
    int score = calculateScore(chosenCategory, dice);
    scores[chosenCategory] = score; // 해당 카테고리에 점수 기록
    printf("Computer scored %d points in category %d.\n", score, chosenCategory + 1);
}


// 게임 중 컴퓨터 점수 출력
void printComputerScores(int scores[]) {
    printf("Computer scores: ");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (scores[i] == -1) printf("[ ] "); // 미사용 카테고리
        else printf("[%d] ", scores[i]);
    }
    printf("\n");
}

// 게임 중 플레이어 점수 출력
void printPlayerScores(int scores[]) {
    printf("\nPlayer scores: ");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (scores[i] == -1) printf("[ ] "); // 미사용 카테고리
        else printf("[%d] ", scores[i]); // 기록된 점수
    }
    printf("\n");
}

