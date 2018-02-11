// ## string transform utils
// - rlyeh, public domain.

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* strtrimbff(char *string, const char *substring) { $
    char *found = strstr(string, substring);
    if( found ) {
        int L = strlen(substring);
        memmove(string, found+L, strlen(string) - L);
    }
    return string;
}
char* strtrimffe(char *string, const char *substring) { $
    ((char *)strfindl(string, substring))[0] = 0;
    return string;
}
char* strtrimblf(char *string, const char *substring) { $
    const char *found = strfindr(string, substring);
    int L = strlen(substring);
    memmove( string, found + L, strlen(found) - L + 1);
    return string;
}
char* strtrimlfe(char *string, const char *substring) { $
    ((char *)strfindr(string, substring))[0] = 0;
    return string;
}
char *strtrimws(char *str) {
    char *ibuf, *obuf;
    if( str ) {
        for( ibuf = obuf = str; *ibuf; ) {
            while( *ibuf && isspace(*ibuf)  )  (ibuf++);
            if(    *ibuf && obuf != str     ) *(obuf++) = ' ';
            while( *ibuf && !isspace(*ibuf) ) *(obuf++) = *(ibuf++);
        }
        *obuf = 0;
    }
    return str;
}

#ifdef TRIMDEMO
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main() {
    {
        char bufws[] = "   Hello  world  ";
        assert( 0 == strcmp("Hello world", strtrimws(bufws)));

        char buf1[] = "hellohelloworldworld";
        char buf2[] = "hellohelloworldworld";
        char buf3[] = "hellohelloworldworld";
        char buf4[] = "hellohelloworldworld";
        strtrimbff(buf1, "ell"); puts(buf1); assert( 0 == strcmp( buf1, "ohelloworldworld") );
        strtrimffe(buf2, "ell"); puts(buf2); assert( 0 == strcmp( buf2, "h") );
        strtrimblf(buf3, "ell"); puts(buf3); assert( 0 == strcmp( buf3, "oworldworld") );
        strtrimlfe(buf4, "ell"); puts(buf4); assert( 0 == strcmp( buf4, "helloh") );
    }
    assert(~puts("Ok"));
}
#endif
