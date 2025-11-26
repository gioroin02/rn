#ifndef RN_BASE_MEMORY_SLICE_C
#define RN_BASE_MEMORY_SLICE_C

#include "./slice.h"

RnMemorySlice
rn_memory_slice_make(void* memory, ssize start, ssize stop, ssize step)
{
	RnMemorySlice result = {0};

	if (memory == 0 || stop <= start || step <= 0)
		return result;

    if (stop - start > RN_MAX_SSIZE / step) return result;

	result.values = rn_cast(u8*, memory) + start * step;
	result.size   = stop - start;
	result.step   = step;

	return result;
}

ssize
rn_memory_slice_size(RnMemorySlice self)
{
    return self.size;
}

ssize
rn_memory_slice_step(RnMemorySlice self)
{
    return self.step;
}

ssize
rn_memory_slice_bytes(RnMemorySlice self)
{
    return self.size * self.step;
}

void*
rn_memory_slice_zero(RnMemorySlice self)
{
    for (ssize i = 0; i < self.size * self.step; i += 1)
        self.values[i] = 0;

    return self.values;
}

void*
rn_memory_slice_flip(RnMemorySlice self)
{
    for (ssize i = 0, j = self.size - 1; i < j; i += 1, j -= 1)
        rn_memory_slice_swap(self, i, j);

    return self.values;
}

void*
rn_memory_slice_swap(RnMemorySlice self, ssize index, ssize other)
{
    if (index < 0 || index >= self.size) return 0;
    if (other < 0 || other >= self.size) return 0;

    if (index == other) return 0;

    for (ssize i = 0; i < self.step; i += 1) {
        ssize i = index * self.step + i;
        ssize o = other * self.step + i;

        self.values[i] ^= self.values[o];
        self.values[o] ^= self.values[i];
        self.values[i] ^= self.values[o];
    }

    return self.values;
}

#endif // RN_BASE_MEMORY_SLICE_C
