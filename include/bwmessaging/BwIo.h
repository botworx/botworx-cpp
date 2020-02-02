#ifndef _BwIo_H
#define _BwIo_H

class BwIo ;
class BwIoSlot ;

typedef std::map<bwPath, BwIo*> BwIoMap ;
typedef BwIoMap::iterator BwIoMapIter ;

class BwIo : public BwPart {
public:
	enum ioTypes {
		IO_TOPIC = 0,
		IO_ATTR,
		IO_VALUE
	} ;
	typedef ioTypes ioType ;
	BwIo(BwIo *pParent, const bwString& name, ioType = IO_TOPIC) ;
	//
	BwIo* getParent() { return p_parent ; }
	void invalidate() ;
	void signalChildNeedsUpdate() ;
	void update() ;
	virtual void onUpdate() {}
	virtual void notify(BwMessage evt) ;
	bwPath makePath() ;
	bwPath getPath() { return m_path ; }
	BwIo* findOrCreateIo(const bwPath& path) ;
	BwIo* findIo(const bwPath& path) ;
	//
	void setSlot(BwIoSlot *pSlot) { p_slot = pSlot ; }
	BwIoSlot* getSlot() { return p_slot ; }
	//Messages
	class Value {
	public:
		enum what_e {
			VAL_nullptr = 0,
			VAL_STRING,
			VAL_INT,
			VAL_FLOAT
		} ;
		typedef what_e bwWhat ;
		bwWhat m_what ;
		bwWhat what() { return m_what ; }
		Value(bwWhat what) : m_what(what) {
		}
		void setTimetag(unsigned long timetag) { m_timetag = timetag ; }
		unsigned long getTimetag() { return m_timetag ; }
		void setData(void *data) { p_data = data ; }
		void* getData() { return p_data ; }
		bwString toString() ;
		//
		bwString string_val ;
		union {
			//int64 int_val ;
			bwInt64 int_val ;
			bwFloat float_val ;
		} m_v ;
		unsigned long m_timetag ;
		void *p_data ;
	} ;
	class StringValue : public Value {
	public:
		StringValue(const bwString& val) : Value(VAL_STRING) {
			string_val = val ;
		}
	} ;
	class IntValue : public Value {
	public:
		IntValue(bwInt64 val) : Value(VAL_INT) {
			m_v.int_val = val ;
		}
	} ;
	class FloatValue : public Value {
	public:
		FloatValue(float val) : Value(VAL_FLOAT) {
			m_v.float_val = val ;
		}
	} ;
	//
	virtual Value getValue() {return Value(Value::VAL_nullptr) ; }
	virtual void setValue(Value val) {}
	virtual void print(int indent = 0) ;
	void printTree(int indent = 0) ;
	void printIos(int indent = 0) ;

	ioType getType() { return m_type ; }
	//Data Members
protected:
	BwIo* createAttrIo(const bwString& name) ;
	BwIo* createTopicIo(const bwString& name) ;
	BwIo* createValueIo(const bwString& name) ;
	BwIo* findSubIo(const bwString& name) ;
	BwIo* findOrCreateSubIo(const bwString& name, const bwPath& leafPath) ;
	//Data Members
	BwIoSlot *p_slot ;
	BwIo* p_parent ;
	bwPath m_path ;
	BwIoMap m_ios ;
	bool m_needsUpdate ;
	bool m_childNeedsUpdate ;
	//bool m_isLeaf ;
	ioType m_type ;
} ;

#endif //_BwIo_H