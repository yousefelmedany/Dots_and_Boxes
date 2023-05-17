#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

#ifdef _WIN32
#include <windows.h>    // for win32 API functions
#include <io.h>         // for _get_osfhandle()
#else
#define _POSIX_SOURCE   // enable POSIX extensions in standard library headers
#include <unistd.h>     // for isatty()
#endif

#include <stdlib.h>
#include <stdio.h>

// use an enum for platform-independent interface:
typedef enum TextColor
{
    TC_BLACK = 0,
    TC_BLUE = 1,
    TC_GREEN = 2,
    TC_CYAN = 3,
    TC_RED = 4,
    TC_MAGENTA = 5,
    TC_BROWN = 6,
    TC_LIGHTGRAY = 7,
    TC_DARKGRAY = 8,
    TC_LIGHTBLUE = 9,
    TC_LIGHTGREEN = 10,
    TC_LIGHTCYAN = 11,
    TC_LIGHTRED = 12,
    TC_LIGHTMAGENTA = 13,
    TC_YELLOW = 14,
    TC_WHITE = 15
} TextColor;

// set output color on the given stream:
void setTextColor(FILE *stream, TextColor color);


#ifdef _WIN32

void setTextColor(FILE *stream, TextColor color)
{
    int outfd = fileno(stream);
    HANDLE out = (HANDLE)_get_osfhandle(outfd);
    DWORD outType = GetFileType(out);
    DWORD mode;
    if (outType == FILE_TYPE_CHAR && GetConsoleMode(out, &mode))
    {
        // we're directly outputting to a win32 console if the file type
        // is FILE_TYPE_CHAR and GetConsoleMode() returns success

        SetConsoleTextAttribute(out, color);
        // the enum constants are defined to the same values
        // SetConsoleTextAttribute() uses, so just pass on.
    }
}

#else

static const char *ansiColorSequences[] =
{
    "\x1B[0;30m",
    "\x1B[0;34m",
    "\x1B[0;32m",
    "\x1B[0;36m",
    "\x1B[0;31m",
    "\x1B[0;35m",
    "\x1B[0;33m",
    "\x1B[0;37m",
    "\x1B[1;30m",
    "\x1B[1;34m",
    "\x1B[1;32m",
    "\x1B[1;36m",
    "\x1B[1;31m",
    "\x1B[1;35m",
    "\x1B[1;33m",
    "\x1B[1;37m"
};

static const char *ansiColorTerms[] =
{
    "xterm",
    "rxvt",
    "vt100",
    "linux",
    "screen",
    0
    // there are probably missing a few others
};

// get current terminal and check whether it's in our list of terminals
// supporting ANSI colors:
static int isAnsiColorTerm(void)
{
    char *term = getenv("TERM");
    for (const char **ansiTerm = &ansiColorTerms[0]; *ansiTerm; ++ansiTerm)
    {
        int match = 1;
        const char *t = term;
        const char *a = *ansiTerm;
        while (*a && *t)
        {
            if (*a++ != *t++)
            {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

void setTextColor(FILE *stream, TextColor color)
{
    int outfd = fileno(stream);
    if (isatty(outfd) && isAnsiColorTerm())
    {
        // we're directly outputting to a terminal supporting ANSI colors,
        // so send the apppropriate sequence:

    }
}

#endif

#endif // COLORS_H_INCLUDED
