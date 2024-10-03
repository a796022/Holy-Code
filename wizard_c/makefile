# Nombre del ejecutable
TARGET = bin/wizard

# Compilador
CC = gcc

# Opciones de compilación básicas
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`

# Opciones de compilación para depuración
DEBUG_CFLAGS = -g -Wall -Wextra -pedantic

# Bibliotecas necesarias
LIBS = `pkg-config --libs gtk+-3.0`

# Directorios
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIRS = lib/background_keyboard_imput lib/clipboard external/sds
TESTDIR = test
TEST_SRCDIR = $(TESTDIR)/test_src
TEST_OBJDIR = $(TESTDIR)/test_obj
TEST_BINDIR = $(TESTDIR)/test_bin

# Fuentes
SRCS = $(wildcard $(SRCDIR)/*.c) $(foreach dir,$(LIBDIRS),$(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRCS)))

# Test executable
TEST_TARGET = $(TEST_BINDIR)/test_wizard
TEST_SRCS = $(wildcard $(TEST_SRCDIR)/*.c)
TEST_OBJS = $(patsubst %.c,$(TEST_OBJDIR)/%.o,$(notdir $(TEST_SRCS)))
TEST_MAIN_OBJ = $(TEST_OBJDIR)/main.o

# Objetos del programa principal, excluyendo main.o
MAIN_OBJS = $(filter-out $(OBJDIR)/main.o,$(OBJS))

# Reglas de construcción
all: $(TARGET)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)-debug

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(TARGET)-debug: $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -o $(TARGET)-debug $(OBJS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(LIBDIRS:%=%)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(TEST_OBJDIR)/%.o: $(TEST_SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(TEST_SRCDIR) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(TARGET)-debug
	rm -rf $(TEST_OBJDIR) $(TEST_BINDIR)

.PHONY: all debug clean valgrind test test_valgrind

# Regla para ejecutar con Valgrind
valgrind: debug
	sudo -E valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --gen-suppressions=all --suppressions=debug/valgrind/valgrind-suppressions.supp --log-file=debug/valgrind/valgrind_output.txt -s ./$(TARGET)-debug

# Regla para ejecutar si la compilación fue exitosa
run: all
	sudo -E ./$(TARGET)

# Regla para compilar y ejecutar los tests
test: $(TEST_TARGET)
	sudo -E ./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(MAIN_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(MAIN_OBJS) $(LIBS)

# Regla para ejecutar los tests con Valgrind
test_valgrind: $(TEST_TARGET)
	sudo -E valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --gen-suppressions=all --suppressions=debug/valgrind/valgrind-suppressions.supp --log-file=debug/valgrind/valgrind_output.txt -s ./$(TEST_TARGET)