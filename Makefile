TARGET := build/main
EXEC := main
TEMP := temp.txt

IDIR := include
LDIR := lib
BDIR := build

SRCS := $(shell find $(LDIR) -type f -name *.cpp)
OBJS := $(patsubst $(LDIR)/%,$(BDIR)/%,$(SRCS:.cpp=.o))
INC := -I include

CXX := g++
CXXFLAGS := -g -Wall

all: $(OBJS)
	@echo " Linking...";
	$(CXX) $(CXXFLAGS) $(INC) $(OBJS) -o $(EXEC)

$(BDIR)/%.o: $(LDIR)/%.cpp
	@mkdir -p $(BDIR);
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	@echo " Cleaning...";
	$(RM) -r $(BDIR) $(EXEC) $(TEMP)
