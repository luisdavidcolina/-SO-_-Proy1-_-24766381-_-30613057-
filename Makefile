# Definición del compilador y las banderas de compilación
CC = gcc
CFLAGS = -Wall -pthread
LDFLAGS = -L./md5-lib -lmd5

# Directorios de origen, inclusión, objetos y binarios
SRCDIR = src
INCDIR = $(SRCDIR)/include
OBJDIR = obj
BINDIR = bin

# Archivos fuente y objetos
FUENTES = $(wildcard $(SRCDIR)/*.c)
OBJETOS = $(FUENTES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EJECUTABLE = $(BINDIR)/duplicados

# Regla para compilar todo
all: md5-app md5-lib $(EJECUTABLE)

# Regla para compilar el ejecutable principal
$(EJECUTABLE): $(OBJETOS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para compilar los archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ -c $<

# Regla para compilar md5-app
md5-app:
	$(MAKE) -C md5-app

# Regla para compilar md5-lib
md5-lib:
	$(MAKE) -C md5-lib

# Regla para limpiar los archivos compilados
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	$(MAKE) -C md5-app clean
	$(MAKE) -C md5-lib clean

# Declaración de las reglas como phony
.PHONY: all clean md5-app md5-lib
