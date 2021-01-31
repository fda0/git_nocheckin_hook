@echo off
pushd build
set SourcePath=../code/source.c

rem ~~~~~~~~~~WARININGS~~~~~~~~~~
set opts=/WX /W4
rem ~~~~~~~~~~FLAGS~~~~~~~~~~
set opts=%opts% /nologo /GR- /FC
set link_opts=/link /incremental:no /opt:ref
rem ~~~~~~~~~~BUILD x64~~~~~~~~~~
cl %opts% %SourcePath% /O2 %link_opts% /out:pre-commit

popd
