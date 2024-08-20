# Nombre del ejecutable
TARGET = bin/wizard

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`

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

# Reglas de construcción
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(LIBDIRS:%=%)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
