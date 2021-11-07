#include "Newton_method.h"
#include <cmath>

bool Newton_method::is_valid()
{
	if (left_boundary > right_boundary || precision > 1 || precision < 0 ||
		left_boundary == right_boundary || function == nullptr || derivative == nullptr) {
		return false;
	}
	double f_l = function(left_boundary);
	double f_r = function(right_boundary);
	if (std::isnan(f_l) || std::isnan(f_r)) {
		return  false;
	}
	return true;
}

double Newton_method::get_next_value(double current)
{
	double x = current;
	double g = derivative(x);
	if (abs(g) < 1e-20) {
		x = middle_of_interval(left_boundary, right_boundary);
		return x;
	}
	return (x - function(x) / g);
}
double Newton_method::middle_of_interval(const double left_boundary_, const double right_boundary_)
{
	split_ratio += 2;
	return  right_boundary_ - (right_boundary_ - left_boundary_) / split_ratio;
}

double Newton_method::get_initial_value()
{
	return middle_of_interval(left_boundary, right_boundary);
}

