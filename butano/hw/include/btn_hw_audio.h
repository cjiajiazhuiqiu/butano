/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BTN_HW_AUDIO_H
#define BTN_HW_AUDIO_H

#include "btn_common.h"

namespace btn::hw::audio
{
    void init();

    void enable();

    void disable();

    [[nodiscard]] bool music_playing();

    void play_music(int id, int volume, bool loop);

    void stop_music();

    void pause_music();

    void resume_music();

    [[nodiscard]] int music_position();

    void set_music_position(int position);

    void set_music_volume(int volume);

    void play_sound(int priority, int id);

    void play_sound(int priority, int id, int volume, int speed, int panning);

    void stop_all_sounds();

    void disable_vblank_handler();

    void commit();

    void enable_vblank_handler();
}

#endif
