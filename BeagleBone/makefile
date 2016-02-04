CXX = g++

#FLAGS
INCLUDES = -Iinc/
CXXFLAGS = -std=c++11 $(INCLUDES)

SRC = ./src/BlackCore.cpp ./src/BlackPWM.cpp ./src/BlackGPIO.cpp ./src/PWMManager.cpp ./src/BluetoothManager.cpp ./src/main.cpp

SRCWILD = $(wildcard ./src/*.cpp)

OBJECTS = $(SRCWILD:.cpp=.o) 

TARGET = drakeOS

all: $(SRC) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS)
