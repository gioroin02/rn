#ifndef RHO_BASE_DEFINE_H
#define RHO_BASE_DEFINE_H

#define rho_min(v0, v1) ((v0) < (v1) ? (v0) : (v1))
#define rho_max(v0, v1) ((v0) < (v1) ? (v1) : (v0))

#define rho_clamp_top(val, max) rho_min(val, max)
#define rho_clamp_bot(val, min) rho_max(val, min)

#define rho_clamp(val, min, max) rho_max(min, rho_min(val, max))

#endif
