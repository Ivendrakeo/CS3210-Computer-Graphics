EXECUTABLE = run
SOURCES = main.cpp matrix.cpp
OBJECTS = $(SOURCES:.cpp=.o)

example: $(OBJECTS)
	g++ -o $(EXECUTABLE) $(OBJECTS)
	
main.o: main.cpp
	g++ -c main.cpp
	
matrix.o: matrix.cpp
	g++ -c matrix.cpp
	
clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
