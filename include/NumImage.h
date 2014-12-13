/*!
  \brief This file defines numerical images whose data points are defined by discrete points.
*/
#ifndef NUMIMAGE
#define NUMIMAGE 1

#include"Curve.h"
#include"Volume.h"
#include"Interpolator.h"

/*!
  This class implements the Curve abstract class with numerical points. The values are obtained by interpolation.
*/

class NumCurve : public Curve{

public:
	NumCurve();		//!< Default constructor, everything null and 0.
	NumCurve(int size);	//!< Default constructor, _size set and everything else null and 0.
	NumCurve(int size, double* x, double* y);	//!< Initialize with a given x and y array.
	NumCurve(int size, double r, double* y);	//!< Initialize with a radius and an array.
	NumCurve(const NumCurve&);		//!< Copy constructor, same type as NumCurve.
	NumCurve& operator=(const NumCurve&);	//!< Assignment constructor for same type.
	NumCurve(int size, const Curve&);	//!< Copy constr. for general Curve obj. Needs size info.
	void Copy(int size, const Curve&);	//!< Copy operator for general Curve, will use previous size information.

	~NumCurve();		//!< Destructor, has to delete stored data.

	double operator()(double, Interpolator*) const;
				//!< Operator () to access lvalues, argument double will be rounded to nearest intger and be used to access.
	double& operator()(int);	//!< This method can be used to set values at the integer nodes.

	void Print();	//!< Default method, print out everything as two columns.
	void Print(double,double,int);	//!< Print for a given range.

protected:
	double* _datax;	//!< Y-Coordinates of the points.
	double* _datay;	//!< Y-Coordinates of the points.
	int _size;	//!< size of the array.
};

#include "Surface.h"

//class NumSurface : public Surface{

//};

//class NumVolume : public Volume{

//};

#endif