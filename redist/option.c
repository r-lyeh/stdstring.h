// # string options parsing ###################################################
// - rlyeh, public domain

const char *stropt( const char *defaults, const char *options_csv ) { $
    const char *tokens[128];
    if( strchop( options_csv, ",", 128, tokens ) ) {
        for( int t = 0; tokens[t]; t += 2 ) {
            int size = (int)(uintptr_t)tokens[t];
            const char *token = tokens[t+1];
            for( int i = 1; i < __argc; ++i ) {
                const char *kv = __argv[i];
                if( strlen(kv) >= size && !memcmp( kv, token, size ) ) {
                    kv += kv[size] == '=';
                    defaults = kv[size] ? kv+size : defaults;
                }
            }
        }
    }
    return defaults;
}

double stroptf( double defaults, const char *options_csv ) { $
    const char *s = stropt( 0, options_csv );
    if( !s ) return defaults;
    // evaluate expression, includes on/off and true/false tokens
    double v = streval( s );
    if( v != v ) return defaults;
    // skip digits and symbols
    char charset[] = "0123456789+-/*^()";
    s += strspn(s, charset);
    // si units
    double unit = 1.0;
    /**/ if( *s == 'n' ) unit = 1e-9;
    else if( *s == 'u' ) unit = 1e-6;
    else if( *s == 'm' ) unit = 1e-3;
    else if( *s == 'c' ) unit = 1e-2;
    else if( *s == 'd' ) unit = 1e-1;
    //   if( *s =='da' ) unit = 1e1;
    else if( *s == 'h' ) unit = 1e2;
    else if( *s == 'k' ) unit = 1e3;
    else if( *s == 'K' ) unit = 1e3; /*alias*/
    else if( *s == 'M' ) unit = 1e6;
    else if( *s == 'G' ) unit = 1e9;
    else if( *s == 'T' ) unit = 1e12;
    // digital information conversion to kibi, mebi, gibi, etc
    double conv = ( *s && s[1] == 'i' ? 1.024 : 1.0);
    return v * unit * conv;
}

int64_t stropti( int64_t defaults, const char *options_csv ) { $
    return (int64_t)stroptf( (double)defaults, options_csv );
}

#ifdef OPTIONDEMO
#include <stdio.h>
int main() {
    // showcase:
    // demo.exe
    // demo.exe --client=off --server=true --user=another@mail.com
    // demo.exe --port=1111 --distance=120km --time=2ms --bits=4Kib --health=(10+12)*10
    printf("cfg.user: %s\n",     stropt("your@mail.com", "-u,--user"));
    printf("cfg.port: %f\n",     stroptf(8080, "-p,--port"));
    printf("cfg.client: %f\n",   stroptf(1, "-c,--client"));
    printf("cfg.server: %f\n",   stroptf(0, "-s,--server"));
    printf("cfg.distance: %f\n", stroptf(0, "-d,--distance"));
    printf("cfg.time: %f\n",     stroptf(0, "-t,--time"));
    printf("cfg.bits: %f\n",     stroptf(0, "-b,--bits"));
    printf("cfg.health: %f\n",   stroptf(50, "-h,--health"));
}
#endif
