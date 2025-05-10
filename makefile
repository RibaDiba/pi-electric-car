# Compiler and flags
CXX = g++
CXXFLAGS = -c -lwiringPi -lhidapi-hidraw -lm  
LDFLAGS = -lwiringPi -lhidapi-hidraw           

# Targets
TARGET = move

SRCS = src/main.cpp \
       src/Joycon/Joycon.cpp \
       src/MotorLib/MotorArr.cpp \
       src/MotorLib/MotorDriver.cpp \
       src/Joycon_Multiple/Joycons.cpp

OBJS = $(SRCS:.cpp=.o)
all: $(TARGET)

# Link step: combine all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f startup.log

run: 
	sudo ./move
