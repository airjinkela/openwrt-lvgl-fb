#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

// #include <mtk-spi.h>
#include <cJSON.h>
// #include <lvgl.h>
#include "lib/lvgl/lvgl.h"
#include "lib/lvgl/demos/lv_demos.h"

#define FBDEV "/dev/fb0"

static lv_display_t *get_display(void)
{
    lv_display_t *disp;
#if 0
    disp = lv_sdl_window_create(800, 800);
#else
    disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, FBDEV);
#endif
    if (disp == NULL) {
        return NULL;
    }
    return disp;
}

#define MARK_SIZE 5

static lv_obj_t * create_mark(lv_obj_t * parent, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t * mark = lv_obj_create(parent);
    lv_obj_set_size(mark, MARK_SIZE, MARK_SIZE);
    lv_obj_set_pos(mark, x, y);

    lv_obj_clear_flag(mark, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(mark, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(mark, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(mark, 0, 0);
    lv_obj_set_style_radius(mark, 0, 0);

    return mark;
}

void create_positioning_screen(void)
{
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_coord_t w = lv_disp_get_hor_res(NULL);
    lv_coord_t h = lv_disp_get_ver_res(NULL);

    // 左上
    create_mark(scr, 0, 0);

    // 右上
    create_mark(scr, w - MARK_SIZE, 0);

    // 左下
    create_mark(scr, 0, h - MARK_SIZE);

    // 右下
    create_mark(scr, w - MARK_SIZE, h - MARK_SIZE);

    lv_scr_load(scr);
}

int main(int argc, char **argv) {
    lv_init();
    lv_display_t *disp = get_display();
    lv_disp_set_default(disp);
    lv_demo_benchmark();
    // create_positioning_screen();

    uint32_t idle_time;
    while (true) {

        /* Returns the time to the next timer execution */
        idle_time = lv_timer_handler();
        usleep(idle_time * 1000);
    }
}
