#pragma once

#include <stdint.h>

typedef struct
{
    /* Milliseconds from song start; lane is zero-based (K1=0 through K4=3). */
    uint32_t time_ms;
    uint8_t lane;
} GuitarHeroBeat;

typedef struct
{
    char title[24];
    const GuitarHeroBeat *beats;
    uint16_t beat_count;
} GuitarHeroSong;

extern const GuitarHeroSong guitarHeroSongs[];
extern const uint8_t guitarHeroSongCount;
