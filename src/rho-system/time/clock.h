#ifndef RHO_SYSTEM_TIME_CLOCK_H
#define RHO_SYSTEM_TIME_CLOCK_H

#include "import.h"

typedef struct RClock { RUint8 __private__; } RClock;

RClock* rho_clock_reserve(RMemoryArena* arena);

RBool32 rho_clock_create(RClock* self);

void rho_clock_destroy(RClock* self);

void rho_clock_tick(RClock* self);

RUint rho_clock_elapsed(RClock* self);

RUint rho_clock_frequency(RClock* self);

RFloat32 rho_clock_seconds(RClock* self);

#endif
