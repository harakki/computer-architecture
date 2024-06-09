TARGET   := pr02
TARGET2  := console.a

BINDIR   := $(DESTDIR)/bin
BUILDDIR := build

AR       := ar -rcs

LIB      := $(BUILDDIR)/$(TARGET2)

EXCLUDE  := main.c
SOURCES  := $(filter-out $(EXCLUDE), $(wildcard *.c))
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SOURCES))

all: $(BINDIR)/$(TARGET)

lib: $(LIB)

$(LIB): $(OBJFILES)
	$(AR) $@ $(OBJFILES)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR)/$(TARGET): main.c $(LIB) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(BINDIR) $(BUILDDIR):
	mkdir -p $@

.PHONY: all $(LIB) $(TARGET)
