@echo off

pushd ..\build

REM -wd4005 st�nger av varning om redefention av APIENTRY Fr�n glad biblioteket
cl /MD -nologo -Zi -wd4005 ..\src\cj_GL_GLFW.cpp user32.lib gdi32.lib opengl32.lib glfw3.lib shell32.lib

popd

del *.un~ *.cpp~ *.bat~
