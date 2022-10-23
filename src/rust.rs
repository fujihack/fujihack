#[allow(dead_code)]
pub mod c {
	extern {
		pub fn fuji_screen_write(str: *const u8, x: u32, y: u32, fg: u32, bg: u32);
	}
}

#[no_mangle]
fn panic() {
	loop {}
}

#[no_mangle]
pub fn foo_bar() -> u32 {
	unsafe {
		c::fuji_screen_write("Hello, Rust\0".as_ptr(), 1, 1, 0, 7);
	}

	return 0;
}
