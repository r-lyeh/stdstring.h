// # string matching ##########################################################
// - rlyeh, public domain.

#include <string.h>
#include <stdlib.h>
#include <assert.h>

const char *strsub( const char *str, int pos ) { $
    int size = strlen(str);
    pos = pos && size ? (pos > 0 ? pos % size : size-1 + ((pos+1) % size)) : 0;
    return str + pos;
}

const char* strfindl(const char *text, const char *substring) { $
    const char *found = strstr( text, substring );
    return found ? found : text + strlen(text);
}
const char* strfindr(const char *text, const char *substring) { $
    char *found = 0;
    while(1) {
        char *found2 = strstr(text, substring);
        if( !found2 ) break;
        found = found2;
        text = found2 + 1;
    }
    return found ? found : text + strlen(text);
}

bool strbegin( const char *text, const char *substring ) { $
    // also, return strncmp(string, substr, strlen(substr)) == 0;
    int s1 = strlen(text), s2 = strlen(substring);
    return s1 >= s2 ? 0 == memcmp( &text[       0 ], substring, s2 ) : false;
}
bool strend( const char *text, const char *substring ) { $
    int s1 = strlen(text), s2 = strlen(substring);
    return s1 >= s2 ? 0 == memcmp( &text[ s1 - s2 ], substring, s2 ) : false;
}

bool streq( const char *string, const char *substr ) { $
    return !strcmp( string, substr );
}
bool streqi( const char *string, const char *substr ) { $
    while( *string && *substr ) {
        int eqi = (*string++ | 32) == (*substr++ | 32);
        if( !eqi ) return 0;
    }
    return *string == 0 && *substr == 0;
}

#ifdef MATCHDEMO
#include <stdio.h>
int main() {
    assert( streq("hello", "hello") );
    assert(!streq("HELLO", "hello") );

    assert( streqi("hello", "hello") );
    assert( streqi("HELLO", "hello") );

    assert( strbegin("hello", "hell") );
    assert(!strbegin("hell", "hello") );
    assert( strend("hello", "llo") );

    assert(~puts("Ok"));
}
#endif
