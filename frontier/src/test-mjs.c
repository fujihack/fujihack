// Basic Test JS module for mJS https://github.com/petabyt/frontier-mjs
#include <app/js/mjs.h>

int test_mjs() {
	sys_load_app("app/js/js.elf");

	uint8_t *s = sym("mjs_create");
	sys_debug("Test sym for push inst: %02X %02X %02X %02X\n", s[0], s[1], s[2], s[3]);

	typedef struct mjs *td_mjs_create();
	td_mjs_create* _mjs_create = (td_mjs_create*)sym("mjs_create");

	typedef mjs_err_t td_mjs_exec(struct mjs *, const char *src, mjs_val_t *res);
	td_mjs_exec* _mjs_exec = (td_mjs_exec*)sym("mjs_exec");

	typedef const char *td_mjs_strerror(struct mjs *mjs, enum mjs_err err);
	td_mjs_strerror* _mjs_strerror = (td_mjs_strerror*)sym("mjs_strerror");

	typedef void td_mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym);
	td_mjs_set_ffi_resolver* _mjs_set_ffi_resolver = (td_mjs_set_ffi_resolver*)sym("mjs_strerror");

	typedef int td_mjs_get_int(struct mjs *mjs, mjs_val_t v);
	td_mjs_get_int* _mjs_get_int = (td_mjs_get_int*)sym("mjs_get_int");

	struct mjs *js = _mjs_create();
	_mjs_set_ffi_resolver(js, sym);

	mjs_val_t temp = 0;

	int rc = _mjs_exec(js, "function main() {return 123;} main();", &temp);
	sys_debug("JS: %s rc = %d\n", (char *)_mjs_strerror(js, rc), _mjs_get_int(js, temp));

	return 0;
}
