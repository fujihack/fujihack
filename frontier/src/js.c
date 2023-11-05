// Full abstraction layer over Javascript engine
#include <stdlib.h>
#include <mjs.h>
#include <sym.h>

struct mjs *mjs = NULL;
char js_buffer[32];

int js_init() {
	mjs = mjs_create();
	mjs_set_ffi_resolver(mjs, sym);
	mjs_exec(mjs, "let help = \"TODO: Help\";", NULL);
	return 0;
}

char *js_run(char *text) {
	mjs_val_t res = 0;
	mjs_own(mjs, &res);

	mjs_err_t err = mjs_exec(mjs, text, &res);
	if (err != MJS_OK) {
		return (char *)mjs_strerror(mjs, err);
	}

	mjs_sprintf(res, mjs, js_buffer, 32);

	return js_buffer;
}
