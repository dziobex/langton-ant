#include <stdio.h>
#include <wchar.h>
#include <locale.h>
// LINE_VERTICAL:│
// LINE_HORIZONTAL:─
// LINE_DOWN_RIGHT:┌
// LINE_DOWN_LEFT:┐
// LINE_UP_RIGHT:└
// LINE_UP_LEFT:┘
// SQUARE_WHITE: 
// SQUARE_BLACK:█
// ARROW_NORTH_WHITE:△
// ARROW_NORTH_BLACK:▲
// ARROW_EAST_WHITE:▷
// ARROW_EAST_BLACK:▶
// ARROW_SOUTH_WHITE:▽
// ARROW_SOUTH_BLACK:▼
// ARROW_WEST_WHITE:◁
// ARROW_WEST_BLACK:◀
int main() {
    
    printf("█ \n");
    
    char *c = "█";
    printf("%s %d \n", c, strlen(c));
    
    // setlocale(LC_ALL, "");
    setlocale(LC_ALL, "C.UTF-8");
    wchar_t *wc = L"█";
    printf("%ls %d \n", wc, wcslen(wc));
    return 0;
}