// ## C-style formatting
// - rlyeh, public domain.

#include <stdarg.h>

// Wrap vsnprintf into a statically allocated buffer. A bunch of buffers are
// handled internally so that nested calls are safe within reasonable limits.

static builtin(thread) int vl_index = 0;
static builtin(thread) char *vl_buffer[16] = {0};
TEMP char *strfv( const char *fmt, va_list lst ) { //$
    int idx = (++vl_index) % 16;
    int sz = 1 + strvsnprintf(0, 0, fmt, lst);
    vl_buffer[idx] = (char *)REALLOC( vl_buffer[idx], sz );
    strvsnprintf( vl_buffer[idx], sz, fmt, lst );
    return vl_buffer[idx];
}
TEMP char *strf( const char *fmt, ... ) { //$
    va_list lst;
    va_start(lst, fmt);
    char *rc = strfv(fmt, lst);
    va_end(lst);
    return rc;
}
HEAP char *strcpyfv( char **str, const char *fmt, va_list lst ) { //$
    TEMP char *buf = strfv( fmt, lst );
    if( str && *str ) {
        int len = strlen(buf) + 1;
        (*str) = (char*)REALLOC( str && (*str) ? (*str) : 0, len );
        memcpy( (*str), buf, len );
        return *str;
    } else {
        return str ? *str = STRDUP(buf) : STRDUP(buf);
    }
}
HEAP char *strcpyf( char **str, const char *fmt, ... ) { //$
    va_list lst;
    va_start(lst, fmt);
    char *rc = strcpyfv(str, fmt, lst);
    va_end(lst);
    return rc;
}
HEAP char *strcatfv( char **str, const char *fmt, va_list lst ) { //$
    TEMP char *buf = strfv( fmt, lst );
    if( str && *str ) {
        int l1 = strlen(*str), l2 = strlen(buf);
        (*str) = (char*)REALLOC( (*str), l1 + l2 + 1 );
        memcpy( (*str) + l1, buf, l2 + 1 );
        return *str;
    } else {
        return str ? *str = STRDUP(buf) : STRDUP(buf);
    }
}
HEAP char *strcatf( char **str, const char *fmt, ... ) { //$
    va_list lst;
    va_start(lst, fmt);
    HEAP char *rc = strcatfv(str, fmt, lst);
    va_end(lst);
    return rc;
}
