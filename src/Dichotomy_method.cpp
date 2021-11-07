#include "Dichotomy_method.h"
#include <cmath>

bool Dichotomy_method::is_valid()
{
	if (left_boundary > right_boundary || precision > 1 || precision < 0 ||
		left_boundary == right_boundary || function == nullptr) {
		return false;
	}
	double f_l = function(left_boundary);
	double f_r = function(right_boundary);
	if (std::isnan(f_l) || std::isnan(f_r)) {
		return  false;
	}

	return true;
}

double Dichotomy_method::get_next_value(double current)
{
	double x = function(current);
	x = x * right_boundary;
	if (x > 0)
	{
		right_boundary = current;
		return middle_of_interval(left_boundary, right_boundary);
	}
	if (x < 0)
	{
		left_boundary = current;
		return middle_of_interval(left_boundary, right_boundary);
	}
	return current;
}
double Dichotomy_method::middle_of_interval(const double left_boundary_, const double right_boundary_)
{
	return  right_boundary_ - (right_boundary_ - left_boundary_) / split_ratio;
}

double Dichotomy_method::get_initial_value()
{
	return middle_of_interval(left_boundary, right_boundary);
}
