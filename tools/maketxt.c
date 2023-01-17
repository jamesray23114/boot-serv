#include <wchar.h>
#include <stdio.h>

void writews(short* wstr, FILE* file) {

    char* str = (char*) wstr;
    int len = wcslen(wstr) * 2;

    for (int i = 0; i < len; i++)
    {
        fputc(str[i], file);
    }

}

int main()
{
    FILE* file = fopen("_build/test.txt", "w");

    short* str = u"hello world!";

    writews(str, file);

    fclose(file);
    return 0;
}