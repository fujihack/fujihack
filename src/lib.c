#ifndef GIMMIE_H
#define GIMMIE_H

// This is gimmie.h, an old project of mine.
// You define stuff to get a function.
#define GIMMIE_MEMCPY
#define GIMMIE_STRLEN
#define GIMMIE_MEMSET

/* A basic no nonsense divmod function if
 * needed (probably never) */
#ifdef GIMMIE_GDIVMOD
int gdivmod(int a, int b, int o) {
	int di = 0;
	int re = 0;
	while (a != 0) {
		re++;
		di = 0;
		while (di != b) {
			if (a == 0) {
				break;
			}
			
			di++;
			a--;
		}
	}

	if (di == b) {
		di = 0;
	} else {
		re--;
	}
	
	if (o) {
		return di;
	}

	return re;
}
#endif

#ifdef GIMMIE_STRLEN
int strlen(char *buffer) {
	int a = 0;
	while (*buffer != 0) {
		buffer++;
		a++;
	}

	return a;
}
#endif

#ifdef GIMMIE_STRCMP
int strcmp(char *s1, char *s2) {
	while(*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}

	return *(unsigned char*)s1 - *(unsigned char*)s2;
}
#endif

#ifdef GIMMIE_MEMCPY
void *memcpy(void* dest, const void* src, int count) {
	char* dst8 = (char*)dest;
	char* src8 = (char*)src;
	while (count--) {
		*dst8++ = *src8++;
	}
	
	return dest;
}
#endif

#ifdef GIMMIE_MEMSET
void *memset(void *dest, int val, int len) {
	unsigned char *ptr = dest;
	while (len-- > 0) {
		*ptr++ = val;
	}
	
	return dest;
}
#endif

#endif
