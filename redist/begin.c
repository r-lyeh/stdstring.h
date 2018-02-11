/// # String library
/// C string utils library (STB style, header-only). Features:
/// - String expression evaluator (`streval`)
/// - String formatters (to heap buffers) (`strcpyf*`, `strcatf*`)
/// - String formatters (to temporary buffers) (`strf*`)
/// - String fuzzy search (`strscore`, `strfuzzy`)
/// - String regular expression (`strregex [c?^$*]`)
/// - String 64-bit hashing (both compile-time and runtime) (`strhash`)
/// - String interning (quarks) (`strput`, `strget`)
/// - String matching (`strsub`, `strfindl`, `strfindr`, `strbegin`, `strend`, `strmatch`, `streq`, `streqi`)
/// - String splitting (with and without allocations) (`strsplit`, `strchop`, `strjoin`)
/// - String options parsing (`stropt`, `stropti`, `stroptf`)
/// - String trim utils (`strdel`, `strtrimws`, `strtrimblf/bff`, `strtrimrlfe/ffe`)
/// - String transform utils (`strrepl`, `strremap`, `strlower`, `strupper`, `strrev`)
/// - String normalization utils (`strnorm`)
/// - String conversion utils (`strint`, `strhuman`, `strrobot`)
/// - String unicode utils (`strutf8`, `strutf32`, `strwiden`)
/// - [Documentation](https://rawgit.com/r-lyeh/stdstring.h/master/stdstring.h.html).
/// 
/// # Homepage
/// - https://github.com/r-lyeh/stdstring.h
///
/// # Changelog
/// - 2018.1 (v1.0.4): Fix API() macro; Add new transform utils; Rename a few functions.
/// - 2018.1 (v1.0.3): Add `strnorm()`, `strjoin()`. Fix `strcpyf()`.
/// - 2018.1 (v1.0.2): Add `stropt*()` options parser.
/// - 2018.1 (v1.0.1): Fix wrong version of strcatf() in first commit. Cosmetics.
/// - 2018.1 (v1.0.0): Initial release.
///
/// # Credits
/// - Using Rob Pike's regular expression (apparently public domain).
/// - Using Sam Hocevar's preprocessor trick (apparently public domain).
/// - Using Bob Stout's transform utils (public domain).
/// - Using Sean Barrett and Jeff Roberts' string formatters (unlicensed).
/// - Using Werner Stoop's expression evaluator (unlicensed).
/// - Using Dimitri Diakopoulos' unicode stuff (unlicensed).
///
/// # License
/// - rlyeh, unlicensed (~public domain).
/// 

// API ------------------------------------------------------------------------

#ifdef API

API(string,

/// # API
/// ## String expression evaluator
/// - Evaluates a mathematical expression. Returns number value, or NaN if error.
/// - Note: To check for NaN use `isnan(ret)` or `bool error = (ret != ret);`
///<C
ABI      double        streval(const char *expression);

/// ## String fuzzy completion
/// - Compares two strings. Returns string matching score (higher is better).
/// - Fuzzy search a word into a list of given words. Returns best match or empty string (if none).
///<C
ABI      int           strscore(const char *string1, const char *string2);
ABI      const char *  strfuzzy(const char *string, int num, const char *words[]);

/// ## String regular expression
/// - Regular expression matching. returns non-zero if found.
///   - `c` matches any literal character c.
///   - `?` matches any single character.
///   - `^` matches the beginning of the input string.
///   - `$` matches the end of the input string.
///   - `*` matches zero or more occurrences of the previous character.
/// - Return true if string matches wildcard pattern expression (?*).
///<C
ABI      int           strregex(const char *string, const char *regex);
ABI      bool          strmatch(const char *string, const char *substring);

/// ## String hashing
/// - Runtime string hash. Returns 64-bit hash of given string.
/// - Compile-time string hash macro. Returns 64-bit hash of given string.
/// - Note: Macro requires code optimizations enabled (`-O3` for gcc, `/O2` for MSVC).
///<C
ABI      uint64_t      strhash(const char *string);
ABI      uint64_t      STRHASH(const char *string);

/// ## String interning dictionary (quarks)
/// - Insert string into dictionary (if not exists). Returns quark ID, or 0 if empty string.
/// - Retrieve previously interned string. ID#0 returns empty string always.
///<C
ABI      int           strput(const char *string);
ABI      const char *  strget(int quark);

/// ## String matching
/// - Extract substring from position. Negative positions are relative to end of string.
/// - Search substring from beginning (left). Returns end-of-string if not found.
/// - Search substring from end (right). Returns end-of-string if not found.
/// - Return true if string starts with substring.
/// - Return true if string ends with substring.
/// - Return true if strings are equal.
/// - Return true if strings are equal (case insensitive).
///<C
ABI      const char*   strsub  (const char *string, int position);
ABI      const char*   strfindl(const char *string, const char *substring);
ABI      const char*   strfindr(const char *string, const char *substring);
ABI      bool          strbegin(const char *string, const char *substring);
ABI      bool          strend  (const char *string, const char *substring);
ABI      bool          streq   (const char *string, const char *substring);
ABI      bool          streqi  (const char *string, const char *substring);

/// ## String normalization
/// - Normalize resource identificator. Normalized uris have deterministic string hashes.
///<C
ABI TEMP char *        strnorm (const char *uri);

/// ## String conversion utils
/// - Convert a string to integer.
/// - Convert number to human readable string (`12000000 -> 12M`)
/// - Convert human readable string to number (`12M -> 12000000`)
///<C
ABI      int64_t       strint  (const char *string);
ABI TEMP char*         strhuman(uint64_t number);
ABI      uint64_t      strrobot(const char *string);

/// ## String options parsing
/// - Parse argc/argv looking for comma-separated values. Returns matching string or `defaults`.
/// - Parse argc/argv looking for comma-separated values. Returns matching integer or `defaults`.
/// - Parse argc/argv looking for comma-separated values. Returns matching floating or `defaults`.
///<C
ABI      const char *  stropt (const char *defaults, const char *options_csv);
ABI      int64_t       stropti(int64_t defaults, const char *options_csv);
ABI      double        stroptf(double defaults, const char *options_csv);

/// ## String format (temporary buffers)
/// - Format a C-style formatted string. Returns temporary buffer (do not `free()`).
/// - Format a C-style formatted valist. Returns temporary buffer (do not `free()`).
/// - Note: 16 buffers are handled internally so that nested calls are safe within reasonable limits.
///<C
ABI TEMP char *        strf (const char *format, ...);
ABI TEMP char *        strfv(const char *format, va_list list);

/// ## String format (heap buffers)
/// - Assign a C-style formatted string. Reallocates input buffer (will create buffer if `str` is NULL).
/// - Assign a C-style formatted valist. Reallocates input buffer (will create buffer if `str` is NULL).
/// - Concat a C-style formatted string. Reallocates input buffer (will create buffer if `str` is NULL).
/// - Concat a C-style formatted valist. Reallocates input buffer (will create buffer if `str` is NULL).
///<C
ABI HEAP char *        strcpyf (INOUT char **string, const char *format, ...);
ABI HEAP char *        strcpyfv(INOUT char **string, const char *format, va_list list);
ABI HEAP char *        strcatf (INOUT char **string, const char *format, ...);
ABI HEAP char *        strcatfv(INOUT char **string, const char *format, va_list list);

/// ## String splitting
/// - Check delimiters and split string into tokens. Function never allocates.
/// - Check delimiters and split string into tokens. Returns null-terminated list.
/// - Join tokens into a string.
///<C
ABI      int           strchop (const char *string, const char *delimiters, int avail, const char *tokens[]);
ABI HEAP char**        strsplit(const char *string, const char *delimiters);
ABI HEAP char*         strjoin (INOUT char **out, const char *tokens[], const char *separator);

/// ## String trimming
/// - Delete substring from a string.
/// - Trim characters from begin of string to first-find (`b-str-str-e` to `x-xxx-str-e`).
/// - Trim characters from begin of string to last-find (`b-str-str-e` to `x-xxx-xxx-e`).
/// - Trim characters from first-find to end of string (`b-str-str-e` to `b-xxx-xxx-x`).
/// - Trim characters from last-find to end of string (`b-str-str-e` to `b-str-xxx-x`).
/// - Trim leading, trailing and excess embedded whitespaces.
///<C
ABI      char*         strdel    (char *string, const char *substring);
ABI      char*         strtrimbff(char *string, const char *substring);
ABI      char*         strtrimblf(char *string, const char *substring);
ABI      char*         strtrimffe(char *string, const char *substring);
ABI      char*         strtrimlfe(char *string, const char *substring);
ABI      char*         strtrimws (char *string);

/// ## String transforms
/// - Replace a substring in a string.
/// - Remap specific characters in a string from a given set to another one. Length of both sets must be identical.
/// - Convert a string to lowercase (ANSI only, not utf8/locale aware!).
/// - Convert a string to uppercase (ANSI only, not utf8/locale aware!).
/// - Reverse a string in-place.
///<C
ABI HEAP char*         strrepl   (INOUT char **string, const char *target, const char *replace);
ABI      char*         strremap  (INOUT char *string, const char srcs[], const char dsts[]);
ABI      char*         strlower  (char *string);
ABI      char*         strupper  (char *string);
ABI      char*         strrev    (char *string);

/// ## String unicode utils
/// - Extract 32bit codepoint from string. Also advances input string to next codepoint.
/// - Convert 32bit codepoint to utf8 string.
/// - Convert utf8 to utf16 string (Windows only).
///<C
ABI      uint32_t      strutf32(INOUT const char **utf8);
ABI TEMP char *        strutf8(uint32_t codepoint);
ABI TEMP wchar_t*      strwiden(const char *utf8);
///>

);

#endif

// HEADER ---------------------------------------------------------------------

#ifndef STDSTRING_H
#define STDSTRING_H

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef AVA
   // symbol visiblity, abi and linkage
   #ifdef __cplusplus
   #define ABI extern "C"
   #else
   #define ABI
   #endif
   #define API(name,...)   __VA_ARGS__
   // code annonations
   #define HEAP           /* heap pointer. must free() after use */
   #define TEMP           /* temporary stack pointer. do not free() after use */
   #define INOUT          /* both input and output argument */
   #define OPTIONAL       /* optional argument */
   // mem wrappers
   #define REALLOC(p, sz) realloc((p), (sz))
   #define MALLOC(sz)     REALLOC(0, (sz))
   #define CALLOC(n, m)   memset(MALLOC((n)*(m)), 0, (n)*(m))
   #define FREE(p)        REALLOC(p, 0)
   #define STRDUP(s)      strdup(s)
   // compiler stuff
   #ifdef _MSC_VER
   #define builtin(x)     __declspec(x)
   #else
   #define builtin(x)     __##x
   #endif
   // raii perf/profiler
   #define $
#endif

#include __FILE__

#define STRHASH(str)                  STRHASH64(0,131ull,str,0)
#define STRHASH64(hsh,mul,str,idx)    STRHASH16(STRHASH16(STRHASH16(STRHASH16(hsh,mul,str,idx+48),mul,str,idx+32),mul,str,idx+16),mul,str,idx)
#define STRHASH16(hsh,mul,str,idx)    STRHASH04(STRHASH04(STRHASH04(STRHASH04(hsh,mul,str,idx+12),mul,str,idx+ 8),mul,str,idx+ 4),mul,str,idx)
#define STRHASH04(hsh,mul,str,idx)    STRHASH01(STRHASH01(STRHASH01(STRHASH01(hsh,mul,str,idx+ 3),mul,str,idx+ 2),mul,str,idx+ 1),mul,str,idx)
#define STRHASH01(hsh,mul,str,idx)    ((STRHASHCHR(str,idx) ^ hsh) * mul)
#define STRHASHCHR(str,idx)           ((unsigned)str[(idx)<STRHASHLEN(str)?STRHASHLEN(str)-1-(idx):STRHASHLEN(str)])
#define STRHASHLEN(str)               (sizeof(str)-1)

// IMPLEMENTATION -------------------------------------------------------------

#ifdef STDSTRING_IMPLEMENTATION

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// String symbol that holds whole api declarations
// Useful for function-foreign interface (FFI) and related script bindings.
ABI const char * const strapi() {
    #undef  API
    #define API(name, ...) #__VA_ARGS__
    return
    #include __FILE__
    ;
}

#ifdef APIDEMO
#include <stdio.h>
int main() {
    puts(strapi());
}
#endif
