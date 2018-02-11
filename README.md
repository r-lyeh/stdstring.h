# stdstring.h
C string utils library (STB style, header-only). Features:
- String expression evaluator (`streval`)
- String formatters (to heap buffers) (`strcpyf*`, `strcatf*`)
- String formatters (to temporary buffers) (`strf*`)
- String fuzzy search (`strscore`, `strfuzzy`)
- String regular expression (`strregex [c?^$*]`)
- String 64-bit hashing (both compile-time and runtime) (`strhash`)
- String interning (quarks) (`strput`, `strget`)
- String matching (`strsub`, `strfindl`, `strfindr`, `strbegin`, `strend`, `strmatch`, `streq`, `streqi`)
- String splitting (with and without allocations) (`strsplit`, `strchop`, `strjoin`)
- String options parsing (`stropt`, `stropti`, `stroptf`)
- String trim utils (`strdel`, `strtrimws`, `strtrimblf/bff`, `strtrimrlfe/ffe`)
- String transform utils (`strrepl`, `strremap`, `strlower`, `strupper`, `strrev`)
- String normalization utils (`strnorm`)
- String conversion utils (`strint`, `strhuman`, `strrobot`)
- String unicode utils (`strutf8`, `strutf32`, `strwiden`)
- [Documentation](https://rawgit.com/r-lyeh/stdstring.h/master/stdstring.h.html).

# Homepage
- https://github.com/r-lyeh/stdstring.h

# Changelog
- 2018.1 (v1.0.4): Fix API() macro; Add new transform utils; Rename a few functions.
- 2018.1 (v1.0.3): Add `strnorm()`, `strjoin()`. Fix `strcpyf()`.
- 2018.1 (v1.0.2): Add `stropt*()` options parser.
- 2018.1 (v1.0.1): Fix wrong version of strcatf() in first commit. Cosmetics.
- 2018.1 (v1.0.0): Initial release.

# Credits
- Using Rob Pike's regular expression (apparently public domain).
- Using Sam Hocevar's preprocessor trick (apparently public domain).
- Using Bob Stout's transform utils (public domain).
- Using Sean Barrett and Jeff Roberts' string formatters (unlicensed).
- Using Werner Stoop's expression evaluator (unlicensed).
- Using Dimitri Diakopoulos' unicode stuff (unlicensed).

# License
- rlyeh, unlicensed (~public domain).
