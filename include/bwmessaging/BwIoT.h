#ifndef _BwIoT_H
#define _BwIoT_H

#include <bwmessaging/BwIoSlot.h>

template<typename T>
class BwTopicIoT : public T {
public:
	BwTopicIoT<T>(T *pParent, const bwString& name, typename T::ioType type = IO_TOPIC) : T(pParent, name, type) {}
} ;

template<typename T>
class BwAttrIoT : public T {
public:
	BwAttrIoT<T>(T *pParent, const bwString& name, typename T::ioType type = IO_ATTR) 
		: T(pParent, name, type) {}
	void setValue(typename T::Value val) { addValue(val) ; }
	virtual typename T::Value getValue() { return (*m_ios.begin()).second->getValue() ; }
	void addValue(typename T::Value val) { 
		BwIo *pVal = createValueIo(val.toString()) ;
		pVal->setValue(val) ;
	}
} ;

template<typename T>
class BwValueIoT : public T {
public:
	BwValueIoT<T>(T *pParent, const bwString& name, typename T::ioType type = IO_VALUE) 
		: T(pParent, name, type), m_value(typename T::Value(typename T::Value::VAL_nullptr)) {}
	void setValue(typename T::Value val) { m_value = val ; invalidate() ; }
	virtual typename T::Value getValue() { return m_value ; }
	//Data Members
	typename T::Value m_value ;
} ;

#endif //_BwIoT_H
