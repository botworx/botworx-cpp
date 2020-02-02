#ifndef _AiBuffer_H
#define _AiBuffer_H

//
//AiBuffer
//
#define BWBUFFER_SIZE 4096
class AiBuffer : public BwCell {
public:
	AiBuffer() : BwCell(TT_BUFFER), m_size(BWBUFFER_SIZE) {}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	char* getBuffer() { return m_buffer ; }
	void setSize(size_t size) { m_size = size ; }
	size_t getSize() { return m_size ; }
	//Data Members
	size_t m_size ;
	char m_buffer[BWBUFFER_SIZE] ;
};
typedef boost::intrusive_ptr<AiBuffer> AiBufferPtr ;
//
//AiBufferKit
//
template<>
struct BwSigT<AiBufferKit> : BwSigT<BwKit> {
	typedef AiBuffer	T_Part ;
} ;
typedef BwPoolKitT<AiBufferKit, BwKit> AiBufferKitBase ;
//f6:idea:implement MultiPools, pools of pools ... size 128, 256 ...
//whoah wouldn't be to hard ... pool vector ...
class AiBufferKit : public AiBufferKitBase {
public:
	AiBufferKit(BwKit *pKit) : AiBufferKitBase(pKit) {}
	/*Data Members*/
public:
};
//
//AiPair
//
inline void* AiBuffer::operator new(size_t count) throw() {
#if AI_OPTION_POOLING
	return k_buffer().rent(count) ;
#else
	return BW_USERMALLOC(count, TT_BUFFER) ;
#endif
}

#endif //_AiBuffer_H
