#ifndef _BwAlignedAlloc_H
#define _BwAlignedAlloc_H

#include <stddef.h>

namespace bwstd {

template <class T>
class aligned_alloc
{
public:
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;
	typedef T*        pointer;
	typedef const T*  const_pointer;
	typedef T&       reference;
	typedef const T& const_reference;
	typedef T         value_type;

	aligned_alloc() { init() ; }
	aligned_alloc(const aligned_alloc&) { init() ; bwAssert(0) ; } //TODO:what's it do??? :)
	void init() {
	}
	pointer allocate(size_type n, const void * = 0) {
		return _aligned_malloc(count, BW_ALIGNMENT) ;
	}
	void deallocate(void* object, size_type n) {
		if (ptr == 0 || n == 0)
			return;
		//else
		_aligned_free(object) ;
	}

	pointer address(reference x) const { return &x; }

	const_pointer address(const_reference x) const { return &x; }

	aligned_alloc<T>& operator=(const aligned_alloc&) { return *this; }

	void construct(pointer p, const T& val) {
		new ((T*) p) T(val); }

	void destroy(pointer p) { p->~T(); }

	size_type max_size() const { return size_t(-1); }

	template <class U>
	struct rebind { typedef aligned_alloc<U> other; };

	template <class U>
	aligned_alloc(const aligned_alloc<U>&) {}

	template <class U>
	aligned_alloc& operator=(const aligned_alloc<U>&) { return *this; }
};

} //namespace bwstd

#endif //_BwAlignedAlloc_H
