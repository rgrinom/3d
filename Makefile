build: build_test

build_test:
	g++ -std=c++20 -O2 -o test -lsfml-graphics -lsfml-window -lsfml-system test.cpp Sources/MyDouble.cpp Sources/SoLE.cpp Sources/Point.cpp Sources/Plane.cpp Sources/Line.cpp Sources/Polygon.cpp Sources/Movements.cpp Sources/Figures.cpp Sources/Camera.cpp

run_test:
	./test

clear:
	rm test