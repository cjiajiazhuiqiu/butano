/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BTN_HW_BGS_H
#define BTN_HW_BGS_H

#include "btn_size.h"
#include "btn_memory.h"
#include "btn_regular_bg_builder.h"
#include "btn_hw_tonc.h"

namespace btn::hw::bgs
{
    class handle
    {

    public:
        uint16_t cnt;
        uint16_t hofs;
        uint16_t vofs;
    };

    [[nodiscard]] constexpr int count()
    {
        return 4;
    }

    inline void setup_regular(const regular_bg_builder& builder, handle& bg)
    {
        bg.cnt = uint16_t(BG_PRIO(builder.priority()) | (builder.mosaic_enabled() << 6));
    }

    inline void set_tiles_cbb(int tiles_cbb, uint16_t& bg_cnt)
    {
        BFN_SET(bg_cnt, tiles_cbb, BG_CBB);
    }

    inline void set_tiles_cbb(int tiles_cbb, handle& bg)
    {
        set_tiles_cbb(tiles_cbb, bg.cnt);
    }

    inline void set_map_sbb(int map_sbb, uint16_t& bg_cnt)
    {
        BFN_SET(bg_cnt, map_sbb, BG_SBB);
    }

    inline void set_map_sbb(int map_sbb, handle& bg)
    {
        set_map_sbb(map_sbb, bg.cnt);
    }

    inline void set_map_dimensions(const size& map_dimensions, handle& bg)
    {
        int size = (map_dimensions.width() > 32) + ((map_dimensions.height() > 32) * 2);
        BFN_SET(bg.cnt, size, BG_SIZE);
    }

    [[nodiscard]] inline palette_bpp_mode bpp_mode(const handle& bg)
    {
        return (bg.cnt & BG_8BPP) ? palette_bpp_mode::BPP_8 : palette_bpp_mode::BPP_4;
    }

    inline void set_bpp_mode(palette_bpp_mode bpp_mode, uint16_t& bg_cnt)
    {
        if(bpp_mode == palette_bpp_mode::BPP_8)
        {
            bg_cnt |= BG_8BPP;
        }
        else
        {
            bg_cnt &= ~BG_8BPP;
        }
    }

    inline void set_bpp_mode(palette_bpp_mode bpp_mode, handle& bg)
    {
        set_bpp_mode(bpp_mode, bg.cnt);
    }

    inline void set_x(int x, handle& bg)
    {
        bg.hofs = uint16_t(x);
    }

    inline void set_y(int y, handle& bg)
    {
        bg.vofs = uint16_t(y);
    }

    inline void set_priority(int priority, uint16_t& bg_cnt)
    {
        BFN_SET(bg_cnt, priority, BG_PRIO);
    }

    inline void set_priority(int priority, handle& bg)
    {
        set_priority(priority, bg.cnt);
    }

    [[nodiscard]] inline bool mosaic_enabled(const handle& bg)
    {
        return bg.cnt & BG_MOSAIC;
    }

    inline void set_mosaic_enabled(bool mosaic_enabled, uint16_t& bg_cnt)
    {
        if(mosaic_enabled)
        {
            bg_cnt |= BG_MOSAIC;
        }
        else
        {
            bg_cnt &= ~BG_MOSAIC;
        }
    }

    inline void set_mosaic_enabled(bool mosaic_enabled, handle& bg)
    {
        set_mosaic_enabled(mosaic_enabled, bg.cnt);
    }

    inline void commit(const handle* bgs_ptr)
    {
        const handle& bg0 = bgs_ptr[0];
        REG_BG0CNT = bg0.cnt;
        REG_BG0HOFS = bg0.hofs;
        REG_BG0VOFS = bg0.vofs;

        const handle& bg1 = bgs_ptr[1];
        REG_BG1CNT = bg1.cnt;
        REG_BG1HOFS = bg1.hofs;
        REG_BG1VOFS = bg1.vofs;

        const handle& bg2 = bgs_ptr[2];
        REG_BG2CNT = bg2.cnt;
        REG_BG2HOFS = bg2.hofs;
        REG_BG2VOFS = bg2.vofs;

        const handle& bg3 = bgs_ptr[3];
        REG_BG3CNT = bg3.cnt;
        REG_BG3HOFS = bg3.hofs;
        REG_BG3VOFS = bg3.vofs;
    }

    [[nodiscard]] inline uint16_t* regular_horizontal_position_register(int id)
    {
        return reinterpret_cast<uint16_t*>(REG_BASE + 0x0010 + (0x0004 * id));
    }

    [[nodiscard]] inline uint16_t* regular_vertical_position_register(int id)
    {
        return reinterpret_cast<uint16_t*>(REG_BASE + 0x0012 + (0x0004 * id));
    }

    [[nodiscard]] inline uint16_t* attributes_register(int id)
    {
        return reinterpret_cast<uint16_t*>(REG_BASE + 0x0008 + (0x0002 * id));
    }
}

#endif
