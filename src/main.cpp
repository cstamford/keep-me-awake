#include <Windows.h>
#include <time.h>

#include <chrono>
#include <thread>

// With these settings, we will wiggle every [5, 30] seconds.

#define WIGGLE_MIN_SECONDS 5
#define WIGGLE_MAX_SECONDS 30

// With these settings, we will wiggle between:
//
// 9 am + [0, 30 mins]
// to
// 12 midday + [0, 15 mins]
// then a break until
// 12:30 midday + [0, 15 mins]
// to
// 5 pm + [0, 60 mins]
//

#define WIGGLE_START_TIME 9.0f // 9 am
#define WIGGLE_START_TIME_VARIANCE 0.5f // 30 mins
#define WIGGLE_BREAK_START_TIME 12.0f // 12 midday
#define WIGGLE_BREAK_START_TIME_VARIANCE 0.25f // 15 mins
#define WIGGLE_BREAK_END_TIME 12.5f // 12:30 midday
#define WIGGLE_BREAK_END_TIME_VARIANCE 0.25f // 15 mins
#define WIGGLE_END_TIME 17.0f // 5 pm
#define WIGGLE_END_TIME_VARIANCE 1.0f // 60 mins

// By default, we don't wiggle on weekends, and we do take breaks.

#define WIGGLE_ON_WEEKENDS 0
#define WIGGLE_HAS_BREAK 1

bool is_time_valid()
{
    time_t cur_time = time(nullptr);
    tm cur_time_local;
    localtime_s(&cur_time_local, &cur_time);

#if WIGGLE_ON_WEEKENDS == 0
    if (cur_time_local.tm_wday == 0 || cur_time_local.tm_wday == 6)
    {
        return false;
    }
#endif

    static int s_day = -1;
    static float s_offset_start;
    static float s_offset_mid_first;
    static float s_offset_mid_last;
    static float s_offset_end;

    if (cur_time_local.tm_wday != s_day)
    {
        s_day = cur_time_local.tm_wday;
        s_offset_start = (rand() % (int)(WIGGLE_START_TIME_VARIANCE * 60.0f)) / 60.0f;
        s_offset_mid_first = (rand() % (int)(WIGGLE_BREAK_START_TIME_VARIANCE * 60.0f)) / 60.0f;
        s_offset_mid_last = (rand() % (int)(WIGGLE_BREAK_END_TIME_VARIANCE * 60.0f)) / 60.0f;
        s_offset_end = (rand() % (int)(WIGGLE_END_TIME_VARIANCE * 60.0f)) / 60.0f;
    }

    float start = WIGGLE_START_TIME + s_offset_start;
    float mid_first = WIGGLE_BREAK_START_TIME + s_offset_mid_first;
    float mid_last = WIGGLE_BREAK_END_TIME + s_offset_mid_last;
    float end = WIGGLE_END_TIME + s_offset_end;

    float cur_time_float = cur_time_local.tm_hour + cur_time_local.tm_min / 60.0f;

    if (cur_time_float < start)
    {
        return false;
    }

#if WIGGLE_HAS_BREAK == 1
    if (cur_time_float > mid_first && cur_time_float < mid_last)
    {
        return false;
    }
#endif

    if (cur_time_float > end)
    {
        return false;
    }

    return true;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    srand((unsigned int)time(nullptr));

    while (true)
    {
        if (is_time_valid())
        {
            static int s_dir = 1;

            INPUT input;
            input.type = INPUT_MOUSE;
            input.mi.dx = s_dir * 4;
            input.mi.dy = s_dir * 4;
            input.mi.mouseData = 0;
            input.mi.dwFlags = MOUSEEVENTF_MOVE;
            input.mi.time = 0;
            input.mi.dwExtraInfo = 0;

            SendInput(1, &input, sizeof(input));

            s_dir = -s_dir;
        }

        int sleep_for = WIGGLE_MIN_SECONDS + (rand() % (WIGGLE_MAX_SECONDS - WIGGLE_MIN_SECONDS));
        std::this_thread::sleep_for(std::chrono::seconds(sleep_for));
    }
}
