#ifndef _MiaSystem_H
#define _MiaSystem_H

class MiaCore ;

class MiaSystem {
public:
	MiaSystem() ;
	//Singleton support
	static MiaSystem *s_singleton ;
	static MiaSystem& singleton() ;
	//
	MiaAgent* createAgent(const std::string& name, const std::string& fileName) ;
	virtual MiaAgent* produceAgent() ;
	void open() ;
	void close() ;
protected:
	/*Data Members*/
	MiaAgent *p_agent ;
};

#endif //_MiaSystem_H
