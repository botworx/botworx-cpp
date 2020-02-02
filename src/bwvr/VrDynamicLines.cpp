#include "stdafx.h"
#include <bwvr/VrDynamicLines.h>
#include <bwvr/config/ogre.h>

using namespace Ogre;

enum {
  POSITION_BINDING,
  TEXCOORD_BINDING
};

VrDynamicLines::VrDynamicLines(OperationType opType)
{
  initialize(opType,false);
  setMaterial("BaseWhiteNoLighting");
  mDirty = true;
}

VrDynamicLines::~VrDynamicLines()
{
}

void VrDynamicLines::setOperationType(OperationType opType)
{
  mRenderOp.operationType = opType;
}

RenderOperation::OperationType VrDynamicLines::getOperationType() const
{
  return mRenderOp.operationType;
}

void VrDynamicLines::addPoint(const Vector3 &p)
{
   mPoints.push_back(p);
   mDirty = true;
}
void VrDynamicLines::addPoint(Real x, Real y, Real z)
{
   mPoints.push_back(Vector3(x,y,z));
   mDirty = true;
}
const Vector3& VrDynamicLines::getPoint(unsigned short index) const
{
   assert(index < mPoints.size() && "Point index is out of bounds!!");
   return mPoints[index];
}
unsigned short VrDynamicLines::getNumPoints(void) const
{
  return (unsigned short)mPoints.size();
}
void VrDynamicLines::setPoint(unsigned short index, const Vector3 &value)
{
  assert(index < mPoints.size() && "Point index is out of bounds!!");

  mPoints[index] = value;
  mDirty = true;
}
void VrDynamicLines::clear()
{
  mPoints.clear();
  mDirty = true;
}

void VrDynamicLines::update()
{
  if (mDirty) fillHardwareBuffers();
}

void VrDynamicLines::createVertexDeclaration()
{
  VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
  decl->addElement(POSITION_BINDING, 0, VET_FLOAT3, VES_POSITION);
}

void VrDynamicLines::fillHardwareBuffers()
{
  int size = mPoints.size();

  prepareHardwareBuffers(size,0);

  if (!size) {
    mBox.setExtents(Vector3::ZERO,Vector3::ZERO);
    mDirty=false;
    return;
  }

  Vector3 vaabMin = mPoints[0];
  Vector3 vaabMax = mPoints[0];

  HardwareVertexBufferSharedPtr vbuf =
    mRenderOp.vertexData->vertexBufferBinding->getBuffer(0);

  Real *prPos = static_cast<Real*>(vbuf->lock(HardwareBuffer::HBL_DISCARD));
  {
   for(int i = 0; i < size; ++i)
   {
      *prPos++ = mPoints[i].x;
      *prPos++ = mPoints[i].y;
      *prPos++ = mPoints[i].z;

      if(mPoints[i].x < vaabMin.x)
         vaabMin.x = mPoints[i].x;
      if(mPoints[i].y < vaabMin.y)
         vaabMin.y = mPoints[i].y;
      if(mPoints[i].z < vaabMin.z)
         vaabMin.z = mPoints[i].z;

      if(mPoints[i].x > vaabMax.x)
         vaabMax.x = mPoints[i].x;
      if(mPoints[i].y > vaabMax.y)
         vaabMax.y = mPoints[i].y;
      if(mPoints[i].z > vaabMax.z)
         vaabMax.z = mPoints[i].z;
   }
  }
  vbuf->unlock();

  mBox.setExtents(vaabMin, vaabMax);

  mDirty = false;
}

/*
void VrDynamicLines::getWorldTransforms(Matrix4 *xform) const
{
   // return identity matrix to prevent parent transforms
   *xform = Matrix4::IDENTITY;
}
*/
/*
const Quaternion &VrDynamicLines::getWorldOrientation(void) const
{
   return Quaternion::IDENTITY;
}

const Vector3 &VrDynamicLines::getWorldPosition(void) const
{
   return Vector3::ZERO;
}
*/
