#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
#include <conio.h>
//
//int main(void)
//{
//    clock_t initial_clock = clock();   // �ʱ� clock
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
//            clock_t current_clock = clock();   // ���� clock
//            if (current_clock - initial_clock >= 1000)   // 1�� ���
//            {
//                i++;
//                system("cls");
//                printf("%d ", i);
//                initial_clock = clock();   // ���� clock�� �ʱ� clock���� ����
//            }
//        }
//        if (_kbhit())   // Ű �Է��� �־��ٸ�
//        {
//            if (_getch() == 'p')   // 'p' Ű���
//                go = (go + 1) % 2;   // ����(0)/�簳(1) ��ȯ
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
//	// ����Ű�� ��� 0 �Ǵ� 224�� ���� ���� �Էµ�
//	ch = 256 + _getch();
//	// �� ������ �ش� ����Ű�� ���� 72(Up),
//	// 80(Down), 75(Left), 77(Right) ���� �Էµ�
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

    printf("=== Ű���� �� ��� ���α׷� ===\n");
    printf("Ű�� ������ �ش� Ű�� ���� ����մϴ�.\n");
    printf("ESC Ű�� ������ ���α׷��� ����˴ϴ�.\n");
    printf("=====================================\n\n");

    while (1) {
        printf("[%d] Ű�� ��������: ", ++count);

        key = _getch(); // Ű �Է� �ޱ� (ȭ�鿡 ǥ�õ��� ����)

        if (key == 27) { // ESC Ű (ASCII 27)
            printf("\nESC Ű�� ���Ƚ��ϴ�. ���α׷��� �����մϴ�.\n");
            break;
        }
        else if (key == 0 || key == 224) { // Ȯ�� Ű (Ư��Ű)
            int extended_key = _getch(); // Ȯ�� Ű�ڵ� �б�
            printf("\n   Ȯ�� Ű ����!");
            printf("\n   ù ��° ��: %d", key);
            printf("\n   �� ��° ��: %d", extended_key);

            // �ֿ� Ư��Ű �̸� ���
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
            case 72: printf(" (���� ȭ��ǥ)"); break;
            case 80: printf(" (�Ʒ��� ȭ��ǥ)"); break;
            case 75: printf(" (���� ȭ��ǥ)"); break;
            case 77: printf(" (������ ȭ��ǥ)"); break;
            case 71: printf(" (Home)"); break;
            case 79: printf(" (End)"); break;
            case 73: printf(" (Page Up)"); break;
            case 81: printf(" (Page Down)"); break;
            case 82: printf(" (Insert)"); break;
            case 83: printf(" (Delete)"); break;
            default: printf(" (�� �� ���� Ư��Ű)"); break;
            }
            printf("\n\n");
        }
        else { // �Ϲ� Ű
            printf("\n   �Ϲ� Ű ����!");
            printf("\n   ASCII ��: %d", key);

            if (key >= 32 && key <= 126) { // ��� ������ ����
                printf("\n   ����: '%c'", key);
            }
            else { // ���� ����
                switch (key) {
                case 8:  printf(" (Backspace)"); break;
                case 9:  printf(" (Tab)"); break;
                case 10: printf(" (Line Feed)"); break;
                case 13: printf(" (Enter)"); break;
                case 32: printf(" (Space)"); break;
                default: printf(" (���� ����)"); break;
                }
            }

            // Ctrl ����Ű Ȯ��
            if (key >= 1 && key <= 26 && key != 9 && key != 10 && key != 13) {
                printf(" [Ctrl+%c]", 'A' + key - 1);
            }

            printf("\n\n");
        }
    }

    printf("\n���α׷��� �����մϴ�. �ƹ� Ű�� ��������...");
    _getch();

    return 0;
}

