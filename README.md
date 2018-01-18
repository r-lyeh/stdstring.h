# stdstring.h
C string library (STB style, header-only). Features:
- String expression evaluator (`streval`)
- String formatters (to heap buffers) (`strcpyf*`, `strcatf*`)
- String formatters (to temporary buffers) (`strf*`)
- String fuzzy search (`strscore`, `strfuzzy`)
- String regular expression (`strregex [c?^$*]`)
- String 64-bit hashing (both compile-time and runtime) (`strhash`)
- String interning (quarks) (`intern`, `string`)
- String matching (`strsub`, `strfindl`, `strfindr`, `strbegin`, `strend`, `strmatch`, `streq`, `streqi`)
- String splitting (with and without allocations) (`strsplit`, `strchop`, `strjoin`)
- String options parsing (`stropt`, `stropti`, `stroptf`)
- String transform utils (`strrepl`, `strremap`, `strlower`, `strtrimlb/e`, `strtrimrb/e`)
- String normalization (`strnorm`)
- String conversion utils (`strint`, `strhuman`, `strrobot`)
- String unicode utils (`strutf8`, `strutf32`, `strwiden`)
- [Documentation](https://rawgit.com/r-lyeh/stdstring.h/master/stdstring.h.html).

# Homepage
- https://github.com/r-lyeh/stdstring.h

# Credits
- Using Rob Pike's regular expression (apparently public domain).
- Using Sam Hocevar's preprocessor trick (apparently public domain).
- Using Sean Barrett and Jeff Roberts' string formatters (unlicensed).
- Using Werner Stoop's expression evaluator (unlicensed).
- Using Dimitri Diakopoulos' unicode stuff (unlicensed).

# License
- Unlicensed (~public domain).
