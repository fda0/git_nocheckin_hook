@echo off

pushd build

set SourcePath=../code/source.c

rem ~~~~~~~~~~WARININGS~~~~~~~~~~
set opts=/WX /W4
set opts=%opts% /wd4100 /wd4201 /wd4189 /wd4505 /wd4101 /wd4996

rem ~~~~~~~~~~FLAGS~~~~~~~~~~
set opts=%opts% /nologo /GR- /FC
rem set opts=%opts% /MTd /EHa- /Oi /Zi

set link_opts=/link /incremental:no /opt:ref

rem ~~~~~~~~~~BUILD x64~~~~~~~~~~
cl %opts% %SourcePath% /O2 %link_opts% /out:pre-commit

popd
