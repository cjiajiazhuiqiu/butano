/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BTN_LOG_BACKEND_H
#define BTN_LOG_BACKEND_H

#include "btn_common.h"

/**
 * @def BTN_LOG_BACKEND_MGBA
 *
 * mGBA emulator (https://mgba.io) log backend.
 *
 * @ingroup log
 */
#define BTN_LOG_BACKEND_MGBA        0

/**
 * @def BTN_LOG_BACKEND_NOCASHGBA
 *
 * No$gba emulator (https://problemkaputt.de/gba.htm) log backend.
 *
 * @ingroup log
 */
#define BTN_LOG_BACKEND_NOCASHGBA   1

/**
 * @def BTN_LOG_BACKEND_VBA
 *
 * VisualBoyAdvance emulator (https://en.wikipedia.org/wiki/VisualBoyAdvance) log backend.
 *
 * It crashes on hardware and on other emulators!
 *
 * @ingroup log
 */
#define BTN_LOG_BACKEND_VBA         2

#endif
