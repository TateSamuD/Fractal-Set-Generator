CXX = g++
ECHO = echo
VAL = valgrind
RM = rm -f

CXXFLAGS = -ggdb -std=c++17 -O3 -fopenmp
DATE = $(shell date +"%Y%m%d_%H%M")
VALGRIND_OPTIONS = --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=fractal_$(DATE).log

LDFLAGS = -lm 

SRCS = main.cpp fractal.cpp image_gen.cpp video_gen.cpp
EXE = Fractals
DIRS = ./Julia_z2_Frames ./Julia_z4_Frames ./Turbulence_Frames
OBJS = $(SRCS:.cpp=.o)

.PHONY: all valgrind clean directories

all: $(EXE)
	@$(ECHO) Build complete!

$(EXE): $(OBJS)
	@$(ECHO) Linking object files to $@
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@$(ECHO) Done!

$(DIRS):
	@$(ECHO) Creating directories
	@$(MKDIR) $(DIRS)
	@$(ECHO) Done!

-include $(OBJS:.o=.d)

%.o: %.cpp
	@$(ECHO) "Compiling $<"
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $<
	@$(ECHO) Done!

directories: $(DIRS)

valgrind: $(EXE)
	@$(ECHO) Running debugger. Please wait for log file!
	@$(VAL) $(VALGRIND_OPTIONS) ./$(EXE)
	@$(ECHO) Done!

clean:
	@$(ECHO) Removing all generated files
	@$(RM) $(EXE) *~ *.o core *.d .ppm *.exe 
	@$(RM) -r $(DIRS)
	@$(ECHO) Done!
