CC = g++
CFLAGS = -c
LDFLAGS = -lX11
SOURCES = gcontext.cpp x11context.cpp matrix.cpp Shape.cpp Line.cpp Triangle.cpp Image.cpp main.cpp mydrawing.cpp ViewContext.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = run

all: $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) $(OBJECTS)
	
-include *.d

main.o: main.cpp
	g++ -c $<
gcontext.o: gcontext.cpp
	g++ -c $<
x11context.o: x11context.cpp
	g++ -c $<
matrix.o: matrix.cpp
	g++ -c $<
Shape.o: Shape.cpp
	g++ -c $<
Line.o: Line.cpp
	g++ -c $<
Triangle.o: Triangle.cpp
	g++ -c $<
Image.o: Image.cpp
	g++ -c $<
mydrawing.o: mydrawing.cpp
	g++ -c $<
ViewContext.o: ViewContext.cpp
	g++ -c $<

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	rm -f *.d
