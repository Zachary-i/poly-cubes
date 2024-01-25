@echo off

mkdir ..\..\build
pushd ..\..\build
cl -FC -Zi -EHsc -F 4194304 ..\cubes\code\polycubes.cpp
popd
