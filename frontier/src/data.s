# Combine lib.js and test.js
.align 4
.global all_js
all_js:
.incbin "lib.js"
.incbin "test.js"

# have the size of both as a 32 bit integer
.global all_js_size
.align 4
all_js_size:
.int all_js_size - all_js
