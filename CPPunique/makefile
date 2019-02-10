CXX      = g++ #which compiler 
CXX_FILE = $(wildcard *.cpp) #find the file that ends in .cpp
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE)) #remove .cpp from file when executing
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0
#-g in debugging, -o2 or -o3 for optimization but no warnings
# std sets version of cpp
#-wall give warnings for all to be displayed, warning errors turned on
#-werror every warnig is treated as an error, stops execution
#-pedantic-errors diagnostic warnings, things that could be problematic. 
#-fmessage all warnings in one line


# dependencies on the right of colon
# $$$ how it should look in the terminal
# -o output name
all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe
# the whole point of the makefile is to make it easier to execute in the terminal