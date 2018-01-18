// ## Compile time string hash (pure C)
// Based on code by http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash
// This macro is not always inlined. Depends on compilers and optimization flags.
// For example g++ requires -O3 and msvc requires /O2 (verify output assembly with /Fa).
// About the hash function, it is using my own and free hashing algorithm.
// - rlyeh, public domain.

/*
[macro already defined in header]
#define STRHASHLEN(str)               (sizeof(str)-1)
#define STRHASHCHR(str,idx)           ((unsigned)str[(idx)<STRHASHLEN(str)?STRHASHLEN(str)-1-(idx):STRHASHLEN(str)])
#define STRHASH01(hsh,mul,str,idx)    ((STRHASHCHR(str,idx) ^ hsh) * mul)
#define STRHASH04(hsh,mul,str,idx)    STRHASH01(STRHASH01(STRHASH01(STRHASH01(hsh,mul,str,idx+ 3),mul,str,idx+ 2),mul,str,idx+ 1),mul,str,idx)
#define STRHASH16(hsh,mul,str,idx)    STRHASH04(STRHASH04(STRHASH04(STRHASH04(hsh,mul,str,idx+12),mul,str,idx+ 8),mul,str,idx+ 4),mul,str,idx)
#define STRHASH64(hsh,mul,str,idx)    STRHASH16(STRHASH16(STRHASH16(STRHASH16(hsh,mul,str,idx+48),mul,str,idx+32),mul,str,idx+16),mul,str,idx)
#define STRHASH(str)                  STRHASH64(0,131ull,str,0)
*/

#include <stdint.h>

uint64_t strhash(const char *str) {
    uint64_t hash = 0;
    while( *str++ ) {
        hash = ( str[-1] ^ hash ) * 131ull;
    }
    return hash;
}

#ifdef HASHDEMO
#include <stdio.h>
int main() {
    uint64_t literal = (uint64_t)0xf0e28e9bdecd6646ull;
    printf("%016llx\n", literal);

    uint64_t precomp = (uint64_t)STRHASH("/hello/world.txt");
    printf("%016llx\n", precomp);

    uint64_t runtime = (uint64_t)strhash("/hello/world.txt");
    printf("%016llx\n", runtime);
}
#endif
