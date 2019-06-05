
# vim: ft=make noexpandtab

INCDIRS=-I../../libvcol/src
CFLAGS=-Wall -DDEBUG $(INCDIRS)
SOURCES=
OBJECTS=$(subst .c,.o,$(SOURCES))
OBJDIR=../obj/Debug-Linux-Allegro

MD=mkdir -p -v

all: ../bin/Debug-Linux-Allegro/libcamin.a

../bin/Debug-Linux-Allegro/libcamin.a: $(OBJECTS) input/allegroi.o
	$(MD) ../bin/Debug-Linux-Allegro
	$(AR) rcs $@ $(addprefix $(OBJDIR)/,$^)

%.o: %.c
	$(MD) $(OBJDIR)/$(dir $@)
	$(CC) -c -o $(OBJDIR)/$@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf ../obj; \
	rm -rf ../bin

