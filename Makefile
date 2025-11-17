COMPILER = g++
OPTIONS = -Wall -Werror -pedantic -fsanitize=address -MMD -MP -I $(INCLUDE) -g
COMPILE = $(COMPILER) $(OPTIONS)

SRC = src
BUILD = build
BIN = bin
INCLUDE = include

SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SOURCES))
DEPS = $(OBJECTS:.o=.d)

TARGET = $(BIN)/argus

$(shell mkdir -p $(BUILD) $(BIN) $(SAVE))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(COMPILE) $(OBJECTS) -o $(TARGET)

$(BUILD)/%.o: $(SRC)/%.cpp
	$(COMPILE) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all clean
