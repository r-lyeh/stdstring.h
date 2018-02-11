// ## string interning (quarks)
// - rlyeh, public domain.

#include <stdint.h>
#include <assert.h>

static builtin(thread) int quarklen = 0, quarkcap = 0;
static builtin(thread) char *quarks = 0;

int strput( const char *string ) { $
    if( !quarks ) {
        // init buffer on first time
        quarks = (char*)REALLOC( quarks, (1+1) );
        quarkcap += 1;
        // copy null string
        quarks[0] = 0;
        quarklen += 1;
        quarkcap -= 1;
    }
    if( string && string[0] ) {
        int len = strlen(string)+1;
        if( quarkcap < len ) {
            int extend = (int)(len * 1.5f); // 2.33f
            // printf("alloc += %d\n", extend);
            quarks = (char*)REALLOC( quarks, quarklen + extend );
            quarkcap += extend;
        }
        memcpy( quarks + quarklen, string, len );
        quarklen += len;
        quarkcap -= len;
        // printf("%d/%d\n", quarklen, quarklen+quarkcap);
        return quarklen - len;
    }
    return 0;
}
const char *strget( int key ) {
    assert( quarks );
    return quarks + key;
}

#ifdef INTERNDEMO
#include <stdio.h>
#include <assert.h>
int main() {
    assert( !strput(NULL) ); // quark #0, couldnt intern null string
    assert( !strput("") );   // quark #0, can intern empty string
    assert( !strget(0)[0] ); // empty string for quark #0

    int q1 = strput("Hello");  // -> quark #1
    int q2 = strput("cruel");  // -> quark #2
    int q3 = strput("world."); // -> quark #3
    //printf("%d/%d\n", quarklen, quarklen+quarkcap);

    char buf[256];
    sprintf(buf, "%s %s %s", strget(q1), strget(q2), strget(q3));
    assert( !strcmp("Hello cruel world.", buf) );

    assert(~puts("Ok"));
}
#endif
