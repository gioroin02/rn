#ifndef RN_BASE_DEFINES_H
#define RN_BASE_DEFINES_H

#define rn_cast(type, expr) ((type) expr)

#define rn_array_count(expr)  sizeof(expr) / sizeof(*(expr))
#define rn_array_stride(expr) sizeof(*(expr))

#define rn_min(a, b) ((a) < (b) ? (a) : (b))
#define rn_max(a, b) ((a) < (b) ? (b) : (a))

#define rn_clamp_top(x, max) rn_min(x, max)
#define rn_clamp_bot(x, min) rn_max(x, min)

#define rn_clamp(x, min, max) rn_max(min, rn_min(x, max))

#define __rn_text__(expr) # expr
#define __rn_glue__(a, b) a ## b

#define rn_text(expr) __rn_text__(expr)
#define rn_glue(a, b) __rn_glue__(a, b)

#endif // RN_BASE_DEFINES_H
