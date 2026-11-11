#pragma once

#include <stdint.h>

#ifndef APP_ID_DEFAULT
#define APP_ID_DEFAULT 0xFF
#endif

#ifndef APP_ID_P1
#define APP_ID_P1 APP_ID_DEFAULT
#endif

#ifndef APP_ID_P2
#define APP_ID_P2 APP_ID_DEFAULT
#endif

#ifndef APP_ID_POWER
#define APP_ID_POWER APP_ID_DEFAULT
#endif

#ifndef APP_ID_TSKMNGR
#define APP_ID_TSKMNGR APP_ID_DEFAULT
#endif

static_assert(APP_ID_DEFAULT <= UINT8_MAX, "APP_ID_DEFAULT must fit in a byte");
static_assert(APP_ID_P1 <= UINT8_MAX, "APP_ID_P1 must fit in a byte");
static_assert(APP_ID_P2 <= UINT8_MAX, "APP_ID_P2 must fit in a byte");
static_assert(APP_ID_POWER <= UINT8_MAX, "APP_ID_POWER must fit in a byte");
static_assert(APP_ID_TSKMNGR <= UINT8_MAX, "APP_ID_TSKMNGR must fit in a byte");
static_assert(APP_ID_P1 == APP_ID_DEFAULT || APP_ID_P2 == APP_ID_DEFAULT || APP_ID_P1 != APP_ID_P2, "Application IDs must be unique");
static_assert(APP_ID_P1 == APP_ID_DEFAULT || APP_ID_POWER == APP_ID_DEFAULT || APP_ID_P1 != APP_ID_POWER, "Application IDs must be unique");
static_assert(APP_ID_P2 == APP_ID_DEFAULT || APP_ID_POWER == APP_ID_DEFAULT || APP_ID_P2 != APP_ID_POWER, "Application IDs must be unique");
static_assert(APP_ID_P1 == APP_ID_DEFAULT || APP_ID_TSKMNGR == APP_ID_DEFAULT || APP_ID_P1 != APP_ID_TSKMNGR, "Application IDs must be unique");
static_assert(APP_ID_P2 == APP_ID_DEFAULT || APP_ID_TSKMNGR == APP_ID_DEFAULT || APP_ID_P2 != APP_ID_TSKMNGR, "Application IDs must be unique");
static_assert(APP_ID_POWER == APP_ID_DEFAULT || APP_ID_TSKMNGR == APP_ID_DEFAULT || APP_ID_POWER != APP_ID_TSKMNGR, "Application IDs must be unique");
