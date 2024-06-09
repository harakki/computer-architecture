TARGET   := simpleComputer
TARGET2  := fontCreator
TARGET3  := console.a

BINDIR   := $(DESTDIR)/bin
BUILDDIR := build

AR       := ar -rcs

LIB      := $(BUILDDIR)/$(TARGET3)

EXCLUDE  := main.c
SOURCES  := $(filter-out $(EXCLUDE), $(wildcard *.c))
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SOURCES))

all: $(BINDIR)/$(TARGET)

lib: $(LIB)

$(LIB): $(OBJFILES)
	$(AR) $@ $(OBJFILES)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): main.c $(LIB) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(BINDIR) $(BUILDDIR):
	mkdir -p $@

$(TARGET2): $(BINDIR)/$(TARGET2)

$(BINDIR)/$(TARGET2): | $(BINDIR)
	$(CC) $(CFLAGS) font.c -o $@

.PHONY: all $(LIB) $(TARGET) $(TARGET2)
