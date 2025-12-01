// game.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "game.h"

/* 기록 파일명 */
static const char* RECORD_FILE = "record.txt";

/* 기록 저장: append 모드로 한 줄 추가 */
void saveRecord(int score, int success, int fail) {
    FILE* fp = fopen(RECORD_FILE, "a");
    if (!fp) {
        fprintf(stderr, "기록 파일 열기 실패: %s\n", RECORD_FILE);
        return;
    }

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    if (t) {
        fprintf(fp, "[%04d-%02d-%02d %02d:%02d] 점수:%d 성공:%d 실패:%d\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min,
            score, success, fail);
    }
    else {
        fprintf(fp, "[unknown time] 점수:%d 성공:%d 실패:%d\n", score, success, fail);
    }

    fclose(fp);
}

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* startGame: 메인 게임 루프 */
void startGame(void) {
    srand((unsigned int)time(NULL));

    int score = 0;
    int success = 0;
    int fail = 0;
    int level = 1;
    const int totalRounds = 5; /* 한 세션의 주문 수 */

    char input[128];

    printf("\n=== 카페 주문 시뮬레이션 게임 시작 ===\n");
    printf("규칙: 화면에 뜨는 레시피 순서대로 재료를 정확히 입력하세요.\n");
    printf("입력은 엔터 입니다.\n");

    for (int round = 1; round <= totalRounds; round++) {
        printf("\n--- %d번째 주문 ---\n", round);

        int idx = rand() % MENU_COUNT;
        Menu* m = &menuList[idx];

        /* 레벨에 따라 제한시간 조정 (기본 15초, 레벨 오르면 -2초, 최소 5초) */
        int limit = 15 - (level - 1) * 2;
        if (limit < 5) limit = 5;

        printf("주문: %s\n", m->name);
        printf("재료 개수: %d\n", m->count);
        printf("제한시간: %d초\n", limit);

        printf("레시피: ");
        for (int j = 0; j < m->count; j++) {
            printf("%s", m->ingredients[j]);
            if (j < m->count - 1) printf(" -> ");
        }
        printf("\n");

        time_t start = time(NULL);
        int correct = 1;

        for (int i = 0; i < m->count; i++) {
            printf("[%d/%d] 입력: ", i + 1, m->count);

            /* fgets로 입력 받기 */
            if (!fgets(input, sizeof(input), stdin)) {
                printf("입력 오류 발생. 게임을 종료합니다.\n");
                correct = 0;
                break;
            }
            /* 개행 문자 제거 */
            input[strcspn(input, "\r\n")] = 0;

            /* 제한시간 체크 */
            if (difftime(time(NULL), start) > (double)limit) {
                printf("시간 초과 (제한: %d초)\n", limit);
                correct = 0;
                break;
            }

            /* 재료 문자열 비교 */
            if (strcmp(input, m->ingredients[i]) != 0) {
                printf("재료가 일치하지 않습니다. 정답: \"%s\"\n", m->ingredients[i]);
                correct = 0;
                break;
            }
        }

        if (correct) {
            printf("메뉴 완성 +100점\n");
            score += 100;
            success++;
            /* 레벨업 조건: 누적 점수가 200 이상이면 레벨업 */
            if (score >= level * 200) {
                level++;
                printf("레벨업| 현재 레벨: %d (제한시간 감소)\n", level);
            }
        }
        else {
            printf("실패 -50점\n");
            score -= 50;
            fail++;
            if (score < 0) score = 0; /* 점수 음수 방지 */
        }
    }

    printf("\n=== 게임 종료 ===\n");
    printf("총 점수: %d\n성공: %d  실패: %d\n", score, success, fail);

    saveRecord(score, success, fail);
    printf("기록이 '%s'에 저장되었습니다.\n", RECORD_FILE);
}

