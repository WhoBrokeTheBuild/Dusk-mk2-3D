
WORKDIR = `pwd`

CXX = g++
AR = ar
LD = g++

INC = \
-I. \
-I../Libraries/glm/include \
-I/usr/include/SDL2
LIBDIR = -L/usr/lib64
LIB = -lSDL2 -lSDL2main -lSDL2_image -lpng
CFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall
LDFLAGS =

# Debug
XCFLAGS = $(CFLAGS) -g -DDEBUG
XLDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = obj
OUTDIR = ../../
OUT = duskrc

SOURCES = \
Main.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CXX) $(XCFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	$(LD) $(LIBDIR) -o $(OUTDIR)$(OUT) $(OBJECTS) $(XLDFLAGS) $(LIB)
