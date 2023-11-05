// mJS bindings to Frontier, and polyfills

let io = {
	print: ffi("void uart_str(char *)"),
	msleep: ffi("void msleep(int)"),
	mouse_x: ffi("int sys_mouse_x()"),
	mouse_y: ffi("int sys_mouse_y()"),
};

let bmp = {
	clear: ffi("void bmp_clear(int)"),
	text: ffi("void font_print_string(int, int, char *, int)"),
	render: ffi("void bmp_apply()"),
	pixel: ffi("void bmp_pixel(int, int, int)"),
};

function String(number) {
	return JSON.stringify(number);
}
