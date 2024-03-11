CXX = g++            # C++ compiler
CXXFLAGS = -std=c++17 # Compilation flags
SRC =  LexicalAnalyzerTest.cpp        # Replace with your C++ source file
OUTPUT = LexicalAnalyzerTest        # Replace with your desired executable name

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)