CC=g++
CFLAGS=-c -pedantic-errors
LDFLAGS=
SOURCES=boolcalc.cpp boolexpr.cpp fullsystem.cpp workspace_global.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=boolcalc

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
