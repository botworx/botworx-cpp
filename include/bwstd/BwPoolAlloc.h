/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwPoolAlloc_H
#define _BwPoolAlloc_H

namespace bwstd {

template <class T>
class pool_alloc
{
public:
	typedef boost::pool<> pool ;
	//
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;
	typedef T*        pointer;
	typedef const T*  const_pointer;
	typedef T&       reference;
	typedef const T& const_reference;
	typedef T         value_type;

	pool_alloc() : m_pool(sizeof(value_type)) {}
	pool_alloc(const pool_alloc&) : m_pool(sizeof(value_type)) {}

	pointer allocate(size_type n, const void * = 0) {
		/*T* t = (T*) malloc(n * sizeof(T));
		std::cout
		<< "  used pool_alloc to allocate   at address "
		<< t << " (+)" << std::endl;*/
		T* t = (T*)m_pool.ordered_malloc(n) ;
		return t;
	}
	  
	void deallocate(void* pCell, size_type n) {
		if (pCell) {
			/*free(p);
			std::cout
			<< "  used pool_alloc to deallocate at address "
			<< p << " (-)" << 
			std::endl;*/
			//m_pool.free(pCell) ;
			m_pool.ordered_free(pCell, n) ;
		} 
	}

	pointer address(reference x) const { return &x; }

	const_pointer address(const_reference x) const { return &x; }

	pool_alloc<T>& operator=(const pool_alloc&) { return *this; }

	void construct(pointer p, const T& val) {
		new ((T*) p) T(val); }

	void destroy(pointer p) { p->~T(); }

	size_type max_size() const { return size_t(-1); }

	template <class U>
	struct rebind { typedef pool_alloc<U> other; };

	template <class U>
	//pool_alloc(const pool_alloc<U>&) {}
	pool_alloc(const pool_alloc<U>&) : m_pool(sizeof(value_type)) {}

	template <class U>
	pool_alloc& operator=(const pool_alloc<U>&) { return *this; }
	/*Data Members*/
	pool m_pool ;
};

} //namespace bwstd

#endif //_BwPoolAlloc_H
