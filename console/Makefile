TARGET   := test

BINDIR   := $ (DESTDIR)/bin
BUILDDIR := build

AR       := ar -rcs

EXCLUDE  := 
SOURCES  := $(filter-out $(EXCLUDE), $(wildcard *.c))
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): test.c
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR) $(BUILDDIR):
	mkdir -p $@

.PHONY: all $(TARGET)
