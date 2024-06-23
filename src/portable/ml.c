// Magic Lantern built-in runtime support
// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdio.h>
#include <string.h>

int ml_menu_add() {
	puts("menu_add");
	return 0;
}

int ml_task_create() {
	return -1;
}

int ml_mem_malloc() {
	return -1;
}

void *ml_sym(char *name) {
	if (!strcmp(name, "menu_add")) {
		return ml_menu_add;
	} else if (!strcmp(name, "task_create")) {
		return ml_task_create;
	} else if (!strcmp(name, "__mem_malloc")) {
		return ml_mem_malloc;
	}

	return NULL;
}
