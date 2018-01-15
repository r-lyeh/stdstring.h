// ## split strings into tokens
// - rlyeh, public domain.

#include <stdlib.h>
#include <string.h>
#include <assert.h>

HEAP char **strsplit( const char *string, const char *delimiters ) { $
    int len = sizeof(char *) * (strlen(string)/2+1+1), i = 0;
    char **res = (char **)CALLOC(1, len + strlen(string) + 1 );
    char *buf = strcpy( (char *)res + len, string );
    for( char *token = strtok(buf, delimiters); token; token = strtok(NULL, delimiters) ) {
        res[i++] = token;
    }
    return res;
}

int strchop( const char *string, const char *delimiters, int avail, const char **tokens ) { $
    assert( avail >= 4 && 0 == ( avail % 2 ) );
    for( avail /= 2; *string && avail-- > 0; ) {
        int n = strcspn( string += strspn(string, delimiters), delimiters );
        *tokens++ = (*tokens++ = (const char *)(uintptr_t)n) ? string : "";
        string += n;
    }
    return *tokens++ = 0, *tokens = 0, avail > 0;
}

#ifdef SPLITDEMO
#include <stdio.h>
int main() {
    // split input text into tokens. allocates once.
    char **tokens = strsplit("JAN,;,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC", ",;");
    for (int i = 0; tokens[i]; i++) {
        printf("[%s],", tokens[i]);
    }
    free( tokens );

    // split input text into tokens. does not allocate.
    const char *words[32] = {0};
    if( strchop( "There is a lady who's sure, all that glitter is gold...", " ,.", 32, words ) ) { // "$"
        for( int i = 0; words[i]; i += 2 ) {
            printf("[%.*s],", (int)(uintptr_t)words[i+0], words[i+1]);
        }
    }
}
#endif
