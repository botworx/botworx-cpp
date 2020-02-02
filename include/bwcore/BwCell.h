#ifndef _BwCell_H
#define _BwCell_H

template<typename T, typename F>
inline void setFlag(T& val, F flag) { val |= flag ; }

template<typename T, typename F>
inline bool getFlag(T& val, F flag) { return val & flag ; }

template<typename T, typename F>
inline void clearFlag(T& val, F flag) { val ^= flag ; }

//
// BwCell
//
class BwCell {
public:
	BwCell(ThingTT typeId = TT_PART) : m_refCount(0), m_typeId(typeId), m_isBlob(false) {}
	ThingTT getTypeId() const { return m_typeId ; }
	//Memory Management
	virtual void purge() ;
	friend void intrusive_ptr_add_ref(BwCell* p) ;
    friend void intrusive_ptr_release(BwCell* p) ;
    friend void intrusive_ptr_add_ref(const BwCell* p) ;
    friend void intrusive_ptr_release(const BwCell* p) ;
	//Data Members
	int m_refCount ;
	//boost::detail::atomic_count m_refCount ;
	ThingTT  m_typeId ;
	bool m_isBlob ;
} ;
typedef boost::intrusive_ptr<BwCell> BwCellPtr ;
typedef boost::intrusive_ptr<const BwCell> BwCellConstPtr ;

#define asThingTT(T) ((ThingTT)T)
#define isBlob(C) (C->m_isBlob)
//
//Garbage Container
//
inline void intrusive_ptr_add_ref(BwCell* p) {
    ++p->m_refCount;
}
inline void intrusive_ptr_add_ref(const BwCell* p) {
    ++const_cast<BwCell*>(p)->m_refCount;
}
//
inline void intrusive_ptr_release(BwCell* p) {
	if(--p->m_refCount == 0) p->purge() ;
}
inline void intrusive_ptr_release(const BwCell* p) {
	if(--const_cast<BwCell*>(p)->m_refCount == 0) const_cast<BwCell*>(p)->purge() ;
}
//
inline void addRef(BwCell* pCell) {
	if(pCell == nullptr) return  ;
    intrusive_ptr_add_ref(pCell) ;
}
inline void removeRef(BwCell* pCell) {
	if(pCell == nullptr) return ;
    intrusive_ptr_release(pCell) ;
}
//
#define asCell(C) (static_cast<BwCell*>(C))
#define asConstCell(C) (static_cast<const BwCell*>(C))
//
//#define setTT(C, T) (C->m_typeID = T)
#define getTT(C) (C->getTypeId())
#define isTT(X, T) (X == T)
#define isAboveTT(X, T) (X > T)
#define isOrAboveTT(X, T) (X >= T)
#define isBelowTT(X, T) (X < T)
#define isOrBelowTT(X, T) (X <= T)
#define ofTT(X,T) (isOrAboveTT(X, T) && isOrBelowTT(X, T##_UNKNOWN))
#define ifTT(X, T) isTT(X, T) ? T
#define ifOfTT(X, T) ofTT(X, T) ? T

#endif //_BwCell_H
