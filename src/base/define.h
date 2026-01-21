#ifndef P_BASE_DEFINE_H
#define P_BASE_DEFINE_H

#define pMin(v0, v1) ((v0) < (v1) ? (v0) : (v1))
#define pMax(v0, v1) ((v0) < (v1) ? (v1) : (v0))

#define pClampTop(val, max) pMin(val, max)
#define pClampBot(val, min) pMax(val, min)

#define pClamp(val, min, max) pMax(min, pMin(val, max))

#define pOffsetOf(self, mem) ((char*) &((self)->mem) - (char*) (self))

#endif // P_BASE_DEFINE_H
