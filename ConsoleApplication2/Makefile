CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
# На Linux iconv входит в glibc, отдельная библиотека не нужна.
# На macOS/FreeBSD добавьте: LDFLAGS = -liconv
LDFLAGS =
TARGET  = bibtree
SRC     = bibtree.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Тестовый прогон: два входных файла, поиск по префиксу "Cormen"
test: $(TARGET)
	./$(TARGET) refs1.bib refs2.bib -o output.bib -s "Cormen"
	@echo "--- Первые 30 строк output.bib ---"
	@head -30 output.bib

clean:
	rm -f $(TARGET) output.bib
