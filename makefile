# Nombre del ejecutable
TARGET = wizard

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`

# Bibliotecas necesarias
LIBS = `pkg-config --libs gtk+-3.0`

# Fuentes
SRCS = main.c

# Objetos
OBJS = $(SRCS:.c=.o)

# Reglas de construcción
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
