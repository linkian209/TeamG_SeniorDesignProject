CXX = g++

#FLAGS
INCLUDES = -Iinc/
CXXFLAGS = -std=c++11 $(INCLUDES) -D_GLIBCXX_USE_NANOSLEEP -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_{1,2,4}
LINKFLAGS = -lpthread 

SRCWILD = $(wildcard ./src/*.cpp)

OBJECTS = $(SRCWILD:.cpp=.o) 

TARGET = drakeOS

all: $(SRC) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LINKFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS)
delete:
	rm -f $(OBJECTS) $(TARGET)
