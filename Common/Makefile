
WORKDIR = `pwd`

CXX = g++
AR = ar

INC = \
-I.
CFLAGS = -pedantic-errors -pedantic -std=c++11 -Wall

# Debug
XCFLAGS = $(CFLAGS) -g -DDEBUG
XLDFLAGS = $(LDFLAGS)

# Release
#CFLAGS = $(CFLAGS) -O2 -DRELEASE
#LDFLAGS = $(LDFLAGS) -s

OBJDIR = obj
OUT = ../libdusk.a

SOURCES = \
Logging/LoggingSystem.cpp \
Logging/Logger.cpp \
Logging/Loggers/ConsoleLogger.cpp \
Logging/Loggers/FileLogger.cpp \
Logging/Loggers/StreamLogger.cpp \
Dusk.cpp

OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CXX) $(XCFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	$(AR) rvs $(OUT) $(OBJECTS)
