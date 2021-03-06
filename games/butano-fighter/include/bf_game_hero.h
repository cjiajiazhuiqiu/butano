/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BF_GAME_HERO_H
#define BF_GAME_HERO_H

#include "btn_deque.h"
#include "btn_music_actions.h"
#include "btn_sprite_actions.h"
#include "btn_sprite_animate_actions.h"
#include "btn_sprite_palette_actions.h"
#include "btn_sprite_affine_mat_actions.h"
#include "bf_status.h"
#include "bf_game_explosion.h"

namespace bf
{
    enum class scene_type;
    class butano_background;
}

namespace bf::game
{

class objects;
class enemies;
class hero_bomb;
class background;
class enemy_bullets;

class hero
{

public:
    hero(const btn::camera_ptr& camera, status& status);

    [[nodiscard]] bool alive() const
    {
        return ! _death_counter;
    }

    [[nodiscard]] int level() const
    {
        return _status.level();
    }

    [[nodiscard]] int experience() const
    {
        return _status.experience();
    }

    [[nodiscard]] btn::fixed next_level_experience_ratio() const
    {
        return _status.next_level_experience_ratio();
    }

    [[nodiscard]] bool add_experience(int experience)
    {
        return _status.add_experience(experience);
    }

    [[nodiscard]] int bombs_count() const
    {
        return _status.bombs_count();
    }

    [[nodiscard]] const btn::fixed_point& body_position() const
    {
        return _body_position;
    }

    [[nodiscard]] const btn::fixed_point& weapon_position() const
    {
        return _weapon_position;
    }

    [[nodiscard]] bool shooting() const
    {
        return _shooting;
    }

    void set_shooting(bool shooting)
    {
        _shooting = shooting;
    }

    [[nodiscard]] bool looking_down() const
    {
        return _looking_down;
    }

    void show_shoot(btn::color fade_color);

    [[nodiscard]] bool throw_bomb()
    {
        return _status.throw_bomb();
    }

    btn::optional<scene_type> update(const hero_bomb& hero_bomb, const enemies& enemies, enemy_bullets& enemy_bullets,
                                     objects& objects, background& background, butano_background& butano_background,
                                     btn::camera_ptr& camera);

private:
    struct body_snapshot_type
    {
        btn::fixed_point position;
        int16_t graphics_index = 0;
        bool looking_down = false;
    };

    constexpr static const int body_snapshots_count = 16;

    status& _status;
    const btn::sprite_item& _body_sprite_item;
    btn::vector<btn::sprite_ptr, 3> _body_shadows;
    btn::sprite_cached_animate_action<2> _body_sprite_animate_action;
    btn::deque<body_snapshot_type, body_snapshots_count> _body_snapshots;
    btn::fixed_point _body_position;
    btn::fixed_point _weapon_position;
    btn::sprite_ptr _weapon_sprite;
    btn::sprite_ptr _shield_sprite;
    btn::sprite_affine_mat_ptr _bomb_sprites_affine_mat;
    btn::optional<btn::sprite_rotate_by_action> _body_rotate_action;
    btn::optional<btn::sprite_palette_fade_to_action> _body_palette_fade_action;
    btn::optional<btn::sprite_move_to_action> _weapon_move_action;
    btn::optional<btn::sprite_rotate_by_action> _weapon_rotate_action;
    btn::optional<btn::sprite_palette_fade_to_action> _weapon_palette_fade_action;
    btn::optional<btn::sprite_visible_toggle_action> _shield_toggle_action;
    btn::optional<btn::sprite_rotate_by_action> _shield_rotate_action;
    btn::vector<btn::sprite_move_by_action, constants::max_hero_bombs> _bomb_sprite_move_actions;
    btn::optional<btn::sprite_affine_mat_rotate_by_action> _bomb_sprites_rotate_action;
    btn::optional<btn::music_volume_to_action> _music_volume_action;
    btn::optional<explosion> _death_explosion;
    int _show_shoot_counter = 0;
    int _scale_weapon_counter = 0;
    int _body_shadows_counter = 0;
    int _shield_counter = 0;
    int _death_counter = 0;
    bool _shooting = false;
    bool _looking_down = false;
    bool _stage_done = false;

    void _move(btn::camera_ptr& camera);

    void _animate_alive(const btn::fixed_point& old_body_position);

    void _show_shield(int old_bombs_count, const btn::camera_ptr& camera, background& background);

    void _animate_shield(background& background);

    btn::optional<scene_type> _animate_dead(const btn::camera_ptr& camera, background& background,
                                            butano_background& butano_background);
};

}

#endif
