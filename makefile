CXX = g++            # C++ compiler
CXXFLAGS = -std=c++11 # Compilation flags
SRC =  LightState.cpp        # Replace with your C++ source file
OUTPUT = LightState        # Replace with your desired executable name

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)