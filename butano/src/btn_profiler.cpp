/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "btn_profiler.h"

#if BTN_CFG_PROFILER_ENABLED
    #include "btn_timer.h"
    #include "btn_optional.h"
    #include "btn_unordered_map.h"

    namespace _btn::profiler
    {
        namespace
        {
            static_assert(BTN_CFG_PROFILER_MAX_ENTRIES > 0);
            static_assert(btn::power_of_two(BTN_CFG_PROFILER_MAX_ENTRIES));

            class static_data
            {

            public:
                ticks_map ticks_per_entry;
                btn::optional<btn::timer> current_timer;
                const char* current_id = nullptr;
                unsigned current_id_hash;
            };

            BTN_DATA_EWRAM static_data data;
        }

        void start(const char* id, unsigned id_hash)
        {
            BTN_ASSERT(id, "Id is null");
            BTN_ASSERT(! data.current_id, "There's already an active id: ", data.current_id);

            data.current_id = id;
            data.current_id_hash = id_hash;
            data.current_timer = btn::timer();
        }

        void stop()
        {
            BTN_ASSERT(data.current_id, "There's no active id");

            int timer_ticks = data.current_timer->elapsed_ticks();
            auto timer_ticks_64 = int64_t(timer_ticks);
            ticks& ticks = data.ticks_per_entry(data.current_id_hash, data.current_id);
            ticks.total += timer_ticks_64;
            ticks.max = btn::max(ticks.max, timer_ticks);
            data.current_id = nullptr;
        }

        const ticks_map& ticks_per_entry()
        {
            BTN_ASSERT(! data.current_id, "There's an active id: ", data.current_id);

            return data.ticks_per_entry;
        }

        void reset()
        {
            BTN_ASSERT(! data.current_id, "There's an active id: ", data.current_id);

            data.ticks_per_entry.clear();
        }
    }
#endif
