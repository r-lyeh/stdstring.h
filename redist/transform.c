// ## string transform utils
// - rlyeh, public domain.

#include <string.h>
#include <stdlib.h>

char* strtrimlb(char *string, const char *substring) { $
    char *found = strstr(string, substring);
    if( found ) {
        int L = strlen(substring);
        memmove(string, found+L, strlen(string) - L);
    }
    return string;
}
char* strtrimle(char *string, const char *substring) { $
    ((char *)strfindl(string, substring))[0] = 0;
    return string;
}
char* strtrimrb(char *string, const char *substring) { $
    const char *found = strfindr(string, substring);
    int L = strlen(substring);
    memmove( string, found + L, strlen(found) - L + 1);
    return string;
}
char* strtrimre(char *string, const char *substring) { $
    ((char *)strfindr(string, substring))[0] = 0;
    return string;
}
char *strlower(char *string) { $
    for( char *s = string; *s; *s++ ) {
        if( *s >= 'A' && *s <= 'Z' ) *s = *s - 'A' + 'a'; // *s &= 32;
    }
    return string;
}
char *strremap( INOUT char *string, const char srcs[], const char dsts[] ) { $
    uint8_t map[256] =
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
    "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f"
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f"
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f"
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f"
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f"
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
    "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f"
    "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f"
    "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf"
    "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf"
    "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf"
    "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf"
    "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef"
    "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";
    for( int i = 0; srcs[i]; ++i) map[(uint8_t)srcs[i]] = dsts[i];
    for( int i = 0; string[i]; ++i ) string[i] = map[(uint8_t)string[i]];
    return string;
}

#ifdef TRANSFORMDEMO
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main() {
    {
        char buf1[] = "hellohelloworldworld";
        char buf2[] = "hellohelloworldworld";
        char buf3[] = "hellohelloworldworld";
        char buf4[] = "hellohelloworldworld";
        strtrimlb(buf1, "ell"); puts(buf1); assert( 0 == strcmp( buf1, "ohelloworldworld") );
        strtrimle(buf2, "ell"); puts(buf2); assert( 0 == strcmp( buf2, "h") );
        strtrimrb(buf3, "ell"); puts(buf3); assert( 0 == strcmp( buf3, "oworldworld") );
        strtrimre(buf4, "ell"); puts(buf4); assert( 0 == strcmp( buf4, "helloh") );
    }
    char remap[] = "H3110 W0r1d";
    assert( 0 == strcmp( "Hello World", strremap(remap, "310", "elo")));
    assert(~puts("Ok"));
}
#endif
