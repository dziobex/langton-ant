#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void printbuffer (const char* pt, size_t max)
{
  int length;
  wchar_t dest;

  mbtowc (NULL, NULL, 0);  /* reset mbtowc */

  while (max>0) {
    length = mbtowc(&dest,pt,max);
    if (length<1) break;
    printf ("[%lc]",dest);
    pt+=length; max-=length;
  }
}

int main() {
    
    printf("█ \n");
    
    char *c = "█";
    printf("%s %d \n", c, strlen(c));
    
    //setlocale(LC_ALL, "");
    setlocale(LC_ALL, "C.UTF-8");

    char* string = "█";
    printbuffer(string, sizeof string);
}