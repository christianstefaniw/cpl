SDIR = src
ODIR = obj
CC = gcc
OFILES = $(ODIR)/lexer.o $(ODIR)/cpl.o $(ODIR)/helpers.o $(ODIR)/parser.o


$(ODIR)/lexer.o: $(SDIR)/lexer/lexer.c $(SDIR)/lexer/lexer.h
	$(CC) -c $(SDIR)/lexer/lexer.c -o $(ODIR)/lexer.o

$(ODIR)/cpl.o: $(SDIR)/cpl.c $(SDIR)/cpl.h
	$(CC) -c $(SDIR)/cpl.c -o $(ODIR)/cpl.o

$(ODIR)/helpers.o: $(SDIR)/helpers.c $(SDIR)/helpers.h
	$(CC) -c $(SDIR)/helpers.c -o $(ODIR)/helpers.o

$(ODIR)/parser.o: $(SDIR)/parser/parser.c $(SDIR)/parser/parser.h
	$(CC) -c $(SDIR)/parser/parser.c -o $(ODIR)/parser.o


cpl: $(OFILES)
	$(CC) $(OFILES) -o cpl

clean:
	rm $(ODIR)/*.o