.PHONY: usage cmake ninja clean build allin
# recipes
usage:
	cat Makefile.usage.txt
cmake:
	cmake -B build/ -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja:
	ninja -C build/
clean:
	rm -rf build/ && git restore build/.gitignore
build:
	make cmake && make ninja
allin:
	make clean && make build
