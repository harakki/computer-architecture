TARGET  := assembler

BINDIR  := $(DESTDIR)/bin

SOURCES := $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

$(BINDIR):
	mkdir -p $@

.PHONY: $(TARGET)
