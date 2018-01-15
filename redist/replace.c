// ## replace substring in a string
// - rlyeh, public domain.

HEAP char *strreplace(const char *string, const char *source, const char *target) { $
    HEAP char *buf = 0;
    char *found;
    const char *copy = string;
    for( int srclen = strlen(source); srclen && string[0]; ) {
        if( 0 != (found = strstr( string, source )) ) {
            strcatf(&buf, "%.*s%s", (int)(found - string), string, target);
            string += (found - string) + srclen;
        } else {
            strcatf(&buf, "%s", string);
            break;
        }
    }
    return buf ? buf : STRDUP( copy ); // strcatf( 0, "%s", copy );
}

#ifdef REPLACEDEMO
int main() {
      puts(strreplace("mary has a little lamb little lamb", "little", "little"));
      puts(strreplace("mary has a little lamb little lamb", "big", "big"));
      puts(strreplace("mary has a big lamb big lamb", "big", "little"));

      puts(strreplace("mary has a little lamb little lamb", "little", "big"));
      puts(strreplace("mary has a little lamb little lamb", "little ", ""));
      puts(strreplace("mary has a little lamb little lamb", "", "little"));
}
#endif
