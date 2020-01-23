#ifndef BTN_HW_IRQ_H
#define BTN_HW_IRQ_H

#include "tonc.h"
#include "btn_common.h"

namespace btn::hw::irq
{
    enum class id
    {
        VBLANK,
        HBLANK,
        VCOUNT,
        TIMER0,
        TIMER1,
        TIMER2,
        TIMER3,
        SERIAL,
        DMA0,
        DMA1,
        DMA2,
        DMA3,
        KEYPAD,
        GAMEPAK
    };

    inline void init()
    {
        irq_init(nullptr);
    }

    inline void add(id irq_id, void(*isr)())
    {
        irq_add(eIrqIndex(irq_id), isr);
    }

    inline void remove(id irq_id)
    {
        irq_delete(eIrqIndex(irq_id));
    }
}

#endif
