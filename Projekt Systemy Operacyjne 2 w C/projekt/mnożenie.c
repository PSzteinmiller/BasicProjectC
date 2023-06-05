#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void multiply(int value1, int value2);

int main() {

    int a;
    int b;


    while (1) {
        printf(" a= ");
        if (scanf("%d", &a) == 1) {
            break;
        }
        while (getchar() != '\n');  // clear input buffer
        printf("Invalid input, please try again.\n");
    }

    while (1) {
        printf("b= ");
        if (scanf("%d", &b) == 1) {
            break;
        }
        while (getchar() != '\n');  // clear input buffer
        printf("Invalid input, please try again.\n");
    }


    if (a < 0 || b < 0) {
        printf("non-negative values expected");
        return 0;
    }

    int value1 = a > b ? a : b;
    int value2 = b < a ? b : a;

    multiply(value1, value2);
}

//funkcja pomocnicza do wypisywania podanego znaku dana ilosc razy

void printNChars(int n, char c) {
    while (n-- > 0)
        putchar(c);

}

//funkcja pomocnicza do wypisywania podanej ilosci spacji

void printNSpaces(int n) {
    printNChars(n, ' ');

}


void multiply(int value1, int value2) {

    int sizeValue1;
    int sizeValue2;

    long long result = (long) value1 * value2;

    sizeValue1 = (int) log10(value1) + 1;
    sizeValue2 = (int) log10(value2) + 1;

    int sizeResult = (int) log10(result) + 1;

    if (value1 == 0 && value2 == 0) {
        printf(" %d\n", value1);
        putchar('*');
        putchar(' ');
        printf("%d", value2);
        printf("\n");
        printNChars(3, '-');
        printf("\n");
        printNChars(2, ' ');
        printf("%lld", result);
    }

    if (value1 == 0 || value2 == 0) {
        printf("%*d\n", sizeValue1, value1);
        putchar('*');
        putchar(' ');
        printf("%d", value2);
        printf("\n");
        printNChars(3, '-');
        printf("\n");
        printNChars(2, ' ');
        printf("%lld", result);
    } else {

        char val1tab[sizeValue1];
        int temp = value1;

        // do tablicy wartosci liczby a wrzucam poszczegolne czesci liczby np. dla 372 to tab[2,7,3]
        
        for (int i = 0; i < sizeValue1; i++) {
            val1tab[i] = temp % 10;
            temp = temp / 10;
        }

        // do tablicy wartosci liczby b wrzucam poszczegolne czesci liczby np. dla 57 to tab[7,5]
        
        temp = value2;
        char val2tab[sizeValue2];
        for (int i = 0; i < sizeValue2; i++) {
            val2tab[i] = temp % 10;
            temp = temp / 10;
        }

        //pomocnicza zmienna przyjmujaca dlugosc pierwszej (dluzszej) liczby
        
        int maxLen = sizeValue1;

        //zapisywane sa w niej przeniesienia
        
        char carries[sizeValue2][maxLen];

        for (int i = 0; i < sizeValue2; ++i) {
            for (int j = 0; j < maxLen; ++j) {
                carries[i][j] = 0;
            }
        }

        //sekcja przeniesien

        //wyliczanie przeniesien
        for (int i = 0; i < sizeValue2; i++) {
            for (int j = 0; j < sizeValue1; j++) {
                int tempRes = val2tab[i] * val1tab[j];
                //zapisujemy do carries nasze przeniesienia
                carries[i][maxLen - j - 1] = (tempRes + (j == 0 ? 0 : carries[i][maxLen - j])) / 10;
            }
        }


        printf("\n");

        //dlugosc pauz oraz odstepow od poczatku linii
        
        int minusCount = 2 + sizeResult;
        int minusCountAfterMultiplication = maxLen + 2;

        int k = minusCount - minusCountAfterMultiplication;



        //petla ktora wypisuje spacje przed przed przeniesieniem, a nastepnie cale przeniesienie
        for (int i = sizeValue2 - 1; i >= 0; i--) {
            printNSpaces(k + 1);
            for (int j = 0; j < maxLen; ++j) {
                if (carries[i][j] == 0)putchar(' ');
                else printf("%hd", carries[i][j]);
            }
            putchar('\n');
        }

        // input a i b

        printNSpaces(k + 2);
        printf("%*d\n", maxLen, value1);
        printNSpaces(k);
        printf("* %*d\n", maxLen, value2);

        //pauzy po mnozeniu
        printNSpaces(k);

        printNChars(minusCountAfterMultiplication, '-');

        printf("\n");


        int extraSpaces = 0;
        //porownujemy ze soba dlugosci najdluzszej liczby oraz ostatniej liczby z dodawania, zeby poprawnie ustawic odstępy - extraSpaces
        if ((int) (log10(val2tab[sizeValue2 - 1] * value1) + 1) == sizeValue1) {
            extraSpaces = -1;
        }


        //wypisywanie liczb potrzebnych do dodawania
        for (int i = 0; i < sizeValue2; ++i) {
            if (i == sizeValue2 - 1) printf("+ ");
            else printNSpaces(2);
            printNSpaces(sizeValue2 - i - 1 + extraSpaces);
            if (i != sizeValue2 - 1) {
                printf("%*d\n", maxLen + 1, value1 * val2tab[i]);
            } else {
                printf("%d\n", value1 * val2tab[i]);
            }
        }

        //pauzy przed wynikiem
        for (int i = 0; i < minusCount; ++i) {
            putchar('-');
        }
        putchar('\n');

        //wynik
        printf("%*lld\n", minusCount, result);
    }

}
