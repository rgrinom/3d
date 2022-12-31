build: build_test

build_test:
	g++ -std=c++20 -o test test.cpp Sources/MyDouble.cpp Sources/SoLE.cpp Sources/Point.cpp Sources/Plane.cpp Sources/Line.cpp Sources/Polygon.cpp

run_test:
	./test

clear:
	rm test