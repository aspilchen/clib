/** @file dynarrExperiment.h
 *  @brief Experimenting with macros to create a generic dynamic array.
 * 
 *  This is a big experiment to create easy to use generic dynamic arrays.
 *  Next step is to make this thread safe.
 * 
 *  @todo Make destructor.
 * 
 *  @version 1.0
 *  @date 2022/04/18
 *  @author Adam Spilchen
 */

#ifndef DYNARR_EXPERIMENTAL_H
#define DYNARR_EXPERIMENTAL_H

struct DynarrMeta {
	void **data;
	size_t size;
	size_t itemSize;
	size_t capacity;
};


void dynarr__init__(struct DynarrMeta *meta, void *data, size_t itemSize);
void dynar__expandIfFull__(struct DynarrMeta *meta); 
void dynarr__pushBack__(struct DynarrMeta *meta);

#define DATA(PTR)     (PTR)->data
#define META(PTR)     (PTR)->meta
#define MDATA(PTR)    META(PTR).data
#define SIZE(PTR)     META(PTR).size
#define TYPESIZE(PTR) sizeof(*DATA(PTR))
#define CAPACITY(PTR) META(PTR).capacity

#define Dynarr(TYPE) dynarr__ ## TYPE ## __
#define DynarrPTRS(TYPE) dynarr__ptrs ## TYPE ## __

/** @brief Declares a dynamic array type.
 *  @warning User must use include gaurds to prevent redifining types. Please use the format
 *  #ifndef DYNARR__<type>__ 
 *  #define DYNARR__<type>__ 
 *  dynarr_declare(<type>)
 *  #endif
 */
#define dynarr_declareValueArray(TYPE) struct Dynarr(TYPE) {struct DynarrMeta meta; TYPE *data;} typedef Dynarr(TYPE)

#define dynarr_declarePointerArray(TYPE) struct DynarrPTRS(TYPE) {struct DynarrMeta meta; TYPE **data;} typedef DynarrPTRS(TYPE)

#define dynarr_init(PTR) dynarr__init__(&META(PTR), &DATA(PTR), TYPESIZE(PTR))

#define dynarr_put(PTR, INDEX, VALUE) (DATA(PTR))[INDEX] = VALUE

#define dynarr_get(PTR, INDEX) DATA(PTR)[INDEX]

#define dynarr_pushBack(PTR, VALUE) dynarr__push__back__(PTR, VALUE)

#define dynarr__push__back__(PTR, VALUE) {dynar__expandIfFull__(&META(PTR)); dynarr_put(PTR, SIZE(PTR), VALUE); SIZE(PTR)++;}

#endif
