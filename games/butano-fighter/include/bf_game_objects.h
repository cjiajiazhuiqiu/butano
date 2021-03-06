/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BF_GAME_OBJECTS_H
#define BF_GAME_OBJECTS_H

#include "btn_deque.h"
#include "btn_optional.h"
#include "btn_forward_list.h"
#include "bf_game_gem.h"
#include "bf_constants.h"
#include "bf_game_object.h"
#include "bf_game_object_message.h"

namespace bf::game
{

class objects
{

public:
    struct bomb_check_result
    {
        int experience_to_add = 0;
        bool add_bomb = false;
    };

    explicit objects(const btn::sprite_palette_ptr& flash_palette);

    [[nodiscard]] bool check_hero_weapon(const btn::fixed_rect& hero_rect, const btn::camera_ptr& camera);

    [[nodiscard]] bomb_check_result check_hero_bomb(const btn::fixed_rect& hero_rect, bool max_hero_bombs,
                                                    int hero_level, const btn::camera_ptr& camera);

    [[nodiscard]] int check_gem(const btn::fixed_rect& hero_rect, int hero_level, const btn::camera_ptr& camera);

    void spawn_hero_weapon_with_sound(const btn::fixed_point& position, int hero_level,
                                      const btn::camera_ptr& camera);

    void spawn_hero_weapon_without_sound(const btn::fixed_point& position, int hero_level,
                                         const btn::camera_ptr& camera);

    void spawn_hero_bomb_with_sound(const btn::fixed_point& position, const btn::camera_ptr& camera);

    void spawn_hero_bomb_without_sound(const btn::fixed_point& position, const btn::camera_ptr& camera);

    void spawn_gem(const btn::fixed_point& position, const btn::camera_ptr& camera);

    void update();

private:
    btn::sprite_palette_ptr _flash_palette;
    btn::sprite_palette_ptr _gem_palette;
    btn::optional<object> _hero_weapon;
    btn::optional<object> _hero_bomb;
    btn::array<btn::sprite_tiles_ptr, 4> _gem_tiles;
    btn::forward_list<gem, constants::max_gems> _gems;
    btn::deque<object_message, constants::max_object_messages> _messages;
};

}

#endif
