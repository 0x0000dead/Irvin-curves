#include "Entity.h"
#include <cmath>



bool Entity::check_result(double current, double previous)
{
	return abs(current - previous) < precision;
}

double Entity::solve(std::vector<double>& values)
{
	if (!is_valid()) {
		return WRONG_SOLUTION;
	}
	double prev = get_initial_value();
	values.push_back(prev); \
		for (size_t i = 0; i < number_of_iteration; ++i)
		{
			auto curr = get_next_value(prev);
			values.push_back(curr);
			if (curr < left_boundary)
			{
				curr = left_boundary;
			}
			if (curr > right_boundary)
			{
				curr = right_boundary;
			}
			if (abs(curr) > 1e-20 && !std::isnormal(curr)) {
				break;
			}
			if (check_result(curr, prev)) {
				return curr;
			}
			prev = curr;
		}
	return WRONG_SOLUTION;
}