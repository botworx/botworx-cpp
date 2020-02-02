#ifndef _BwAligned_H
#define _BwAligned_H

#ifdef WIN32

#include <malloc.h>

template<typename T>
struct BwAligned {
	inline void* operator new(size_t sz) throw() {											
		void* mem = _aligned_malloc(sz, __alignof(T));	
		return mem;									
	}
	inline void* operator new[](size_t sz) throw() {												
		void* mem = _aligned_malloc(sz, __alignof(T));
		return mem;									
	}																									
	inline void operator delete(void* m) throw() {												
		if (m == 0)									
			return;									
		_aligned_free(m);							
	}
	inline void operator delete[](void* m) throw() {												
		_aligned_free(m) ;
	}												
} ;

#endif //WIN32	

#endif //_BwAligned_H
