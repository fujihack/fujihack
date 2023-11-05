#include <stdio.h>
#include <string.h>

#include "biblec.h"

// Split chars and ints from string
int strToInt(char *buf) {
	int ret = 0;
	for (; *buf != '\0'; buf++) {
		ret *= 10;
		ret += *buf - '0';
	}

	return ret;
}

// Parse BibleC index file, see 
// https://api.heb12.com/translations/biblec/web.i
// TODO: better error detection
int biblec_parse(struct BiblecTranslation *translation, char *indexLocation) {
	FILE *index = fopen(indexLocation, "r");
	if (index == NULL) {
		return BIBLEC_FILE_ERROR;
	}

	// If location is never filled in, then assume text
	// file location is in the same folder as the index file.
	strncpy(translation->location, indexLocation, MAX_LOCATION - 1);
	translation->location[strlen(indexLocation) - 1] = 't';

	int book = 0;
	char line[INDEX_MAX_LENGTH];
	while (fgets(line, INDEX_MAX_LENGTH, index) != NULL) {
		// Remove trailing breakline
		strtok(line, "\n");

		// Pointer to line content
		char *contents = line + 1;

		// Make a duplicate for manipulation
		char afterFirst[INDEX_MAX_LENGTH];
		strcpy(afterFirst, contents);

		if (line[0] == '#') {
			// Copy before ':' to afterFirst
			int c = 0;
			while (*contents != ':') {
				afterFirst[c] = *contents;
				contents++;
				c++;
			}

			afterFirst[c] = '\0';
			contents++; // Increment to skip ':'

			if (!strcmp(afterFirst, "name")) {
				strncpy(translation->name, contents, MAX_NAME - 1);
			} else if (!strcmp(afterFirst, "lang")) {
				strncpy(translation->lang, contents, MAX_LANG - 1);
			} else if (!strcmp(afterFirst, "location")) {
				strncpy(translation->location, contents, MAX_LOCATION - 1);
			} else if (!strcmp(afterFirst, "length")) {
				translation->length = strToInt(contents);
			}
		} else if (line[0] == '@') {
			char *bookInfo = strtok(afterFirst, " ");
			strcpy(translation->books[book].name, afterFirst);
			bookInfo = strtok(NULL, " ");
			translation->books[book].start = strToInt(bookInfo);
			bookInfo = strtok(NULL, " ");
			translation->books[book].length = strToInt(bookInfo);
		} else if (line[0] == '!') {
			// Loop through chapters and set them in the struct
			int currentChapter = 0;
			char *chapter = strtok(afterFirst, " ");
			while (chapter != NULL) {
				translation->books[book].chapters[currentChapter] = strToInt(chapter);
				chapter = strtok(NULL, " ");
				currentChapter++;
			}

			book++;
		}

		// Any other line start chars will be skipped
	}

	fclose(index);
	return 0;
}
int getBookID(struct BiblecTranslation *translation, char *book) {
	int bookID = BIBLEC_BOOK_ERROR;
	for (int i = 0; i < translation->length; i++) {
		if (!strcmp(book, translation->books[i].name)) {
			bookID = i;
		}
	}

	return bookID;
}

int biblec_next(struct BiblecReader *reader) {
	// Reached end of requested verses
	if (reader->linesRead > reader->to) {
		return 0;
	}

	// End of file
	if (fgets(reader->result, VERSE_LENGTH, reader->file) == NULL) {
		return 0;
	}

	strtok(reader->result, "\n"); // Strip '\n'
	reader->linesRead++;
	
	return 1;
}

// Create a new reader structure
int biblec_new(struct BiblecReader *reader, struct BiblecTranslation *translation, 
		char *book, int chapter, int verse, int to) {
	int c;

	reader->file = fopen(translation->location, "r");
	if (reader->file == NULL) {
		return BIBLEC_FILE_ERROR;
	}

	int bookID = getBookID(translation, book);
	if (bookID == BIBLEC_BOOK_ERROR) {
		return BIBLEC_BOOK_ERROR;
	}

	if (translation->books[bookID].length < chapter) {
		return BIBLEC_CHAPTER_ERROR;
	}

	// Grab start line, and add until specified chapter is reached.
	int line = translation->books[bookID].start;
	for (c = 0; c < chapter - 1; c++) {
		line += translation->books[bookID].chapters[c];
	}

	// When 0 is passed for "to", grab the entire chapter.
	// Else, "to" refers to how many verses to
	// count in the struct.
	if (to == 0) {
		to = translation->books[bookID].chapters[c] - 1;
	} else {
		to -= verse;
	}
	
	if (to < 0) {
		return BIBLEC_VERSE_ERROR;
	}

	// Add the line over to the specific verse
	line += verse - 1;

	reader->book = book;
	reader->chapter = chapter;
	reader->verse = verse;
	reader->to = to;

	reader->linesRead = 0;

	// Loop through until it gets to the line
	// This is fastest out of tested fgetc, fread
	char verseText[VERSE_LENGTH];
	for (int i = 0; i != line; i++) {
		if (fgets(verseText, VERSE_LENGTH, reader->file) == NULL) {
			return FILE_OVERFLOW;
		}
	}

	return 0;
}

void biblec_close(struct BiblecReader *reader) {
	fclose(reader->file);
}
