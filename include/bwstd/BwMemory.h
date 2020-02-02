#ifndef _BwMemory_H
#define _BwMemory_H

#include <malloc.h>
#include <new>

#define BW_OPTION_ALIGNMENT 0
//#define BW_OPTION_ALIGNMENT 1
//#define BW_ALIGNMENT 0
#define BW_ALIGNMENT 16
//

//TODO:were locked into using this now ...
#define BW_OPTION_NEWDELETE 0
//#define BW_OPTION_NEWDELETE 1

#if BW_DEBUG && _MSC_VER
#define BW_USE_VC_CRTDBG 1
#endif

#ifdef BW_USE_VC_CRTDBG
    #include <crtdbg.h>
    // Need to undef new if including crtdbg.h which may redefine new itself
    #ifdef new
        #undef new
    #endif

    #include <stdlib.h>
    #ifndef _CRTBLD
        // Need when built with pure MS SDK
        #define _CRTBLD
    #endif

    #include <crtdbg.h>

    // this define works around a bug with inline declarations of new, see
    //
    //      http://support.microsoft.com/support/kb/articles/Q140/8/58.asp
    //
    // for the details
    //#define new  new( _NORMAL_BLOCK, __FILE__, __LINE__)

//
//BW_MALLOC
//
#if BW_OPTION_ALIGNMENT
#define BW_MALLOC(size) \
	(_aligned_malloc(size, BW_ALIGNMENT))
#define BW_USERMALLOC(size,type) \
	(_aligned_malloc(size, BW_ALIGNMENT))
#else
#define BW_MALLOC(size) \
	(_malloc_dbg(size, _NORMAL_BLOCK, __FILE__, __LINE__))
#define BW_USERMALLOC(size,type) \
	(_malloc_dbg(size, _CLIENT_BLOCK | (type << 16), __FILE__, __LINE__))
#endif
//
//BW_REALLOC
//
#if BW_OPTION_ALIGNMENT
#define BW_REALLOC(object, re_newsize) \
	(_aligned_realloc(object, re_newsize, BW_ALIGNMENT))
#define BW_USERREALLOC(object, re_newsize, type) \
	(_aligned_realloc(object, re_newsize, BW_ALIGNMENT))
#else
#define BW_REALLOC(object, re_newsize) \
	(_realloc_dbg(object, re_newsize, _NORMAL_BLOCK, __FILE__, __LINE__) )
#define BW_USERREALLOC(object, re_newsize, type) \
	(_realloc_dbg(object, re_newsize, _CLIENT_BLOCK | (type << 16), __FILE__, __LINE__) )
#endif
//
//BW_FREE
//
#if BW_OPTION_ALIGNMENT
#define BW_FREE(object) \
	(_aligned_free(object)) ;
#define BW_USERFREE(object, type) \
	(_aligned_free(object)) ;
#else
#define BW_FREE(object) \
	(_free_dbg(object, _NORMAL_BLOCK))
#define BW_USERFREE(object, type) \
	_free_dbg(object, _CLIENT_BLOCK | (type << 16)) ;
#endif

#else // BW_USE_VC_CRTDBG

#define BW_MALLOC(size) \
	(::malloc(size))
#define BW_USERMALLOC(size,type) \
	(::malloc(size))

#define BW_REALLOC(object, re_newsize) \
	(::realloc(object, re_newsize))
#define BW_USERREALLOC(object, re_newsize, type) \
	(::realloc(object, re_newsize))

#define BW_FREE(object) \
	(::free(object))
#define BW_USERFREE(object, type) \
	(::free(object))

#endif // BW_USE_VC_CRTDBG

//----------------------------------------------------
//Override Global new & delete
//
#if BW_OPTION_NEWDELETE
void* operator new(size_t sz) throw();
void* operator new[](size_t sz) throw();
void operator delete(void* m) throw();
void operator delete[](void* m) throw();
//Scalar New
inline void* operator new(size_t count) {
	return BW_MALLOC(count) ;
}
inline void operator delete(void* object) {
	if (object == nullptr)
		return ;
	//else
	BW_FREE(object) ;
}
//Vector New
inline void* operator new[](size_t count) {
	return BW_MALLOC(count) ;
}
inline void operator delete[](void* object) {
	if (object == nullptr)
		return ;
	//else
	BW_FREE(object);
}

/*TODO:do we need to implement this?
void operator delete(
   void* _Ptr,
   const std::nothrow_t&
) throw( );
*/
#endif //BW_OPTION_NEWDELETE

#define BW_OPTION_ALIGNED_NEWDELETE 0

#if BW_OPTION_ALIGNED_NEWDELETE

#define BW_ALIGNED_NEWDELETE \
\
inline void* operator new(size_t sz) throw()	\
{												\
	void* mem = _aligned_malloc(sz, BW_ALIGNMENT);	\
	return mem;									\
}												\
												\
inline void* operator new[](size_t sz) throw()	\
{												\
	void* mem = _aligned_malloc(sz, BW_ALIGNMENT);	\
	return mem;									\
}												\
												\
inline void operator delete(void* m) throw()	\
{												\
	if (m == 0)									\
		return;									\
	_aligned_free(m);							\
}												\
												\
inline void operator delete[](void* m) throw()	\
{												\
	_aligned_free(m);							\
}												\
												\
inline void* operator new(size_t count, void * object) throw() { \
	return object ; \
} \
inline void operator delete(void *object, void *memory) throw() { \
	\
} \

struct aligned_user_allocator_new_delete
{
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  static char * malloc(const size_type bytes) {
	char* mem = (char*)_aligned_malloc(bytes, BW_ALIGNMENT);
	return mem ;
  //{ return new (std::nothrow) char[bytes]; }
  }
  static void free(char * const block) {
		_aligned_free(block);
  //{ delete [] block; }
  }
};

#else //BW_OPTION_ALIGNED_NEWDELETE

#define BW_ALIGNED_NEWDELETE

#endif //BW_OPTION_ALIGNED_NEWDELETE

//----------------------------------------------------
#if BW_DEBUG && _MSC_VER

extern void __cdecl BwDbg_dumper(void *ptr, size_t block_size) ;

#define BW_RPT(string) _RPT0(_CRT_WARN, string)
//
class BwDbgDumper {
public:
	BwDbgDumper::BwDbgDumper(char *pName) {
		p_name = pName ;
	}
	void dump(void* pBlock, size_t blockSize) {
		int block = _CrtReportBlockType(pBlock);
		int blockType = _BLOCK_TYPE(block) ;
		int blockSubType = _BLOCK_SUBTYPE(block) ;

		_RPT4(_CRT_WARN, "###%s### : type %d, subtype %d, size %d\n",
			p_name, blockType, blockSubType, blockSize);

		on_dump(pBlock, blockSize) ;
	}
	virtual void on_dump(void* pBlock, size_t blockSize) {}
	//Data Members
	char *p_name ;
};
//
#define BW_DBG_DUMPER(x) \
class BwDbgDumper_##x : public BwDbgDumper { \
public: \
	BwDbgDumper_##x(char *pName) : BwDbgDumper(pName) {} \
	virtual void on_dump(void* pBlock, size_t blockSize) ; \
}; \
	BwDbgDumper_##x BwDbgDumper_##x##_var( #x ) ; \
void BwDbgDumper_##x::on_dump(void* pBlock, size_t blockSize)

#define BW_DBG_DUMP(x) (BwDbgDumper_##x##_var.dump(ptr, blockSize))

#endif //#if BW_DEBUG && _MSC_VER

#endif //_BwMemory_H
