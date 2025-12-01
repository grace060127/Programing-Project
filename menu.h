// menu.h
#ifndef MENU_H
#define MENU_H

#define MAX_ING 10
#define MAX_ING_NAME 30
#define MENU_COUNT 7

/* 메뉴 구조체 */
typedef struct {
    char name[50];
    char ingredients[MAX_ING][MAX_ING_NAME];
    int count;
} Menu;

/* menuList의 실제 정의는 menu.c에 있음 */
extern Menu menuList[MENU_COUNT];

/* 메뉴 초기화 함수 */
void initMenu(void);

#endif 
