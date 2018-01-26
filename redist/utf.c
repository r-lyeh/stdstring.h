// ## utf8 and unicode
// Based on code by @ddiakopoulos (unlicensed).
// - rlyeh, public domain.

uint32_t strutf32(INOUT const char **p) { $
    if( (**p & 0x80) == 0x00 ) {
        int a = *((*p)++);
        return a;
    }
    if( (**p & 0xe0) == 0xc0 ) {
        int a = *((*p)++) & 0x1f;
        int b = *((*p)++) & 0x3f;
        return (a << 6) | b;
    }
    if( (**p & 0xf0) == 0xe0 ) {
        int a = *((*p)++) & 0x0f;
        int b = *((*p)++) & 0x3f;
        int c = *((*p)++) & 0x3f;
        return (a << 12) | (b << 6) | c;
    }
    if( (**p & 0xf8) == 0xf0 ) {
        int a = *((*p)++) & 0x07;
        int b = *((*p)++) & 0x3f;
        int c = *((*p)++) & 0x3f;
        int d = *((*p)++) & 0x3f;
        return (a << 18) | (b << 12) | (c << 8) | d;
    }
    return 0;
}
static builtin(thread) uint8_t utf[8] = {0};
TEMP char *strutf8(uint32_t cp) { $
    int n = 0;
    /**/ if( cp <        0x80 ) n = 1;
    else if( cp <       0x800 ) n = 2;
    else if( cp <     0x10000 ) n = 3;
    else if( cp <    0x200000 ) n = 4;
    else if( cp <   0x4000000 ) n = 5;
    else if( cp <= 0x7fffffff ) n = 6;
    switch (n) {
        case 6: utf[5] = 0x80 | (cp & 0x3f); cp = (cp >> 6) | 0x4000000;
        case 5: utf[4] = 0x80 | (cp & 0x3f); cp = (cp >> 6) | 0x200000;
        case 4: utf[3] = 0x80 | (cp & 0x3f); cp = (cp >> 6) | 0x10000;
        case 3: utf[2] = 0x80 | (cp & 0x3f); cp = (cp >> 6) | 0x800;
        case 2: utf[1] = 0x80 | (cp & 0x3f); cp = (cp >> 6) | 0xc0;
        case 1: utf[0] = cp; default:;
    }
    return utf[n] = '\0', (char *)utf;
}

#ifdef _WIN32
#include <shlobj.h>
TEMP wchar_t *strwiden(const char *utf8) { $ // wide strings (windows only)
    static builtin(thread) char *buf = 0;
    int needed = 2 * MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    buf = REALLOC( buf, needed + 1 ); buf[needed] = 0;
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, (void*)buf, needed);
    return (wchar_t *)buf;
}
#endif

#ifdef UTFDEMO
#include <assert.h>
int main() {
    const char *text = "私 は ガ";
    const char *copy = text;
    assert( strutf32(&copy) == 31169 );
    assert( strutf32(&copy) == 32 );
    assert( strutf32(&copy) == 12399 );
    assert( strutf32(&copy) == 32 );
    assert( strutf32(&copy) == 12460 );
    assert( strutf32(&copy) == 0 );
#ifdef _WIN32
    #pragma comment(lib,"user32.lib")
    MessageBoxW(0, strwiden(text), L"Unicode", 0);
#endif
    assert(~puts("Ok"));
}
#endif
