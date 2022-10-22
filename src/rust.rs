#![no_std]

#[no_mangle]
fn panic() {
	loop {}
}

#[no_mangle]
pub fn foo_bar() -> u32 {	
	return 123;
}
