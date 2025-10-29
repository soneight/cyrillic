.PHONY: usage cmake build clean

usage:
	cat Makefile.usage.txt
cmake:
	cd build && cmake -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && cd ../
build:
	cd build && ninja && cd ../
clean:
	rm -rf build/ && git restore build/.gitignore
