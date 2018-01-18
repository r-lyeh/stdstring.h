// ## string conversion unit utils
// - rlyeh, public domain.

#include <string.h>
#include <stdlib.h>

int64_t strint( const char *string ) { $
    int64_t v = 0, n = 1;
    if( string ) {
        while( *string == '-' ) n *= -1, string++;
        while( *string >= '0' && *string <= '9') v = (v * 10) + *string++ - '0';
    }
    return n * v;
}

static builtin(thread) char strhuman_buf[8] = {0};
TEMP char *strhuman(uint64_t number) { $
    int base = 1000; // ideally 1000 for units, 1024 for bits (conversion: 0.9765625)
    const char prefixes[] = " KMGTPEZY";
    const char* prefixp = prefixes;
    uint64_t i = number, d = 0;
    while( (i > base) && *prefixp++ ) {
        d = (i % base) / 10, i /= base;
    }
    if (d > 0) strsnprintf( strhuman_buf, sizeof(strhuman_buf), "%llu.%llu%c", i,d, *prefixp );
    else       strsnprintf( strhuman_buf, sizeof(strhuman_buf), "%llu%c", i, *prefixp );
    return strhuman_buf;
}

uint64_t strrobot(const char *string) { $
    int base = 1000; // ideally 1000 for units, 1024 for bits (conversion: 0.9765625)
    size_t sz = 1, mul = 0;
    char *pend;
    double num = strtod(string, &pend); sz = pend - string;
    while( string[sz] && string[sz] == ' ' ) sz++;
    switch( string[sz] ) {
        default:                   mul = 0;
        break; case 'K': case 'k': mul = 1;
        break; case 'M': case 'm': mul = 2;
        break; case 'G': case 'g': mul = 3;
        break; case 'T': case 't': mul = 4;
        break; case 'P': case 'p': mul = 5;
        break; case 'E': case 'e': mul = 6; // may overflow
        break; case 'Z': case 'z': mul = 7; // may overflow
        break; case 'Y': case 'y': mul = 8; // may overflow
    }
    while( mul-- ) if( num * base < num ) return 0; else num *= base;
    return num;
}

#ifdef CONVERSIONDEMO
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main() {
    // string to integer (atoi)
    assert( strint( "-120" ) == -120 );
    // safe substring access (forward)
    assert(!strcmp(strsub( "Hello", 0), "Hello"));
    assert(!strcmp(strsub( "Hello", 1), "ello"));
    assert(!strcmp(strsub( "Hello", 2), "llo"));
    assert(!strcmp(strsub( "Hello", 3), "lo"));
    assert(!strcmp(strsub( "Hello", 4), "o"));
    assert(!strcmp(strsub( "Hello", 5), "Hello"));
    // safe substring access (backward)
    assert(!strcmp(strsub( "Hello", 0), "Hello"));
    assert(!strcmp(strsub( "Hello",-1), "o"));
    assert(!strcmp(strsub( "Hello",-2), "lo"));
    assert(!strcmp(strsub( "Hello",-3), "llo"));
    assert(!strcmp(strsub( "Hello",-4), "ello"));
    assert(!strcmp(strsub( "Hello",-5), "Hello"));
    // human<-->robot conversion
    assert(!strcmp(strhuman(120000),"120K"));
    assert( strrobot("1435.23Gb") == 1435230000000ULL );
    //
    assert(~puts("Ok"));
}
#endif
