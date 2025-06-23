INCDIR := include
SRCDIR := src
OUTDIR := out
TARGET := $(OUTDIR)/trab4
CFLAGS := -Wall -Wextra -Werror -lm -std=c99 -I$(INCDIR)

SRCS   := $(shell find $(SRCDIR) -name "*.c")
OBJS   := $(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%.o,$(SRCS))

build: $(TARGET)

# Builda e executa o código, repassando os argumentos
run: build
	cd $(OUTDIR)
	./$(TARGET)

# Gera a pasta de saída caso ela não exista
outdir:
	mkdir -p $(OUTDIR)

# Regras para compilar cada arquivo .c
$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar o trabalho final
$(TARGET): outdir $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)