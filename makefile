SDIR = src
ODIR = obj
CC = gcc
OFILES = $(ODIR)/lexer.o $(ODIR)/cpl.o $(ODIR)/helpers.o $(ODIR)/parser.o $(ODIR)/evaluator.o $(ODIR)/built_in_fn.o $(ODIR)/errors.o

all: cpl

$(ODIR)/lexer.o: $(SDIR)/lexer.c $(SDIR)/lexer.h
	$(CC) -c $(SDIR)/lexer.c -o $(ODIR)/lexer.o

$(ODIR)/cpl.o: $(SDIR)/cpl.c
	$(CC) -c $(SDIR)/cpl.c -o $(ODIR)/cpl.o

$(ODIR)/helpers.o: $(SDIR)/helpers.c $(SDIR)/helpers.h
	$(CC) -c $(SDIR)/helpers.c -o $(ODIR)/helpers.o

$(ODIR)/parser.o: $(SDIR)/parser.c $(SDIR)/parser.h
	$(CC) -c $(SDIR)/parser.c -o $(ODIR)/parser.o

$(ODIR)/evaluator.o: $(SDIR)/evaluator.c $(SDIR)/evaluator.h
	$(CC) -c $(SDIR)/evaluator.c -o $(ODIR)/evaluator.o

$(ODIR)/built_in_fn.o: $(SDIR)/built_in_fn.c $(SDIR)/built_in_fn.h
	$(CC) -c $(SDIR)/built_in_fn.c -o $(ODIR)/built_in_fn.o

$(ODIR)/errors.o: $(SDIR)/errors.c $(SDIR)/errors.h
	$(CC) -c $(SDIR)/errors.c -o $(ODIR)/errors.o


cpl: $(OFILES)
	$(CC) $(OFILES) -o cpl

clean:
	rm $(ODIR)/*.o