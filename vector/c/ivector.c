#include "ivector.h"  // << change this

#define __VALUE_TYPE__ int  // << change this
#define __VEC_PREFIX__ i   // << change this
#define __NULL_VALUE__ ((__VALUE_TYPE__){ 0 })  // change this if need

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define __CORRECT_CALL_MACRO(macro, ...)  macro(__VA_ARGS__)

#define __HELP_MAKE_VEC_FUNC_NAME(prefix, name) prefix ## vec_ ## name
#define __MAKE_VEC_FUNC_NAME(name) __CORRECT_CALL_MACRO(__HELP_MAKE_VEC_FUNC_NAME, __VEC_PREFIX__, name)

#define __HELP_MAKE_VEC_TYPEDEF(prefix) typedef struct prefix ## vector prefix ## vector_t
#define __MAKE_VEC_TYPEDEF() __CORRECT_CALL_MACRO(__HELP_MAKE_VEC_TYPEDEF, __VEC_PREFIX__)

#define __HELP_VEC_TYPENAME(prefix) prefix ## vector_t
#define __VEC_TYPENAME __CORRECT_CALL_MACRO(__HELP_VEC_TYPENAME, __VEC_PREFIX__)

#define __HELP_VSTRUCTNAME(prefix) prefix ## vector
#define __VEC_STRUCTNAME __CORRECT_CALL_MACRO(__HELP_VSTRUCTNAME, __VEC_PREFIX__)

#define VSIZEOF(elems) (sizeof(__VALUE_TYPE__) * (elems))

struct __VEC_STRUCTNAME
{
    __VALUE_TYPE__ *data;
    size_t size;
    size_t capacity;
};

#define EXTEND_FACTOR 2
#define SHRINK_ON_CAP 0.5
#define SHRINK_FACTOR 0.7
#define DEFAULT_INITIAL_SIZE 10

bool extend(__VEC_TYPENAME *vec)
{
    size_t new_cap = vec->capacity * EXTEND_FACTOR;
    __VALUE_TYPE__ *new_data = realloc(vec->data, VSIZEOF(new_cap));
    bool success = new_data != NULL;
    if (success)
    {
        vec->data = new_data;
        vec->capacity = new_cap;
    }
    return success;
}

bool shrink(__VEC_TYPENAME *vec)
{
    size_t new_cap = (size_t)((double)vec->capacity * SHRINK_FACTOR);
    __VALUE_TYPE__ *new_data = realloc(vec->data, VSIZEOF(new_cap));
    bool success = new_data != NULL;
    if (success)
    {
        vec->data = new_data;
        vec->capacity = new_cap;
    }
    return success;
}

void remove_elem(__VEC_TYPENAME *vec, size_t index)
{
    if (index < vec->size - 1)
        for (size_t i = index; i < vec->size - 1; i++)
            vec->data[i] = vec->data[i + 1];
    vec->size--;
}

__VEC_TYPENAME *__MAKE_VEC_FUNC_NAME(create)(size_t initial_size)
{
    if (initial_size == 0)
        initial_size = DEFAULT_INITIAL_SIZE;
    
    __VEC_TYPENAME *vec = malloc(sizeof(__VEC_TYPENAME));

    if (vec)
    {
        vec->data = malloc(VSIZEOF(initial_size));
        if (vec->data)
        {
            vec->size = 0;
            vec->capacity = initial_size;
        }
        else
        {
            free(vec);
            vec = NULL;
        }
    }
    
    return vec;
}

void __MAKE_VEC_FUNC_NAME(free)(__VEC_TYPENAME *vec)
{
    free(vec->data);
    free(vec);
}

bool __MAKE_VEC_FUNC_NAME(add)(__VEC_TYPENAME *vec, __VALUE_TYPE__ value)
{
    bool success = true;
    if (vec->size >= vec->capacity)
        success = extend(vec);
    
    if (success)
    {
        vec->data[vec->size] = value;
        vec->size++;
    }

    return success; 
}

__VALUE_TYPE__ __MAKE_VEC_FUNC_NAME(get)(__VEC_TYPENAME *vec, size_t index)
{
    __VALUE_TYPE__ ret = __NULL_VALUE__;

    if (index < vec->size)
        ret = vec->data[index];

    return ret;
}

bool __MAKE_VEC_FUNC_NAME(set)(__VEC_TYPENAME *vec, size_t index, __VALUE_TYPE__ value)
{
    bool success = index < vec->size;
    if (success)
    {
        vec->data[index] = value;
    }
    return success;
}

void __MAKE_VEC_FUNC_NAME(add_unsafe)(__VEC_TYPENAME *vec, __VALUE_TYPE__ value)
{
    if (vec->size >= vec->capacity)
        extend(vec);
    vec->data[vec->size] = value;
    vec->size++;
}

__VALUE_TYPE__ __MAKE_VEC_FUNC_NAME(get_unsafe)(__VEC_TYPENAME *vec, size_t index)
{
    return vec->data[index];
}

void __MAKE_VEC_FUNC_NAME(set_unsafe)(__VEC_TYPENAME *vec, size_t index, __VALUE_TYPE__ value)
{
    vec->data[index] = value;
}

bool __MAKE_VEC_FUNC_NAME(remove_by_idx)(__VEC_TYPENAME *vec, size_t index)
{
    bool success = index < vec->size;
    if (success)
    {
        remove_elem(vec, index);
        if (vec->size < (size_t)(vec->capacity * SHRINK_ON_CAP))
            shrink(vec);
    }
    return success;
}

 void __MAKE_VEC_FUNC_NAME(remove_by_idx_unsafe)(__VEC_TYPENAME *vec, size_t index)
{
    remove_elem(vec, index);
    if (vec->size < (size_t)(vec->capacity * SHRINK_ON_CAP))
        shrink(vec);
}

size_t __MAKE_VEC_FUNC_NAME(size)(__VEC_TYPENAME *vec)
{
    return vec->size;
}

bool __MAKE_VEC_FUNC_NAME(remove)(__VEC_TYPENAME *, __VALUE_TYPE__ value);

int __MAKE_VEC_FUNC_NAME(remove_all)(__VEC_TYPENAME *, __VALUE_TYPE__ value);
