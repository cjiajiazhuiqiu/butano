/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BF_STATS_H
#define BF_STATS_H

#include "btn_vector.h"
#include "btn_sprite_ptr.h"
#include "btn_fixed_point.h"

namespace btn
{
    class sprite_text_generator;
}


namespace bf
{

class stats
{

public:
    enum class mode_type
    {
        DISABLED,
        SIMPLE,
        DETAILED
    };

    explicit stats(btn::sprite_text_generator& text_generator);

    [[nodiscard]] mode_type mode() const
    {
        return _mode;
    }

    void set_mode(mode_type mode);

    void update();

private:
    btn::sprite_text_generator& _text_generator;
    btn::vector<btn::sprite_ptr, 8> _static_text_sprites;
    btn::vector<btn::sprite_ptr, 3> _text_sprites;
    btn::fixed_point _text_position;
    btn::fixed _max_cpu_usage;
    mode_type _mode = mode_type::DISABLED;
    int _counter = 0;
};

}

#endif
