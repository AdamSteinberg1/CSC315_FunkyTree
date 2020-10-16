
CC = gcc
C++ = g++
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm


main: main.o Vec2.o Polygon.o Triangle.o Circle.o Mat3.o Vec3.o Tessellator.o LinkedList.o
	$(C++) -o main main.o Vec2.o Polygon.o Triangle.o Circle.o Mat3.o Vec3.o Tessellator.o LinkedList.o $(INCDIRS) $(LIBDIRS) $(LDLIBS)

main.o: main.cpp
	$(C++) -c main.cpp

Vec2.o: Vec2.cpp
	$(C++) -c Vec2.cpp

Polygon.o: Polygon.cpp Vec2.o Triangle.o
	$(C++) -c Polygon.cpp

Triangle.o: Triangle.cpp Vec2.o
	$(C++) -c Triangle.cpp

Circle.o: Circle.cpp Vec2.o Polygon.o
	$(C++) -c Circle.cpp

Mat3.o: Mat3.cpp
	$(C++) -c Mat3.cpp

Vec3.o: Vec3.cpp
	$(C++) -c Vec3.cpp

Tesselator.o: Tessellator.cpp LinkedList.o
	$(C++) -c Tessellator.cpp

LinkedList.o: LinkedList.cpp
	$(C++) -c LinkedList.cpp
