CC := gcc
SOURCE_FILES := src\main.c src\libs\physics.c src\libs\render.c src\libs\vectors.c
O_FILES := $(subst src\,build\,$(SOURCE_FILES:.c=.o))
TARGET := executable.exe
WARNINGS := -Wall -Wextra -Wshadow -Wconversion
ALLEGRO_TAGS := -lallegro -lallegro_font -lallegro_primitives
C_FLAGS := -O2 $(ALLEGRO_TAGS) $(WARNINGS)

$(TARGET): $(O_FILES)
	$(CC) $^ -o $(TARGET) $(C_FLAGS)

build\\%.o: src\%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

build: $(TARGET)

clean:
	@echo cleaning...
	@del /q /f $(O_FILES) $(TARGET)

run: $(TARGET)
	./$(TARGET)

test:
	@echo $(TARGET)
	@echo $(SOURCE_FILES)
	@echo $(O_FILES)

.PHONY: clean build run