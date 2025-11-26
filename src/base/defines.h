#ifndef RN_BASE_DEFINES_H
#define RN_BASE_DEFINES_H

#define rnManySize(expr) sizeof(expr) / sizeof(*(expr))
#define rnManyStep(expr) sizeof(*(expr))

#define rnMin(a, b) ((a) < (b) ? (a) : (b))
#define rnMax(a, b) ((a) < (b) ? (b) : (a))

#define rnClampTop(x, max) rnMin(x, max)
#define rnClampBot(x, min) rnMax(x, min)

#define rnClamp(x, min, max) rnMax(min, rnMin(x, max))

#define __rnText__(expr) # expr
#define __rnGlue__(a, b) a ## b

#define rnText(expr) __rnText__(expr)
#define rnGlue(a, b) __rnGlue__(a, b)

#endif // RN_BASE_DEFINES_H
