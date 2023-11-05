#ifndef BIBLEC_H
#define BIBLEC_H

#include <stdio.h>

// Size macros, for internal use only
#define MAX_BOOKS 66
#define MAX_CHAPTERS 151
#define INDEX_MAX_LENGTH 512
#define VERSE_LENGTH 1024
#define MAX_NAME 32
#define MAX_LANG 16
#define MAX_LOCATION 128
#define MAX_BOOK_NAME 64

enum Biblec_error {
	// Ensure compatibility for now
	FILE_NOT_FOUND = -1,
	BOOK_NOT_FOUND = -2,
	FILE_OVERFLOW = -3,
	FILE_ERROR = -4,
	BAD_CHAPTER = -5,
	VERSE_ERROR = -6,

	BIBLEC_FILE_ERROR = -1,
	BIBLEC_BOOK_ERROR = -2,
	BIBLEC_OVERFLOW = -3,
	BIBLEC_CHAPTER_ERROR = -4,
	BIBLEC_VERSE_ERROR = -5
};

struct BiblecReader {
	char *book;
	int chapter;
	int verse;
	int to;
	char result[VERSE_LENGTH];
	int linesRead;
	FILE *file;
};

struct BiblecTranslation {
	char name[MAX_NAME];
	char lang[MAX_LANG];
	char location[MAX_LOCATION];
	int length; // (in books)
	struct Book {
		char name[MAX_BOOK_NAME];
		int start;
		int chapters[MAX_CHAPTERS];
		int length; // (in chapters)
	}books[MAX_BOOKS];
};

int biblec_parse(struct BiblecTranslation *translation, char *indexLocation);
int biblec_next(struct BiblecReader *reader);
void biblec_close(struct BiblecReader *reader);

int biblec_new(
	struct BiblecReader *reader,
	struct BiblecTranslation *translation,
	char *book,
	int chapter,
	int verse,
	int to
);

#endif
