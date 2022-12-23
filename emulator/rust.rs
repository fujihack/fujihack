#[allow(dead_code)]
pub mod c {
	extern {
		pub fn fuji_screen_write(str: *const u8, x: u32, y: u32, fg: u32, bg: u32);
		pub fn iolog(str: *const u8);
	}
}

#[no_mangle]
fn __aeabi_unwind_cpp_pr0() {}

#[no_mangle]
fn panic() {
	loop {}
}

// Thanks to u/timerot Reddit
macro_rules! cstr {
    ($data:literal) => {
        &concat!($data, "\0").as_bytes()[0] as *const u8
    }
}

#[no_mangle]
pub fn foo_bar() -> u32 {
	unsafe {
		c::iolog(cstr!("Hello rust world"));
	}

	return 0;
}
