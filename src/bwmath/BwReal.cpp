#include "stdafx.h"
#include <limits>
#include <bwmath/BwReal.h>

namespace bwmath {

//float traits
const float RealTraits<float>::MinusOne(-1.0f);
const float RealTraits<float>::Zero(0.0f);
const float RealTraits<float>::Quarter(0.25f);
const float RealTraits<float>::Half(0.5f);
const float RealTraits<float>::One(1.0f);
const float RealTraits<float>::Two(2.0f);
const float RealTraits<float>::Three(3.0f);
const float RealTraits<float>::Four(3.0f);

const float RealTraits<float>::MinValue(-3.402823466e+38f);
const float RealTraits<float>::MaxValue(3.402823466e+38f);
const float RealTraits<float>::Epsilon(1.192092896e-07f);

const float RealTraits<float>::PosInfinity(3.402823466e+38f);
const float RealTraits<float>::NegInfinity(-3.402823466e+38f);

const float RealTraits<float>::Pi(3.14159265358979323846f);
const float RealTraits<float>::NegPi(-3.14159265358979323846f);
const float RealTraits<float>::Pi2(6.28318530717958647692f);
const float RealTraits<float>::PiDiv2(1.57079632679489661923f);
const float RealTraits<float>::NegPiDiv2(-1.57079632679489661923f);
const float RealTraits<float>::PiDiv4(0.785398163397448309615f);
const float RealTraits<float>::PiDiv6(0.523598775598298873076f);
const float RealTraits<float>::PiDiv8(0.3926990816987241548075f);
const float RealTraits<float>::PiDiv45(0.0698131700797731830768f);
const float RealTraits<float>::PiDiv90(0.0349065850398865915384f);
const float RealTraits<float>::PiDiv180(0.01745329251994329576f);

//double traits
const double RealTraits<double>::MinusOne(-1.0);
const double RealTraits<double>::Zero(0.0);
const double RealTraits<double>::Quarter(0.25);
const double RealTraits<double>::Half(0.5);
const double RealTraits<double>::One(1.0);
const double RealTraits<double>::Two(2.0);
const double RealTraits<double>::Three(3.0);
const double RealTraits<double>::Four(3.0);

const double RealTraits<double>::MinValue(std::numeric_limits<double>::min());
const double RealTraits<double>::MaxValue(std::numeric_limits<double>::max());
const double RealTraits<double>::Epsilon(std::numeric_limits<double>::epsilon());

const double RealTraits<double>::PosInfinity(std::numeric_limits<double>::infinity());
const double RealTraits<double>::NegInfinity(-std::numeric_limits<double>::infinity());

const double RealTraits<double>::Pi(M_PI);
const double RealTraits<double>::NegPi(-M_PI);
const double RealTraits<double>::Pi2(6.28318530717958647692);
const double RealTraits<double>::PiDiv2(1.57079632679489661923);
const double RealTraits<double>::NegPiDiv2(-1.57079632679489661923);
const double RealTraits<double>::PiDiv4(0.785398163397448309615);
const double RealTraits<double>::PiDiv6(0.523598775598298873076);
const double RealTraits<double>::PiDiv8(0.3926990816987241548075);
const double RealTraits<double>::PiDiv45(0.0698131700797731830768);
const double RealTraits<double>::PiDiv90(0.0349065850398865915384);
const double RealTraits<double>::PiDiv180(0.01745329251994329576);

} //namespace bwmath
