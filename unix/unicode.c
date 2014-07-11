#include <stdio.h>
#include <wchar.h>

int main(void) {
    wchar_t ok[] = L"\xE2\x96\xa0";
    wprintf(L"%ls\n", ok);
    return 0;
}
