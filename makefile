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

# Fuentes
SRCS = $(wildcard $(SRCDIR)/*.c) $(foreach dir,$(LIBDIRS),$(wildcard $(dir)/*.c))
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEBUG_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%-debug.o,$(SRCS))

# Reglas de construcción
all: $(TARGET)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)-debug

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(TARGET)-debug: $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET)-debug $(DEBUG_OBJS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%-debug.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(LIBDIRS:%=%)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%-debug.o: $(LIBDIRS:%=%)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(TARGET)-debug

.PHONY: all debug clean valgrind

# Regla para ejecutar con Valgrind
valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --gen-suppressions=all --suppressions=debug/valgrind/valgrind-suppressions.supp --log-file=debug/valgrind/valgrind_output.txt -s ./$(TARGET)-debug