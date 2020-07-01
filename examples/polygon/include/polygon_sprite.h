#ifndef POLYGON_SPRITE_H
#define POLYGON_SPRITE_H

#include "btn_array.h"
#include "btn_fixed.h"
#include "btn_vector.h"
#include "btn_display.h"
#include "btn_span_fwd.h"
#include "btn_sprite_ptr.h"
#include "btn_sprite_hblank_effects.h"

class polygon;

class polygon_sprite
{

public:
    polygon_sprite(const polygon& polygon, int graphics_index, int z_order);

    polygon_sprite(const btn::span<const polygon*>& polygons, int graphics_index, int z_order);

    polygon_sprite(const polygon_sprite& other) = delete;

    polygon_sprite& operator=(const polygon_sprite& other) = delete;

    void reload_polygons()
    {
        _update = true;
    }

    void update();

private:
    struct hline
    {
        int ixl = btn::display::width();
        int ixr = 0;
    };

    btn::vector<const polygon*, 2> _polygons;
    btn::sprite_ptr _sprite;
    btn::array<btn::fixed, btn::display::height()> _vertical_values;
    btn::sprite_position_hblank_effect_ptr _vertical_hblank_effect;
    btn::array<btn::fixed, btn::display::height()> _horizontal_values;
    btn::sprite_position_hblank_effect_ptr _horizontal_hblank_effect;
    bool _update = true;

    BTN_CODE_IWRAM static void _draw_line(const btn::fixed_point& from, const btn::fixed_point& to, hline* hlines);

    BTN_CODE_IWRAM static void _setup_attributes(const hline* hlines, btn::fixed* vertical_values,
                                                 btn::fixed* horizontal_values);
};

#endif