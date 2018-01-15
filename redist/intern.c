// ## string interning (quarks)
// - rlyeh, public domain.

#include <stdint.h>
#include <assert.h>

static builtin(thread) int quarklen = 0, quarkcap = 0;
static builtin(thread) char *quarks = 0;

int intern( const char *string ) { $
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
const char *string( int key ) {
    assert( quarks );
    return quarks + key;
}

#ifdef INTERNDEMO
#include <stdio.h>
#include <assert.h>
int main() {
    assert( !intern(NULL) ); // quark #0, couldnt intern null string
    assert( !intern("") );   // quark #0, can intern empty string
    assert( !string(0)[0] ); // empty string for quark #0

    int q1 = intern("Hello");  // -> quark #1
    int q2 = intern("cruel");  // -> quark #2
    int q3 = intern("world."); // -> quark #3
    //printf("%d/%d\n", quarklen, quarklen+quarkcap);

    char buf[256];
    sprintf(buf, "%s %s %s", string(q1), string(q2), string(q3));
    assert( !strcmp("Hello cruel world.", buf) );

    assert(~puts("Ok"));
}
#endif
