#pragma once
#include "Entity.h"

class Dichotomy_method final :public Entity
{
	double split_ratio = 2;

	double middle_of_interval(const double left_boundary_, const double right_boundary_);

	bool is_valid()override;
	double get_initial_value() override;
	double get_next_value(double current) override;
public:
	explicit Dichotomy_method(const double left_boundary_, const double right_boundary_,
		const double precision_, const std::function<double(double)>& function_,
		const std::function<double(double)>& derivative_, bool need_to_border_cuttoff_ = false)
		: Entity(left_boundary_, right_boundary_, precision_, function_, derivative_, need_to_border_cuttoff_)
	{}
};