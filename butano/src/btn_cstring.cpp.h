/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "btn_cstring.h"

#include "btn_assert.h"
#include "../hw/include/btn_hw_memory.h"

namespace btn
{

void memcpy(void* destination, const void* source, int bytes)
{
    BTN_ASSERT(bytes >= 0, "Invalid bytes: ", bytes);
    BTN_ASSERT(destination, "Destination is null");
    BTN_ASSERT(source, "Source is null");

    hw::memory::copy_bytes(source, bytes, destination);
}

void memset(void* destination, uint8_t value, int bytes)
{
    BTN_ASSERT(bytes >= 0, "Invalid bytes: ", bytes);
    BTN_ASSERT(destination, "Destination is null");

    hw::memory::set_bytes(value, bytes, destination);
}

void memclear(void* destination, int bytes)
{
    BTN_ASSERT(bytes >= 0, "Invalid bytes: ", bytes);
    BTN_ASSERT(destination, "Destination is null");

    hw::memory::set_bytes(0, bytes, destination);
}

}
