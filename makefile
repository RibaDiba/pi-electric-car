# Compiler and flags
CXX = g++
CXXFLAGS = -c -lwiringPi -lm  
LDFLAGS = -lwiringPi           

# Targets
TARGET = move
OBJ = main.o

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp MotorLib.h 
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm -f *.o $(TARGET)
