#ifndef _BwcImage_H
#define _BwcImage_H

class BwcImage : public BwPart {
public:
	BwcImage(BwPart* pOwner) : BwPart(pOwner) {
		m_type = IMAGE_BAD ;
	}
	void setPath(const bwPath& path) ;
	bwPath getPath() { return m_path ; }
	//
	enum imageType {
		IMAGE_BAD = 0,
		IMAGE_GOOD //it's a start ...
	} ;
	void setType(imageType type) { m_type = type ; }
	imageType getType() { return m_type ; }
	bool isBad() { return m_type == IMAGE_BAD ; }
	bool isGood() { return !isBad() ; }
	//Data Members
	imageType m_type ;
	bwPath m_path ;
} ;
typedef std::map<bwString, BwcImage*> BwcImageMap ;
typedef BwcImageMap::iterator BwcImageMapIter ;

class BwcImageLib : public BwPart {
public:
	BwcImageLib(BwPart* pOwner) : BwPart(pOwner) {}
	BwcImage* createImage() ;
	void addImage(BwcImage* pImage) ;
	BwcImage* findImage(const bwString& name) ;
	//Data Members
	BwcImageMap m_imageMap ;
} ;

#endif //_BwcImage_H