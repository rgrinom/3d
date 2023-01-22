build_demo:
	g++ -std=c++20 -O2 -o demo -lsfml-graphics -lsfml-window -lsfml-system main.cpp Sources/MyDouble.cpp Sources/SoLE.cpp Sources/Point.cpp Sources/Plane.cpp Sources/Line.cpp Sources/Polygon.cpp Sources/Movements.cpp Sources/Figures.cpp Sources/Camera.cpp

build_test:
	g++ -std=c++20 -O2 -o test -lsfml-graphics -lsfml-window -lsfml-system test.cpp Sources/MyDouble.cpp Sources/SoLE.cpp Sources/Point.cpp Sources/Plane.cpp Sources/Line.cpp Sources/Polygon.cpp Sources/Movements.cpp Sources/Figures.cpp Sources/Camera.cpp

run_demo:
	./demo

run_test:
	./test

clear:
	rm test
	rm demo