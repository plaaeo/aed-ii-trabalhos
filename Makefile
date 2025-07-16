.PHONY: all clean run outdir

INCDIR := include
SRCDIR := src
OUTDIR := out
TARGET := $(OUTDIR)/trab4

# Compilador
CC 	   = gcc
CFLAGS = -Wall -Wextra -Werror -lm -std=c99 -I$(INCDIR)

# Arquivos
SRCS   := $(shell find $(SRCDIR) -name "*.c")
OBJS   := $(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%.o,$(SRCS))

# Builda tudo
all: $(TARGET)

# Limpa os arquivos de build
clean:
	rm -rf $(OUTDIR)

# Builda e executa o código, repassando os argumentos
run: all
	cd $(OUTDIR)
	./$(TARGET)

# Gera a pasta de saída caso ela não exista
outdir:
	mkdir -p $(OUTDIR)

# Regras para compilar cada arquivo .c
$(OUTDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(shell dirname "$@")
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar o trabalho final
$(TARGET): outdir $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
