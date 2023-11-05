// mJS experiments, I hate JS
let E_LABEL = 1;
let E_CONTAINER = 2;

let COLOR_YELLOW = 0xded49e;
let COLOR_BLACK = 0;
let COLOR_WHITE = 0xffffff;
let COLOR_GREY = 0x626262;

let ui = {
	reset: ffi("void ui_reset()"),
	drawContainer: ffi("void ui_draw_container(int, int, int, int, int)"),
	endContainer: ffi("void ui_end_container()"),
	drawText: ffi("void ui_draw_text(char *, int)"),

	screen: [],

	addLabel: function(c, text) {
		let e = {type: E_LABEL, text: text, color: COLOR_BLACK};
		if (c === null) {
			this.screen[this.screen.length] = e;
		} else {
			c.children[c.children.length] = e;
		}

		return e;
	},

	addContainer: function(x, y, w, h, color) {
		let e = {type: E_CONTAINER, x: x, y: y, width: w, height: h, color: color, children: []};
		this.screen[this.screen.length] = e;
		return e;
	},
};

// TODO: Implement this
let label = ui.label("Hello Frontier");
ui.setContent(ui.container([
	label,
	ui.button("Hello", function() {
		ui.popup("Hello, World");
	}),
]));
