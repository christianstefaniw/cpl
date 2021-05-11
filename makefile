SDIR = src
ODIR = obj
CC = gcc
OFILES = $(ODIR)/lexer.o $(ODIR)/cpl.o $(ODIR)/helpers.o $(ODIR)/parser.o $(ODIR)/evaluator.o


$(ODIR)/lexer.o: $(SDIR)/lexer.c $(SDIR)/lexer.h
	$(CC) -c $(SDIR)/lexer.c -o $(ODIR)/lexer.o

$(ODIR)/cpl.o: $(SDIR)/cpl.c $(SDIR)/cpl.h
	$(CC) -c $(SDIR)/cpl.c -o $(ODIR)/cpl.o

$(ODIR)/helpers.o: $(SDIR)/helpers.c $(SDIR)/helpers.h
	$(CC) -c $(SDIR)/helpers.c -o $(ODIR)/helpers.o

$(ODIR)/parser.o: $(SDIR)/parser.c $(SDIR)/parser.h
	$(CC) -c $(SDIR)/parser.c -o $(ODIR)/parser.o

$(ODIR)/evaluator.o: $(SDIR)/evaluator.c $(SDIR)/evaluator.h
	$(CC) -c $(SDIR)/evaluator.c -o $(ODIR)/evaluator.o


cpl: $(OFILES)
	$(CC) $(OFILES) -o cpl

clean:
	rm $(ODIR)/*.o