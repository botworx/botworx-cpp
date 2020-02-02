/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaSystem.h>
#include <bwmia/MiaAgent.h>

DECLARE_KITINFO(MyAgent) ;

class MyAgent : public MiaAgent {
public:
	MyAgent(AiKit* pSuperKit, AiKitInfo *pKitInfo) : MiaAgent(NULL, KITINFOREF(MiaAgent)) {}

	static AiKit* produce() {
		return new MyAgent(NULL, KITINFOREF(MiaAgent)) ;
	}
	static MiaAgent* produceAgent() { return static_cast<MiaAgent*>(produce()) ; }
	virtual void createPrinter() {
		p_printer = new MiaPrinter(std::cout) ;
	}
	virtual void createLogger() {
		MiaCore::createLogger() ;
		/*std::string fileName = "../log/log.txt" ;
		std::ofstream* pOut = new std::ofstream(fileName.c_str(), std::ios_base::out | std::ios_base::trunc );
		p_logger = new MiaPrinter(*pOut) ;*/
	}
private:
	MyAgent() : MiaAgent() { bwAssert(0) ; }
};
class MySystem : public MiaSystem {
public:
	MySystem() : MiaSystem() {}
	//
	virtual MiaAgent* produceAgent() { return MyAgent::produceAgent() ; }
};

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	MySystem system ;
	system.open() ;
	{
		//TODO:really need a better way
		std::string path("../media/BwMia/demos/") ;
		std::string fileName = "Mac.mia" ;
		//std::string fileName = "Blox.mia" ;
		//std::string fileName = "Towers.mia" ;
		//std::string fileName = "WaterJug.mia" ;
		//
		MiaAgent* pAgent = system.createAgent("AGENT", path + fileName) ;

		try {
			pAgent->run() ;
		}
		catch(...) {
			bwAssert(0) ;
		}

		std::cout.flush() ;

		char input[10] ;
		std::cin.getline(input, 10) ;
	}
	system.close() ;
	return 0;
}
