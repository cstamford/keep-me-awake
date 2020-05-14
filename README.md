keep-me-awake
=============

A Windows-only application that runs silently in the background, jiggling the mouse every now and then to keep your machine awake. Useful to avoid:

* Screensavers,
* Idle detection,
* Auto lock

## How to run it?

It's super simple. You just double click on the binary and away it goes, just like that. Want to shut it down? Close the binary in the task manager. Tray icons are for hipsters.

## How to configure it?

Edit the code.

You can change the wiggle interval to ensure that wiggling happens on your terms.

```cpp
// With these settings, we will wiggle every [5, 30] seconds.

#define WIGGLE_MIN_SECONDS 5
#define WIGGLE_MAX_SECONDS 30
```

There are a wide variety of configuration options for when wiggling should start and stop. There are even wiggle breaks, to ensure your mouse cursor is given a fair opportunity to rest up.

```cpp
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
```

Do you desire around-the-clock ~~profits~~ wiggles, you capitalist pig-dog? Simply change the wiggle options below.

```cpp
// By default, we don't wiggle on weekends, and we do take breaks.

#define WIGGLE_ON_WEEKENDS 0
#define WIGGLE_HAS_BREAK 1
```

## Alternative projects

Are you a dirty consumer peasant who does not speak the glorious language of C++, and therefore require pretty user interfaces bearing beautifully crafted sans serif-fonts? Look no further, for the following program, penned in the foul Unholy Text of C#, will offer you all that and more!

https://github.com/cerebrate/mousejiggler
