CC = g++
CFLAGS = -c
LDFLAGS = -lX11
SOURCES = gcontext.cpp x11context.cpp main.cpp
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
	
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	rm -f *.d
