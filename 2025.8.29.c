#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
#include <conio.h>
//
//int main(void)
//{
//    clock_t initial_clock = clock();   // 초기 clock
//    int i = 1;
//    int go = 1;
//
//    system("cls");
//    printf("%d ", i);
//
//    while (i < 100)
//    {
//        if (go == 1)
//        {
//            clock_t current_clock = clock();   // 현재 clock
//            if (current_clock - initial_clock >= 1000)   // 1초 경과
//            {
//                i++;
//                system("cls");
//                printf("%d ", i);
//                initial_clock = clock();   // 현재 clock을 초기 clock으로 대입
//            }
//        }
//        if (_kbhit())   // 키 입력이 있었다면
//        {
//            if (_getch() == 'p')   // 'p' 키라면
//                go = (go + 1) % 2;   // 멈춤(0)/재개(1) 변환
//        }
//    }
//}

//#define KEY_ESC 27
//#define KEY_UP (256 + 72)
//#define KEY_DOWN (256 + 80)
//#define KEY_LEFT (256 + 75)
//#define KEY_RIGHT (256 + 77)
//
//int Getkey(void)
//{
//	int ch = _getch();
//
//	if (ch == 0 || ch == 224);
//	// 방향키의 경우 0 또는 224의 값이 먼저 입력됨
//	ch = 256 + _getch();
//	// 그 다음에 해당 방향키에 따라 72(Up),
//	// 80(Down), 75(Left), 77(Right) 값이 입력됨
//
//	return ch;
//}
//
//int main(void)
//{
//		int ch;
//	while ((ch = Getkey()) != KEY_ESC)
//	{
//		switch (ch)
//		{
//		case KEY_RIGHT:
//			printf("[Key Right]\n");
//			break;
//
//		case KEY_LEFT:
//				printf("[Key Left]\n");
//				break;
//		case KEY_UP:
//					printf("[Key Up]\n");
//					break;
//		case KEY_DOWN:
//						printf("[Key Down]\n");
//						break;
//		}
//	}
//
//}

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int key;
    int count = 0;

    printf("=== 키보드 값 출력 프로그램 ===\n");
    printf("키를 누르면 해당 키의 값을 출력합니다.\n");
    printf("ESC 키를 누르면 프로그램이 종료됩니다.\n");
    printf("=====================================\n\n");

    while (1) {
        printf("[%d] 키를 누르세요: ", ++count);

        key = _getch(); // 키 입력 받기 (화면에 표시되지 않음)

        if (key == 27) { // ESC 키 (ASCII 27)
            printf("\nESC 키가 눌렸습니다. 프로그램을 종료합니다.\n");
            break;
        }
        else if (key == 0 || key == 224) { // 확장 키 (특수키)
            int extended_key = _getch(); // 확장 키코드 읽기
            printf("\n   확장 키 감지!");
            printf("\n   첫 번째 값: %d", key);
            printf("\n   두 번째 값: %d", extended_key);

            // 주요 특수키 이름 출력
            switch (extended_key) {
            case 59: printf(" (F1)"); break;
            case 60: printf(" (F2)"); break;
            case 61: printf(" (F3)"); break;
            case 62: printf(" (F4)"); break;
            case 63: printf(" (F5)"); break;
            case 64: printf(" (F6)"); break;
            case 65: printf(" (F7)"); break;
            case 66: printf(" (F8)"); break;
            case 67: printf(" (F9)"); break;
            case 68: printf(" (F10)"); break;
            case 72: printf(" (위쪽 화살표)"); break;
            case 80: printf(" (아래쪽 화살표)"); break;
            case 75: printf(" (왼쪽 화살표)"); break;
            case 77: printf(" (오른쪽 화살표)"); break;
            case 71: printf(" (Home)"); break;
            case 79: printf(" (End)"); break;
            case 73: printf(" (Page Up)"); break;
            case 81: printf(" (Page Down)"); break;
            case 82: printf(" (Insert)"); break;
            case 83: printf(" (Delete)"); break;
            default: printf(" (알 수 없는 특수키)"); break;
            }
            printf("\n\n");
        }
        else { // 일반 키
            printf("\n   일반 키 감지!");
            printf("\n   ASCII 값: %d", key);

            if (key >= 32 && key <= 126) { // 출력 가능한 문자
                printf("\n   문자: '%c'", key);
            }
            else { // 제어 문자
                switch (key) {
                case 8:  printf(" (Backspace)"); break;
                case 9:  printf(" (Tab)"); break;
                case 10: printf(" (Line Feed)"); break;
                case 13: printf(" (Enter)"); break;
                case 32: printf(" (Space)"); break;
                default: printf(" (제어 문자)"); break;
                }
            }

            // Ctrl 조합키 확인
            if (key >= 1 && key <= 26 && key != 9 && key != 10 && key != 13) {
                printf(" [Ctrl+%c]", 'A' + key - 1);
            }

            printf("\n\n");
        }
    }

    printf("\n프로그램을 종료합니다. 아무 키나 누르세요...");
    _getch();

    return 0;
}

