# Compiler and flags
CXX = g++
CXXFLAGS = -c -lwiringPi -lhidapi-hidraw -lm  
LDFLAGS = -lwiringPi -lhidapi-hidraw           

# Targets
TARGET = move
OBJ = main.o

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp MotorLib.h Joycon.h
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm -f *.o $(TARGET)

run: 
	sudo ./move
