#ifndef __IVECTOR_H__  // << change this
#define __IVECTOR_H__  // << change this

#define __VALUE_TYPE__ int  // << change this
#define __VEC_PREFIX__ i   // << change this


#include <stdlib.h>
#include <stdbool.h>

#define __CORRECT_CALL_MACRO(macro, ...)  macro(__VA_ARGS__)

#define __HELP_MAKE_VEC_FUNC_NAME(prefix, name) prefix ## vec_ ## name
#define __MAKE_VEC_FUNC_NAME(name) __CORRECT_CALL_MACRO(__HELP_MAKE_VEC_FUNC_NAME, __VEC_PREFIX__, name)

#define __HELP_MAKE_VEC_TYPEDEF(prefix) typedef struct prefix ## vector prefix ## vector_t
#define __MAKE_VEC_TYPEDEF() __CORRECT_CALL_MACRO(__HELP_MAKE_VEC_TYPEDEF, __VEC_PREFIX__)

#define __HELP_VEC_TYPENAME(prefix) prefix ## vector_t
#define __VEC_TYPENAME __CORRECT_CALL_MACRO(__HELP_VEC_TYPENAME, __VEC_PREFIX__)

__MAKE_VEC_TYPEDEF();


__VEC_TYPENAME *__MAKE_VEC_FUNC_NAME(create)(size_t initial_size);

void __MAKE_VEC_FUNC_NAME(free)(__VEC_TYPENAME *);

bool __MAKE_VEC_FUNC_NAME(add)(__VEC_TYPENAME *, __VALUE_TYPE__ value);

__VALUE_TYPE__ __MAKE_VEC_FUNC_NAME(get)(__VEC_TYPENAME *, size_t index);

bool __MAKE_VEC_FUNC_NAME(set)(__VEC_TYPENAME *, size_t index, __VALUE_TYPE__ value);

void __MAKE_VEC_FUNC_NAME(add_unsafe)(__VEC_TYPENAME *, __VALUE_TYPE__ value);

__VALUE_TYPE__ __MAKE_VEC_FUNC_NAME(get_unsafe)(__VEC_TYPENAME *, size_t index);

void __MAKE_VEC_FUNC_NAME(set_unsafe)(__VEC_TYPENAME *, size_t index, __VALUE_TYPE__ value);

size_t __MAKE_VEC_FUNC_NAME(size)(__VEC_TYPENAME *);

bool __MAKE_VEC_FUNC_NAME(remove_by_idx)(__VEC_TYPENAME *, size_t index);

void __MAKE_VEC_FUNC_NAME(remove_by_idx_unsafe)(__VEC_TYPENAME *, size_t index);

bool __MAKE_VEC_FUNC_NAME(remove)(__VEC_TYPENAME *, __VALUE_TYPE__ value);

int __MAKE_VEC_FUNC_NAME(remove_all)(__VEC_TYPENAME *, __VALUE_TYPE__ value);


#undef __VALUE_TYPE__
#undef __VEC_PREFIX__
#undef __HELP_MAKE_VEC_FUNC_NAME
#undef __MAKE_VEC_FUNC_NAME
#undef __HELP_MAKE_VEC_TYPEDEF
#undef __MAKE_VEC_TYPEDEF
#undef __HELP_VEC_TYPENAME
#undef __VEC_TYPENAME
#undef __CORRECT_CALL_MACRO

#endif  // include guard
