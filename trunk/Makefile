SOURCES =	$(wildcard sources/*.cpp)
OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	stochastic
LIBS	=
CFLAGS	=
INCLUDES =	headers

all: $(OBJECTS)
	g++ -fopenmp -o $(TARGET) -I $(INCLUDES) $(OBJECTS) $(LIBS)

%.o: %.cpp
	g++ -fopenmp -c $< -o $@ $(CFLAGS) -I $(INCLUDES)

x:	all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

