// IcValue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IcValue.h"
#include <cmath>

float square_root(float n)
{
	return sqrtf(n);
}

double square_root(double n)
{
	return sqrt(n);
}

template<typename T,typename Iter>
int calculate_help(T* out,T calibration_factor,Iter iter,size_t N,size_t time_points)
{
	if(N<2)
	{
		return 1;
	}
	T const denominator=N-1;
	for(size_t t=0;t<time_points;++t)
	{
		auto const data=iter[t];
		T sum{0};
		for(size_t i=1;i<N;++i) //all about same magnitude, precision not too worrying
		{
			auto const diff=data[i]-data[i-1];
			sum+=diff*diff;
		}
		out[t]=calibration_factor*square_root(sum)/denominator;
	}
	return 0;
}

template<typename T>
struct JumpIter {
	T* base;
	size_t jump;
	T* operator[](size_t N) const
	{
		return base+N*jump;
	}
};

extern "C" {

	ICVALUE_DLL_API int calculate_ic_values_incontiguous(double* out,double calibration_factor,double const* const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL
	{
		return calculate_help(out,calibration_factor,values,N,time_points);
	}

	ICVALUE_DLL_API int calculate_ic_values_continguous(double* out,double calibration_factor,double const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL
	{
		return calculate_help(out,calibration_factor,JumpIter<double const>{values,N},N,time_points);
	}

	ICVALUE_DLL_API int calculate_ic_values_partially_continguous(double* out,double calibration_factor,double const* values,size_t N,size_t jump,size_t time_points) ICVALUE_NOEXCEPT_DECL
	{
		return calculate_help(out,calibration_factor,JumpIter<double const>{values,jump},N,time_points);
	}

	ICVALUE_DLL_API int calculate_ic_values_incontiguous_f(float* out,float calibration_factor,float const* const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL
	{
		return calculate_help(out,calibration_factor,values,N,time_points);
	}

	ICVALUE_DLL_API int calculate_ic_values_continguous_f(float* out,float calibration_factor,float const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL
	{
		return calculate_help(out,calibration_factor,JumpIter<float const>{values,N},N,time_points);
	}

	ICVALUE_DLL_API int calculate_ic_values_partially_continguous_f(float*out,float calibration_factor,float const* values,size_t N,size_t jump,size_t time_points) ICVALUE_NOEXCEPT_DECL
	{
		return calculate_help(out,calibration_factor,JumpIter<float const>{values,jump},N,time_points);
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
