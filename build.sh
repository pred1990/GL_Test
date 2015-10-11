#/bin/bash

if [ ! -d "bin/" ]; then
	mkdir bin
	echo creating Folder: "bin"
fi

clang++ lnx_platform.cpp -g -Wall -fno-exceptions\
				-o bin/startWindow\
				-lGL -lX11
chmod 755 bin/startWindow
