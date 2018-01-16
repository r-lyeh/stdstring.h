/// # String library
/// C string library (STB style, header-only). Features:
/// - String expression evaluator (`streval`)
/// - String formatters (to heap buffers) (`strcpyf*`, `strcatf*`)
/// - String formatters (to temporary buffers) (`strf*`)
/// - String fuzzy search (`strscore`, `strfuzzy`)
/// - String regular expression (`strregex [c?^$*]`)
/// - String 64-bit hashing (both compile-time and runtime) (`strhash`)
/// - String interning (quarks) (`intern`, `string`)
/// - String matching (`strsub`, `strfindl`, `strfindr`, `strbegin`, `strend`, `strmatch`, `streq`, `streqi`)
/// - String splitting (with and without allocations) (`strsplit`, `strchop`)
/// - String transform utils (`strrepl`, `strtriml`, `strtrimr`, `strlower`)
/// - String conversion utils (`strint`, `strhuman`, `strrobot`)
/// - String unicode utils (`strutf8`, `strutf32`, `strwiden`)
/// - [Documentation](https://rawgit.com/r-lyeh/stdstring.h/master/stdstring.h.html).
/// 
/// # Homepage
/// - https://github.com/r-lyeh/stdstring.h
///
/// # Changelog
/// - 2018.1 (v1.0.0): *Initial release*
///
/// # Credits
/// - Using Rob Pike's regular expression (apparently public domain).
/// - Using Sam Hocevar's preprocessor trick (apparently public domain).
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
ABI HEAP char *        strcpyf (OUT char **string, const char *format, ...);
ABI HEAP char *        strcpyfv(OUT char **string, const char *format, va_list list);
ABI HEAP char *        strcatf (OUT char **string, const char *format, ...);
ABI HEAP char *        strcatfv(OUT char **string, const char *format, va_list list);

/// ## String fuzzy completion
/// - Compares two strings. Returns string matching score (higher is better).
/// - Fuzzy search a word into a list of given words. Returns best match or empty string (if none).
///<C
ABI      int           strscore(const char *string1, const char *string2);
ABI      const char *  strfuzzy(const char *string, int num, const char *words[]);

/// ## Regular expression
/// - regular expression matching. returns non-zero if found.
/// - `c` matches any literal character c.
/// - `?` matches any single character.
/// - `^` matches the beginning of the input string.
/// - `$` matches the end of the input string.
/// - `*` matches zero or more occurrences of the previous character.
///<C
ABI      int           strregex(const char *string, const char *regex);

/// ## String hashing
/// - Compile-time string hash macro. Returns 64-bit hash of given string.
/// - Runtime string hash. Returns 64-bit hash of given string.
/// - Note: Macro requires code optimizations enabled (`/O3` for gcc, `-O2` for MSVC).
///<C
ABI      uint64_t      strhash(const char *string);
ABI      uint64_t      STRHASH(const char *string);

/// ## Interned string dictionary (quarks)
/// - Insert string into dictionary (if not exists). Returns quark ID, or 0 if empty string.
/// - Retrieve previously interned string. ID#0 returns empty string always.
///<C
ABI      int           intern(const char *string);
ABI      const char *  string(int quark);

/// ## String matching
/// - Extract substring from position. Negative positions are relative to end of string.
/// - Search substring from beginning (left).
/// - Search substring from end (right).
/// - Return true if string starts with substring.
/// - Return true if string ends with substring.
/// - Return true if string matches wildcard pattern expression.
/// - Return true if strings are equal.
/// - Return true if strings are equal (case insensitive).
///<C
ABI      const char*   strsub  (const char *string, int position);
ABI      const char*   strfindl(const char *string, const char *substring);
ABI      const char*   strfindr(const char *string, const char *substring);
ABI      bool          strbegin(const char *string, const char *substring);
ABI      bool          strend  (const char *string, const char *substring);
ABI      bool          strmatch(const char *string, const char *substring);
ABI      bool          streq   (const char *string, const char *substring);
ABI      bool          streqi  (const char *string, const char *substring);

/// ## String splitting
/// - Check delimiters and split string into tokens. Returns null-terminated list.
/// - Check delimiters and split string into tokens. Function never allocates.
///<C
ABI HEAP char**        strsplit(const char *string, const char *delimiters);
ABI      int           strchop (const char *string, const char *delimiters, int avail, const char **tokens);

/// ## String transforms
/// - Replace a substring in a string. Returns copy of input string no match is found.
/// - Trim characters from 0 to first search occurence. Trail characters remain intact.
/// - Trim characters from last search occurence to end of string. Lead characters remain intact.
/// - Convert a string to lowercase (function is not utf8/locale aware!).
///<C
ABI HEAP char*         strreplace(const char *string, const char *source, const char *target);
ABI HEAP char*         strtriml  (char *string, const char *substring);
ABI HEAP char*         strtrimr  (char *string, const char *substring);
ABI HEAP char*         strlower  (char *string);

/// ## String conversion utils
/// - Convert a string to integer.
/// - Convert number to human readable string (`12000000 -> 12M`)
/// - Convert human readable string to number (`12M -> 12000000`)
///<C
ABI      int64_t       strint  (const char *string);
ABI TEMP char*         strhuman(uint64_t number);
ABI      uint64_t      strrobot(const char *string);

/// ## String unicode utils
/// - Extract 32bit codepoint from string.
/// - Convert 32bit codepoint to utf8 string.
/// - Convert utf8 to utf16 string (Windows only).
///<C
ABI      uint32_t      strutf32(INOUT const char **p);
ABI TEMP char *        strutf8(uint32_t cp);
ABI HEAP wchar_t*      strwiden(const char *utf8);
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
   #define API(name,...)   __VA_ARS__
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

#define                STRHASH(str)                  STRHASH64(0,131ull,str,0)
#define                STRHASH64(hsh,mul,str,idx)    STRHASH16(STRHASH16(STRHASH16(STRHASH16(hsh,mul,str,idx+48),mul,str,idx+32),mul,str,idx+16),mul,str,idx)
#define                STRHASH16(hsh,mul,str,idx)    STRHASH04(STRHASH04(STRHASH04(STRHASH04(hsh,mul,str,idx+12),mul,str,idx+ 8),mul,str,idx+ 4),mul,str,idx)
#define                STRHASH04(hsh,mul,str,idx)    STRHASH01(STRHASH01(STRHASH01(STRHASH01(hsh,mul,str,idx+ 3),mul,str,idx+ 2),mul,str,idx+ 1),mul,str,idx)
#define                STRHASH01(hsh,mul,str,idx)    ((STRHASHCHR(str,idx) ^ hsh) * mul)
#define                STRHASHCHR(str,idx)           ((unsigned)str[(idx)<STRHASHLEN(str)?STRHASHLEN(str)-1-(idx):STRHASHLEN(str)])
#define                STRHASHLEN(str)               (sizeof(str)-1)

#include __FILE__

// IMPLEMENTATION -------------------------------------------------------------

#ifdef STDSTRING_IMPLEMENTATION

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// String symbol that holds whole api declarations
// Useful for function-foreign interface (FFI) and related script bindings.
ABI const char * const strapi =
    #undef  API
    #define API(name, ...) #__VA_ARGS__
    #include __FILE__
    ;

#ifdef APIDEMO
#include <stdio.h>
int main() {
    puts(strapi);
}
#endif
