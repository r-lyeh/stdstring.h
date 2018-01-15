// ## rob pike's regexp match (apparently public domain).
// [ref] https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
// @todo: evaluate @kokke/tiny-regex-c instead.

static int reghere(const char *string, const char *re) {
    if( re[0] == '\0' ) return 1;
    if( re[1] == '*' ) return regstar(string, re+2, re[0]);
    if( re[0] == '$' && re[1] == '\0' ) return *string == '\0';
    if( *string!='\0' && (re[0]=='?' || re[0]==*string) ) return reghere(string+1, re+1);
    return 0;
}

static int regstar(const char *string, const char *re, int c) {
    do { /* a * matches zero or more instances */
        if( reghere(string, re) ) return 1;
    } while( *string != '\0' && (*string++ == c || c == '?') );
    return 0;
}

int strregex(const char *string, const char *re) {
    if( re[0] == '^' ) return reghere(string, re+1);
    do { /* must look even if string is empty */
        if( reghere(string, re) ) return 1;
    } while (*string++ != '\0');
    return 0;
}

#ifdef REGEXDEMO
#include <stdio.h>
int main() {
    printf("%d\n", strregex("hello123", "^hel?*$"));
}
#endif
