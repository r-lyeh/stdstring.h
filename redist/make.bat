@echo off

REM amalgamation
cl amalgamate.c
amalgamate > stdstring.h

REM samples
echo #define STDSTRING_IMPLEMENTATION > test.c
echo #include "stdstring.h" >> test.c
cl /nologo test.c -DUTFDEMO         && test
cl /nologo test.c -DTRANSFORMDEMO   && test
cl /nologo test.c -DCONVERSIONDEMO  && test
cl /nologo test.c -DEVALDEMO        && test
cl /nologo test.c -DFUZZYDEMO       && test
cl /nologo test.c -DHASHDEMO        && test
cl /nologo test.c -DINTERNDEMO      && test
cl /nologo test.c -DMATCHDEMO       && test
cl /nologo test.c -DREGEXDEMO       && test
cl /nologo test.c -DREPLACEDEMO     && test
cl /nologo test.c -DSPLITDEMO       && test
cl /nologo test.c -DOPTIONDEMO      && test --client=off --server=true --port=1234 --user=bla@bla.com --distance=120km --time=2ms --bits=4Kib --health=(10+12)*10
del test.c
del *.obj
del *.exe

REM documentation
..\..\stddoc < stdstring.h > stdstring.h.html
start stdstring.h.html

