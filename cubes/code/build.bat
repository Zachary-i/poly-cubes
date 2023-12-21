@echo off

mkdir ..\..\build
pushd ..\..\build
cl -FC -Zi -EHsc ..\cubes\code\polycubes.cpp
popd
