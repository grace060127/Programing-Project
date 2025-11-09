/* cafe_game.c
   C언어 콘솔 기반 카페 주문 시뮬레이터 (레시피 순서 맞추기 + 시간 제한)
   - 무작위 주문(음료 6종 + 디저트 2종)
   - 레시피 순서 맞추기(정답: 재료 순서)
   - 각 주문마다 전체 제한시간(초)
   - 점수, 레벨 시스템 (레벨 오르면 제한시간 감소)
   - 게임 결과를 record.txt에 저장 (append)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdio.h>
#include <string.h>

// 메뉴 구조체 정의
struct Menu {
    char name[50];          // 메뉴 이름
    char ingredients[10][30]; // 재료 이름 (최대 10개)
    int count;              // 재료 개수
};

int main() {
    // 메뉴 배열 정의
    struct Menu menuList[7] = {
        {
            "아이스 아메리카노",
            {"물", "얼음", "샷"},
            3
        },
        {
            "따뜻한 카페라떼",
            {"우유 스팀", "샷", "우유 담기"},
            3
        },
        {
            "아이스 바닐라라떼",
            {"시럽", "우유", "얼음", "샷"},
            4
        },
        {
            "따뜻한 그린티라떼",
            {"파우더", "시럽", "우유 스팀", "우유 담기"},
            4
        },
        {
            "자바칩 프라푸치노",
            {"블렌더", "우유", "파우더", "시럽", "얼음", "블렌더 돌리기", "음료 담기", "휘핑크림", "초코 드리즐", "초코칩"},
            10
        },
        {
            "티라미수",
            {"코코아가루", "베이킹파우더"},
            2
        },
        {
            "크로플",
            {"오븐에 굽기", "메이플시럽", "베이킹파우더"},
            3
        }
    };

    // 메뉴 출력 (테스트용)
    printf("=== 레시피 목록 ===\n\n");
    for (int i = 0; i < 7; i++) {
        printf("%d) %s\n", i + 1, menuList[i].name);
        printf("   레시피 순서: ");
        for (int j = 0; j < menuList[i].count; j++) {
            printf("%s", menuList[i].ingredients[j]);
            if (j < menuList[i].count - 1) printf(" → ");
        }
        printf("\n\n");
    }

    return 0;
}
