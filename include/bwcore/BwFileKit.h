#ifndef _BwFileKit_H
#define _BwFileKit_H


//typedef std::stack<bwPath> bwDirStack ;
typedef std::stack<bwString> bwDirStack ;
typedef bwDirStack::container_type::iterator bwDirStackIter ;

class BwFileKit : public BwKit {
public:
	BwFileKit(BwKit *pKit) : BwKit(pKit) { pushDir("") ; }
	void setDir(const bwString& path) { dir_stack.top() = path ; }
	const bwString& getDir() { return dir_stack.top() ; }
	void pushDir(const bwString& path) { dir_stack.push(path) ; }
	void popDir() { dir_stack.pop() ; }
	void changeDir() { chdir(dir_stack.top().c_str()) ; }
	//void changeDir() { SetCurrentDirectory(dir_stack.top().c_str()) ; }
	bwDirStack& getStack() { return dir_stack ; }
private:
	/*Data Members*/
public:
private:
	bwDirStack dir_stack ;
};

#endif //_BwFileKit_H