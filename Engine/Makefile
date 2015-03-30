
WORKDIR = `pwd`

CXX = g++
AR = ar
LD = g++

INC = \
-I./
-I../Libraries/glm/include \
-I/usr/include/lua5.2/

LIBDIR = \
-L/usr/lib64

LIB = \
-lm -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXi -lXxf86vm \
-lXrandr -lpthread -llua5.2

CFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall

LDFLAGS =

# Debug
XCFLAGS = $(CFLAGS) -g -DDEBUG
XLDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = obj/
OUT = ../dusk

SOURCES = \
Program.cpp \
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
	$(LD) $(LIBDIR) -o $(OUT) $(OBJECTS) $(XLDFLAGS) $(LIB)
