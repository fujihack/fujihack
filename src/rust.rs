// Basic low-level rust experiments
#[allow(dead_code)]
pub mod c {
	extern {
		pub fn fuji_screen_write(str: *const u8, x: u32, y: u32, fg: u32, bg: u32);
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
		c::fuji_screen_write(cstr!("Hello, World"), 1, 1, 0, 7);
	}

	return 0;
}
