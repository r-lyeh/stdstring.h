#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

void include( const char *file ) {
    struct stat st = {0};
    if( stat(file, &st) < 0 ) {
        fprintf(stderr, "Warning: Cannot open '%s'\n", file);
        return;
    }
    char cmd[256] = {0};
#ifdef _WIN32
    sprintf( cmd, "type %s && echo.", file );
#else
    sprintf( cmd, "cat %s && echo $'\n'", file );
#endif
    system( cmd );
}

int main() {
    include("begin.c");
        include("sprintf.c");
        include("eval.c");
        include("regex.c");
        include("format.c");
        include("match.c");
        include("conversion.c");
        include("transform.c");
        include("replace.c");
        include("split.c");
        include("option.c");
        include("intern.c");
        include("fuzzy.c");
        include("utf.c");
        include("hash.c");
    include("end.c");
}
