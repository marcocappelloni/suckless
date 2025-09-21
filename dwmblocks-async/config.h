#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER " | "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 0

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

/*    X("", "sb-mail", 600, 1)  \
    X("", "sb-music", 0, 2)   \
    X("", "sb-disk", 1800, 3) \
    X("", "sb-memory", 10, 4) \
    X("", "sb-loadavg", 5, 5) \
    X("", "sb-mic", 0, 6)     \
    X("", "sb-record", 0, 7)  \
    X("", "sb-volume", 0, 8)  \
    X("", "date '+%H:%M:%S'", 5, 6)
*/
// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
    X("", "/home/maky/packages/suckless/dwmblocks-async/scripts/CPU.sh", 5, 1) \
    X("", "/home/maky/packages/suckless/dwmblocks-async/scripts/root.sh", 60, 2) \
    X("", "/home/maky/packages/suckless/dwmblocks-async/scripts/home.sh", 60, 3) \
    X("", "/home/maky/packages/suckless/dwmblocks-async/scripts/memory.sh", 5, 4) \
    X("", "/home/maky/packages/suckless/dwmblocks-async/scripts/time.sh", 30, 5) \
    X("", "/home/maky/packages/suckless/dwmblocks-async/scripts/battery.sh", 60, 6)

#endif  // CONFIG_H
