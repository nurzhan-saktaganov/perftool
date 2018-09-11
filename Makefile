ifeq ($(INTEL_COMPILER), 1)
	CC=icc
	OPENMP=-qopenmp
	EXPORTMAP=-Wl,--version-script=exportmap.exp
else
	CC=gcc
	OPENMP=-fopenmp
	EXPORTMAP=
endif

BIN=bin
SRC=src

MICFLAG=
ifeq ($(MIC), 1)
	MICFLAG = -mmic
endif

all: omp_dbg.so

omp_dbg.so: builddir
	$(CC) -Wall $(MICFLAG) -shared -fPIC $(OPENMP) \
		$(EXPORTMAP) \
		-o $(BIN)/omp_dbg.so \
		$(SRC)/context_descriptor.c \
		$(SRC)/context_string.c \
		$(SRC)/dvmh_omp_event_analyzer.c \
		$(SRC)/dvmh_omp_event.c \
		$(SRC)/dvmh_omp_interval.c \
		$(SRC)/dvmh_omp_thread_info.c \
		$(SRC)/list.c \
		$(SRC)/omp_dbg.c \
		$(SRC)/register_context.c \
		$(SRC)/stack.c

.PHONY: builddir
builddir:
	mkdir -p $(BIN)
