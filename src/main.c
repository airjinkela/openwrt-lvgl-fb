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
#if LV_USE_SDL
    disp = lv_sdl_window_create(428, 142);
#else
    disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, FBDEV);
#endif
    if (disp == NULL) {
        return NULL;
    }
    return disp;
}

int main(int argc, char **argv) {
    if (argc < 2){
        return 0;
    }

    char *video_path = argv[1];

    lv_init();
    lv_display_t *disp = get_display();
    lv_disp_set_default(disp);

    printf("%s", video_path);
    // lv_demo_benchmark();

    lv_obj_t * player = lv_ffmpeg_player_create(lv_screen_active());
    lv_ffmpeg_player_set_src(player, video_path);
    lv_ffmpeg_player_set_auto_restart(player, false);
    lv_ffmpeg_player_set_cmd(player, LV_FFMPEG_PLAYER_CMD_START);
    lv_obj_center(player);

    uint32_t idle_time;
    while (true) {
        /* Returns the time to the next timer execution */
        idle_time = lv_timer_handler();
        usleep(idle_time * 1000);
    }
    return 0;
}
