EXE := static.exe
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)

CPPFLAGS := -ISFML-2.5.1/include -MMD -MP -DSFML_STATIC
CXXFLAGS := -std=c++17 -Wall -W -pedantic
LDFLAGS  := -LSFML-2.5.1/lib
LDLIBS   := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LDLIBS   += -lopengl32 -lwinmm -lgdi32

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(EXE) $(OBJ) $(DEP)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEP)
endif