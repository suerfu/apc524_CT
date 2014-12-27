/*!
  \brief
  Implements numerical curve.
*/
#include "NumCurve.h"
#include <stdio.h>

// Default constructor, everything to NULL.
NumCurve::NumCurve() : Curve(0)
{
    _datax = 0;    
    _datay = 0;
    _size = 0;
}

// Constructor with a size input.
NumCurve::NumCurve(int size): Curve(0), _size(size)
{
    _datax = new double[_size];
    _datay = new double[_size];
}

// Constructor with a given array.
NumCurve::NumCurve(int size, double* x, double* y): Curve(0), _size(size)
{
        double avg = 0;		// symmetrize the given array. Center them at 0.
    for(int i=0;i<_size;i++){avg += x[i];}
    avg /= _size;
    _datax = new double[_size];
    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = x[i]-avg;	_datay[i] = y[i];
    }
    _r = fabs(_datax[0]) > fabs(_datax[_size-1]) ? fabs(_datax[0]) : fabs(_datax[_size-1]);
}

// Constructor with a size, a range and a set of y-values.
NumCurve::NumCurve(int size, double r, double* y): Curve(r), _size(size)
{
    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datay[i] = y[i];
        _datax[i] = -_r + i*(2*_r)/(_size-1);
    }
}

// Copy constructor that takes in the same type.
NumCurve::NumCurve(const NumCurve& f) : Curve(f._r)
{
    _size = f._size;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = f._datax[i];    
        _datay[i] = f._datay[i];	// Performs a deep copy.
    }
}

// Copy assignment, used when modifying existing objects, so have to take care of memories.
NumCurve& NumCurve::operator=(const NumCurve& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;	// free memory if previously contains objects.
    _size = f._size;
    _r = f._r;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = f._datax[i];    
        _datay[i] = f._datay[i];	// Performs a deep copy.
    }
    return (*this);
}

// Constructor with a size and a Curve object. Use operator () to initialize.
NumCurve::NumCurve(int size, const Curve& f) : Curve(0)
{
    _size = size;
    _r = f.GetRange();
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = -_r + i*(2*_r)/(_size-1);        
        _datay[i] = f(_datax[i],0);	// Evaluate at _datax{} and assign the value to the new obj.
    }
}

// Assignment operator for construction.
void NumCurve::Copy(int size, const Curve& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;	// free memory if previously contains objects.
    _size = size; _r = f.GetRange();
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = -_r + i*(2*_r)/(_size-1);        
        _datay[i] = f(_datax[i]);	// Evaluate at _datax{} and assign the value to the new obj.
    }
}

NumCurve::~NumCurve()
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
}

double NumCurve::operator()(double x, Interpolator* intpl) const
{
    // should implement the operator with an interpolation method. Have to check if the array is symmetric or not. A better approach is to first treat as symmetric, if returns wrong position, then performs a search algorithm to determine the position.
//    return intpl->Interpolate(x,_datax,_datay,_size);
    double d = 2*_r/(_size-1);
    int i0 = int((x+_r)/d)+1;
    int i1 = i0 +1;
    if (i1>=_size) return 0;
    else return _datay[i0]+(_datay[i1]-_datay[i0])*(x-_datax[i0])/d;
}

double& NumCurve::operator()(int index)
{
    if(index<0 || index>_size-1) printf("Index out of range!\n");
    return _datay[index];
}

void NumCurve::Print()
{
    for(int i=0; i<_size; i++) printf("%.9f\t%.9f\n",_datax[i],_datay[i]);
}
