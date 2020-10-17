C++ = g++ -g
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm
OBJS = main.o Vec2.o Polygon.o Triangle.o Circle.o Mat3.o Vec3.o Tessellator.o Clipper.o

tree: $(OBJS)
	$(C++) -o tree $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDLIBS)

main.o: main.cpp Circle.h
	$(C++) -c main.cpp

init.o: init.cpp
	$(C++) -c init.cpp

Vec2.o: Vec2.cpp Vec2.h
	$(C++) -c Vec2.cpp

Polygon.o: Polygon.cpp Polygon.h Tessellator.h Vec2.h Vec3.h Clipper.h Mat3.h
	$(C++) -c Polygon.cpp

Triangle.o: Triangle.cpp Triangle.h
	$(C++) -c Triangle.cpp

Circle.o: Circle.cpp Circle.h Polygon.h Vec2.h
	$(C++) -c Circle.cpp

Mat3.o: Mat3.cpp Mat3.h Vec2.h Vec3.h
	$(C++) -c Mat3.cpp

Vec3.o: Vec3.cpp Vec3.h
	$(C++) -c Vec3.cpp

Tessellator.o: Tessellator.cpp Tessellator.h Vec2.h Triangle.h
	$(C++) -c Tessellator.cpp

Clipper.o: Clipper.cpp Clipper.h Polygon.h
	$(C++) -c Clipper.cpp
