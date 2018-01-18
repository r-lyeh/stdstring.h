// ## replace substring in a string
// - rlyeh, public domain.

#include <assert.h>

HEAP char *strrepl(char **string, const char *target, const char *replace) { $
    assert( string );
    char HEAP *buf = 0, *aux = *string;
    for( int tgtlen = strlen(target); tgtlen && aux[0]; ) {
        char *found = strstr(aux, target);
        if( found ) {
            strcatf(&buf, "%.*s%s", (int)(found - aux), aux, replace);
            aux += (found - aux) + tgtlen;
        } else {
            strcatf(&buf, "%s", aux);
            break;
        }
    }
    if( buf ) {
        strcpyf(string, "%s", buf);
        FREE( buf );
    }
    return *string;
}

#ifdef REPLACEDEMO
#include <stdio.h>
int main() {
      #define test(a,b,eq) do { \
        char *buf = strcpyf(0, "%s", "mary has a little lamb little lamb"); \
        puts(strrepl(&buf, a, b)); \
        assert( 0 == strcmp(eq, buf) ); \
        free(buf); \
      } while(0)
      test("little" /*->*/, "little", /*==*/ "mary has a little lamb little lamb");
      test("big"    /*->*/, "little", /*==*/ "mary has a little lamb little lamb");
      test("little" /*->*/, "big",    /*==*/ "mary has a big lamb big lamb");
      test("little "/*->*/, "",       /*==*/ "mary has a lamb lamb");
      test(""       /*->*/, "little", /*==*/ "mary has a little lamb little lamb");
}
#endif
