#pragma once
#ifndef ICVALUE_H
#define ICVALUE_H
#include <stddef.h>
#ifdef _WIN32
#ifdef ICVALUE_BUILDING
#define ICVALUE_DLL_API __declspec(dllexport)
#else
#define ICVALUE_DLL_API __declspec(dllimport)
#endif
#else
#define ICVALUE_DLL_API
#endif

#ifdef __cplusplus
#if __cplusplus>201100L || _MSVC_LANG>201100L
#define ICVALUE_NOEXCEPT_DECL noexcept
#else
#define ICVALUE_NOEXCEPT_DECL
#endif
extern "C" {
#endif
/*
	out - ptr to buffer to receive data, should be at least time_points long
	calibration_factor - cf
	values - ptr to ptrs where each secondary buffer holds the data for one time point
	N - number of samples per time point
	time_points
	returns 0 on success, 1 on invalid input
*/
ICVALUE_DLL_API int calculate_ic_values_incontiguous(double* out,double calibration_factor,double const* const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL;
ICVALUE_DLL_API int calculate_ic_values_incontiguous_f(float* out,float calibration_factor,float const* const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL;

/*
	out - ptr to buffer to receive data, should be at least time_points long
	calibration_factor - cf
	values - samples arranged in matrix where each row contains N samples and rows are contiguously arranged
	N - number of samples per time point
	time_points
	returns 0 on success, 1 on invalid input
*/
ICVALUE_DLL_API int calculate_ic_values_continguous(double* out,double calibration_factor,double const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL;
ICVALUE_DLL_API int calculate_ic_values_continguous_f(float* out,float calibration_factor,float const* values,size_t N,size_t time_points) ICVALUE_NOEXCEPT_DECL;

/*
	out - ptr to buffer to receive data, should be at least time_points long
	calibration_factor - cf
	values - samples arranged such that each row contains N samples and the next row is jump values away from the previous
	N - number of samples per time point
	time_points
	returns 0 on success, 1 on invalid input
	calculate_ic_values_continguous(out,calibration_factor,values,N,N,time_points) is equivalent to this function
*/
ICVALUE_DLL_API int calculate_ic_values_partially_continguous(double* out,double calibration_factor,double const* values,size_t N,size_t jump,size_t time_points) ICVALUE_NOEXCEPT_DECL;
ICVALUE_DLL_API int calculate_ic_values_partially_continguous_f(float* out,float calibration_factor,float const* values,size_t N,size_t jump,size_t time_points) ICVALUE_NOEXCEPT_DECL;
#ifdef __cplusplus
}
#endif
#endif