# Include directories
ROOT_DIRECTORY = .
FILES_DIRECTORY = $(ROOT_DIRECTORY)/files
FILTER_DIRECTORY = $(ROOT_DIRECTORY)/filters

# Add each subfolder as include directories (prevents nasty relative imports!)
CXX = g++
CXXFLAGS = \
	-std=c++17 -g -Wall -O2 \
	-I $(ROOT_DIRECTORY)

PROG ?= main

# Main program objects
MAIN_OBJS = main.o

# Filter module 
FILTER_OBJS = \
	$(FILTER_DIRECTORY)/ImageFilter.o \
	$(FILTER_DIRECTORY)/batch_processing/FilterList.o \
	$(FILTER_DIRECTORY)/concrete/ChannelSwapFilter.o \
	$(FILTER_DIRECTORY)/concrete/ColorFilter.o \
	$(FILTER_DIRECTORY)/concrete/InvertFilter.o \

FILE_OBJS = \
	$(FILES_DIRECTORY)/File.o \
	$(FILES_DIRECTORY)/Clock.o \
	$(FILES_DIRECTORY)/FileUtils.o \
	$(FILES_DIRECTORY)/image/ImageFile.o \
	$(FILES_DIRECTORY)/image/Pixel.o \
	$(FILES_DIRECTORY)/load/FileLoader.o \
	$(FILES_DIRECTORY)/text/TextFile.o \


OBJS = $(MAIN_OBJS) \
	$(FILE_OBJS) \
	$(FILTER_OBJS) \

mainprog: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) *.out 
	find $(ROOT_DIRECTORY) -name "*.o" -delete

rebuild: clean mainprog