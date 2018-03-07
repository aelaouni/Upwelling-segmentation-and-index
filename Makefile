IDIR =index/src
SDIR=segmentation/src
NDIR=SstNorm/src
CC=gcc
CFLAGS= `pkg-config --libs --cflags opencv` -lnetcdf -lm


ILIBS= -I$(IDIR)
SLIBS= -I$(SDIR)
NLIBS= -I$(NDIR)

_DEPS = *
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJI = main.o index.o display_functions.o netcdf_functions.o
OBJI = $(patsubst %,$(IDIR)/%,$(_OBJI))


_OBJS = main.o clustering_functions.o edge_detector_functions.o display_functions.o RB_segmentation_functions.o netcdf_functions.o
OBJS = $(patsubst %,$(SDIR)/%,$(_OBJS))


_OBJN = main.o line.o  netcdf_functions.o
OBJN = $(patsubst %,$(NDIR)/%,$(_OBJN))


$(IDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(ILIBS) 

$(NDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(NLIBS) 

$(SDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SLIBS) 


all: ind segment norm_sst

ind: $(OBJI)
	gcc -o $@ $^ $(CFLAGS) 

segment: $(OBJS)
	gcc -o $@ $^ $(CFLAGS) 

norm_sst: $(OBJN)
	gcc -o $@ $^ $(CFLAGS) 




.PHONY: clean

clean:
	rm -f $(IDIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(NDIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(SDIR)/*.o *~ core $(INCDIR)/*~
