@echo off

pushd ..\build

REM -wd4005 stänger av varning om redefention av APIENTRY Från glad biblioteket
cl -nologo -Zi -wd4005 ..\src\cj_GL.cpp user32.lib gdi32.lib opengl32.lib

popd

del *.un~ *.cpp~ *.bat~
