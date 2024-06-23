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
	return 123;
}
