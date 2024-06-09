TARGET   := myReadKey.a

BUILDDIR := build

LIB      := $(BUILDDIR)/$(TARGET)

EXCLUDE  := 
SOURCES  := $(filter-out $(EXCLUDE), $(wildcard *.c))
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SOURCES))

all: lib

lib: $(LIB)

$(LIB): $(OBJFILES)
	ar rcs $@ $(OBJFILES)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $@

.PHONY: all lib
