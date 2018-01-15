// ## string transform utils
// - rlyeh, public domain.

#include <string.h>
#include <stdlib.h>

char* strtriml(char *string, const char *substring) { $
    char *found = strstr(string, substring);
    if( found ) {
        int L = strlen(substring);
        memmove(string, found+L, strlen(string) - L);
    }
    return string;
}
char* strtrimr(char *string, const char *substring) { $
    char *found = (char*)strfindr(string, substring);
    if( found ) found[0] = '\0';
    return string;
}
char *strlower(char *string) { $
    for( char *s = string; *s; *s++ ) {
        if( *s >= 'A' && *s <= 'Z' ) *s = *s - 'A' + 'a'; // *s &= 32;
    }
    return string;
}

#ifdef TRANSFORMDEMO
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main() {
    char buf1[] = "[[helloworld--helloworld]]";
    assert( 0 == strcmp( "--helloworld]]", strtriml(buf1, "world")) );
    assert( 0 == strcmp( "--",             strtrimr(buf1, "hello")) );
    assert(~puts("Ok"));
}
#endif
