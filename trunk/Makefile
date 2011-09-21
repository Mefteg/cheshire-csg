SOURCES =	$(wildcard sources/*.cpp)
OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	stochastic
LIBS	=
CFLAGS	=
INCLUDES =	headers

all: $(OBJECTS)
	g++ -o -I $(INCLUDES) $(TARGET) $(OBJECTS) $(LIBS) -fopenmp

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS) -I $(INCLUDES)

x:	all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

