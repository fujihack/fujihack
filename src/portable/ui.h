#ifndef UI_H
#define UI_H

typedef int ui_renderer();

int ui_frame(ui_renderer *);
int ui_reset();
int ui_process_key();
int ui_update(ui_renderer *renderer);

void ui_container(int x, int y, int width, int height, int color);
void ui_end_container();
int ui_button(char *text);
void ui_text(char *text, int color);

#endif
