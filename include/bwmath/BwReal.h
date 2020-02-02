#ifndef _BwReal_H
#define _BwReal_H

namespace bwmath {

template<typename T>
struct RealTraits {
} ;

template<>
struct RealTraits<float> {
	static const float
		MinusOne, 
		Zero,
		Quarter,
		Half,
		One,
		Two,
		Three,
		Four,
		MinValue,
		MaxValue,
		Epsilon,
		NegInfinity,
		PosInfinity,
		Pi,
		NegPi,
		Pi2,
		PiDiv2,
		NegPiDiv2,
		PiDiv4,
		PiDiv6,
		PiDiv8,
		PiDiv45,
		PiDiv90,
		PiDiv180
		;
} ;

template<>
struct RealTraits<double> {
	static const double
		MinusOne, 
		Zero,
		Quarter,
		Half,
		One,
		Two,
		Three,
		Four,
		MinValue,
		MaxValue,
		Epsilon,
		NegInfinity,
		PosInfinity,
		Pi,
		NegPi,
		Pi2,
		PiDiv2,
		NegPiDiv2,
		PiDiv4,
		PiDiv6,
		PiDiv8,
		PiDiv45,
		PiDiv90,
		PiDiv180
		;
} ;

} //namespace bwmath

//Userland Aliases

typedef bwmath::Real bwReal ;
typedef bwmath::RealTraits<bwReal> bwRealTraits ;

inline bwReal max2(bwReal a, bwReal b) { return (a > b ? a : b) ; }
inline bwReal max3(bwReal a, bwReal b, bwReal c) { return (max2(a, max2(b, c))); }
inline bwReal max4(bwReal a, bwReal b, bwReal c, bwReal d) { return (max2(a, max3(b, c, d))); }
inline bwReal min2(bwReal a, bwReal b) { return (a < b ? a : b) ; }
inline bwReal min3(bwReal a, bwReal b, bwReal c) { return (min2(a, min2(b, c))); }
inline bwReal min4(bwReal a, bwReal b, bwReal c, bwReal d) { return (min2(a, min3(b, c, d))); }

namespace bwmath {

template<typename T_NUM>
inline bwReal rcp(const T_NUM& num) {
	if (bwReal(num) > bwReal(0.0))
		return bwReal(1.0) / bwReal(num) ;
	else
		return bwReal(1.0e-30) ;
}

} //namespace bwmath {

/*// reciprocal square root
template<typename T_NUM>
inline bwReal bwRsqrt(const T_NUM& num) {
	return bwReal(1/sqrt(num)) ;
}*/
//! Fast square root for floating-point values.
//inline_ float FastSqrt(float square)
inline float bwSqrt(float square)
{
#ifdef _MSC_VER
		float retval;

		__asm {
				mov             eax, square
				sub             eax, 0x3F800000
				sar             eax, 1
				add             eax, 0x3F800000
				mov             [retval], eax
		}
		return retval;
#else
		return sqrt(square);
#endif
}
//! Computes 1.0f / sqrtf(x). Comes from NVIDIA.
#define IEEE_1_0				0x3f800000					//!< integer representation of 1.0
typedef unsigned int		udword;		//!< sizeof(udword)	must be 4
inline  float bwRsqrt(const float& x)
{
	udword tmp = (udword(IEEE_1_0 << 1) + IEEE_1_0 - *(udword*)&x) >> 1;   
	float y = *(float*)&tmp;                                             
	return y * (1.47f - 0.47f * x * y * y);
}

#define bwSin(x) sin(x)
#define bwCos(x) cos(x)
#define bwFabs(x) fabs(x)
#define bwAtan2(y,x) atan2((y),(x))

#endif //_BwReal_H