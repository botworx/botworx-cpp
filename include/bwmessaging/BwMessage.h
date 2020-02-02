#ifndef _BwMessage_H
#define _BwMessage_H

#include <bwcore/config/boost_serialization.h>
#include <boost/any.hpp>

typedef boost::any BwMsgValue ;
class BwMessengerBase ;

#define BwMsgFieldName_SIZE 17

class BwMsgField {
	//Serialization
	friend class boost::serialization::access ;
	template<class Archive> void save(Archive & ar, const unsigned int version) const ;
    void save(boost::archive::text_oarchive & ar, const unsigned int version) const ;
    template<class Archive> void load(Archive & ar, const unsigned int version) ;
    void load(boost::archive::text_iarchive & ar, const unsigned int version) ;
    BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
	enum fieldType_E {
		FIELD_BAD = 0,
		FIELD_STRING,
		FIELD_INT32,
		FIELD_HANDLE,
		FIELD_BOOL,
		FIELD_INT64,
		FIELD_FLOAT
	} ;
	typedef fieldType_E fieldType ;
	void setFieldType(fieldType type) { m_fieldType = type ; }
	fieldType getFieldType() { return m_fieldType ; }
	BwMsgField() : p_next(nullptr), m_fieldType(FIELD_BAD) {}
	void setName(const bwString& name) {
		strncpy(m_name, name.c_str(), BwMsgFieldName_SIZE) ;
		//name.copy(m_name, BwMsgFieldName_SIZE) ;
	}
	void setVal(const BwMsgValue& value) {
		m_val = value ;
	}
	const bwString& getString() const {
		return *boost::any_cast<bwString>(&m_val) ;
	}
	bool isString() const {
		return m_fieldType == FIELD_STRING ;
	}
	const bwInt32 getInt32() const {
		return boost::any_cast<bwInt32>(m_val) ;
	}
	bool isInt32()	const {
		return m_fieldType == FIELD_INT32 ;
	}
	const bwHandle getHandle() const {
		return boost::any_cast<bwHandle>(m_val) ;
	}
	bool isHandle() const {
		return m_fieldType == FIELD_HANDLE ;
	}
	const bwBool getBool() const {
		return boost::any_cast<bwBool>(m_val) ;
	}
	bool isBool() const {
		return m_fieldType == FIELD_BOOL ;
	}
	const bwInt64 getInt64() const {
		return boost::any_cast<bwInt64>(m_val) ;
	}
	bool isInt64()	const {
		return m_fieldType == FIELD_INT64 ;
	}
	const bwFloat getFloat() const {
		return boost::any_cast<bwFloat>(m_val) ;
	}
	bool isFloat()	const {
		return m_fieldType == FIELD_FLOAT ;
	}
	//Data Members
	BwMsgField *p_next ;
	char m_name[BwMsgFieldName_SIZE] ;
	fieldType m_fieldType ;
	BwMsgValue m_val ;
} ;
//Serialization
//BOOST_CLASS_TRACKING(BwMsgField, boost::serialization::track_never)
///////////////////////////////
class BwMsgData ;
extern void purgeMsgData(BwMsgData *pData) ;
class BwMsgData {
	//Serialization
	friend class boost::serialization::access ;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int file_version) {
        ar & p_field & m_what & m_handle ;
    }
public:
	BwMsgData() : m_refCount(0), m_what(0), m_handle(0), p_field(nullptr) {}
	~BwMsgData() ;
	//Field Access
	BwMsgField* addField(const bwString& name) ;
	BwMsgField* findField(const bwString& name) ;
	bool exists(const bwString& name) { return findField(name) != nullptr ; }
	void addString(const bwString& name, const bwString& val) ;
	void findString(const bwString& name, bwString& result) ;
	void addInt32(const bwString& name, bwInt32 val) ;
	void findInt32(const bwString& name, bwInt32& result) ;
	void addHandle(const bwString& name, bwHandle val) ;
	void findHandle(const bwString& name, bwHandle& result) ;
	void addBool(const bwString& name, bwBool val) ;
	void findBool(const bwString& name, bwBool& result) ;
	void addInt64(const bwString& name, bwInt64 val) ;
	void findInt64(const bwString& name, bwInt64& result) ;
	void addFloat(const bwString& name, bwFloat val) ;
	void findFloat(const bwString& name, bwFloat& result) ;
	//Garbage Container
    friend void intrusive_ptr_add_ref(BwMsgData* p) ;
    friend void intrusive_ptr_release(BwMsgData* p) ;
    //
	void setSender(BwMessengerBase* pSender) { p_sender = pSender ; }
	BwMessengerBase* getSender() const { return p_sender ; }
	//Data Members
	int m_refCount ;
	BwMsgField *p_field ;
	bwWhat m_what ;
	bwHandle m_handle ;
    BwMessengerBase *p_sender ;
} ;
typedef boost::intrusive_ptr<BwMsgData> BwMsgDataPtr ;
inline void intrusive_ptr_add_ref(BwMsgData* p) {
    ++p->m_refCount;
}
inline void intrusive_ptr_release(BwMsgData* p) {
    if(--p->m_refCount == 0) purgeMsgData(p) ;
}
inline BwMsgData* addRef(BwMsgData* pCell) {
	if(pCell == nullptr)
		return pCell ;
    intrusive_ptr_add_ref(pCell) ;
	return pCell ;
}
inline void removeRef(BwMsgData *pCell) {
	if(pCell == nullptr)
		return ;
    intrusive_ptr_release(pCell) ;
}
//Serialization
BOOST_CLASS_TRACKING(BwMsgData, boost::serialization::track_never)
///////////////////////////////////////

class BwMessage {
public:
	BwMessage() ;
	BwMessage(const BwMessage& msg) : m_data(msg.getData()) {
	}
	BwMessage(BwMsgDataPtr& data) : m_data(data) {}
	BwMessage(bwWhat what, bwHandle handle = bwAnyHandle) ;

	BwMsgData& data() const { return *m_data.get() ; }
	BwMsgData* getData() const { return m_data.get() ; }
	const BwMsgDataPtr& operator()() const { return m_data ; }
	bwWhat what() const { return m_data->m_what ; }
	bwHandle handle() const { return m_data->m_handle ; }
	void setSender(BwMessengerBase* pSender) const { m_data->setSender(pSender) ; }
	BwMessengerBase* getSender() const { return m_data->getSender() ; }
	//
	//Data Members
	BwMsgDataPtr m_data ;
} ;

#endif //_BwMessage_H
