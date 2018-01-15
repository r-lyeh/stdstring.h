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
- String splitting (with and without allocations) (`strsplit`, `strchop`)
- String transform utils (`strrepl`, `strtriml`, `strtrimr`, `strlower`)
- String conversion utils (`strint`, `strhuman`, `strrobot`)
- String unicode utils (`strutf8`, `strutf32`, `strwiden`)
- [Documentation](https://rawgit.com/r-lyeh/stdstring.h/master/stdstring.h.html).

# Homepage
- https://github.com/r-lyeh/stdstring.h

# Changelog
- 2018.1 (v1.0.0): *Initial release*

# License
- Public domain (~unlicensed).
