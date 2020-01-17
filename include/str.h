
#ifndef PROJECT_INCLUDES_STR_H
#define PROJECT_INCLUDES_STR_H

#include "password.h"

char*
__attribute__((alloc_size(1), malloc, returns_nonnull, warn_unused_result))
allocateBuffer(size_t length);

char*
__attribute__((returns_nonnull, warn_unused_result))
generateRandomString(size_t length);

char**
__attribute__((returns_nonnull, warn_unused_result))
generateRandomStrings(size_t length, size_t number);

#endif /* PROJECT_INCLUDES_STR_H */
