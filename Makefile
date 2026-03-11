CC = gcc

CFLAGS = -Wall -Iinclude -g

TARGET = bin/product_program

SRCDIR = src

OBJDIR = obj

INCDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.c)

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(TARGET)
$(TARGET): $(OBJECTS) | bin
	$(CC) $^ -o $@
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR):
	mkdir -p $(OBJDIR)
bin:
	mkdir -p bin
clean:
	rm -rf $(OBJDIR) bin
check: all
	./$(TARGET) test
distcheck: all
	./$(TARGET) test
.PHONY: all clean check distcheck
