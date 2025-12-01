// main.c
#include <stdio.h>
#include "menu.h"
#include "game.h"

int main(void) {
    /* 메뉴 초기화 */
    initMenu();

    printf("카페 주문 시뮬레이션 게임입니다.\n");
    printf("시작하려면 Enter를 누르세요...");
    /* 사용자 엔터 대기 */
    int ch = getchar();
    if (ch != '\n') {
        /* 만약 이전에 남아있는 문자 등 처리 */
        while (ch != '\n' && ch != EOF) ch = getchar();
    }

    /* 게임 시작 */
    startGame();

    return 0;
}
