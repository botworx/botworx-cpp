#ifndef _MiaDirectory_H
#define _MiaDirectory_H

class MiaMind ;

class MiaEntry ;

typedef std::map<bwPath, MiaEntry*> MiaEntryMap ;
typedef MiaEntryMap::iterator MiaEntryMapIter ;

class MiaEntry {
public:
	MiaEntry(MiaEntry *pParent, const bwString& name, MiaMind* pMind) ;
	//
	MiaEntry* getParent() { return p_parent ; }
	bwPath makePath() ;
	bwPath getPath() { return m_path ; }
	MiaEntry* findOrCreateDescendant(const bwPath& path) ;
	MiaEntry* findDescendant(const bwPath& path) ;
	//
	virtual void print(int indent = 0) ;
	void printTree(int indent = 0) ;
	void printChildren(int indent = 0) ;
	//Data Members
protected:
	MiaEntry* findChild(const bwString& name) ;
	MiaEntry* findOrCreateChild(const bwString& name, const bwPath& leafPath) ;
	//Data Members
	MiaEntry* p_parent ;
	bwString m_name ;
	bwPath m_path ;
	MiaEntryMap m_children ;
	MiaMind* p_mind ;
} ;

#endif //_MiaDirectory_H