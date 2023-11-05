// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
// Goal: Create a system that can temporarily patch memory - it should save the orig memory,
// store it, and be able to restore on demand.

#include <stdint.h>

enum Patches {
	// Standard memory patches
	PATCH_U8,
	PATCH_U16,
	PATCH_U32,
	PATCH_U64,
	PATCH_VAR,

	// Assembly branch inst patches	
	PATCH_JUMP,
	PATCH_CALL,

	// Patch a function - completely overwrite it and jump somewhere else, preserving args
	PATCH_FUNC,

	// Patch header of func to jump to another func - do stuff with args - then return as if
	// nothing happened. Includes API (?) to call orig function with new arguments
	PATCH_FUNC_STEALTH,
};

struct Patch {
	uintptr_t address;
	int type;
	int length;
	char data[];
};
