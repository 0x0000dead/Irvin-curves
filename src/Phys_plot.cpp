#include "Phys_plot.h"
namespace phfm
{
	double Phys_plot::Ed_convert(double Ed)
	{
		return Ed * PhysConst.eV;
	}

	double Phys_plot::equation(Material_base material, double mu, double Ndo, double T, double Eg, double Ed)
	{
		return Ndo / (1. + exp((Eg - Ed - mu) / PhysConst.k / T)) +
			Nv(material, T) * exp(-mu / PhysConst.k / T) -
			Nc(material, T) * exp((mu - Eg) / PhysConst.k / T);
	}

	double Phys_plot::derivative(Material_base material, double mu, double Ndo, double T, double Eg, double Ed)
	{
		return (Ndo * exp((Eg - Ed - mu) / (PhysConst.k * T)) / pow(1. +  exp((Eg - Ed - mu) / (PhysConst.k * T)), 2.) -
			Nv(material, T) * exp(-mu / PhysConst.k / T) -
			Nc(material, T) * exp((mu - Eg) / PhysConst.k / T)) / (PhysConst.k * T);
	}

	double Phys_plot::Nv(Material_base material, double T)
	{
		return 2.51e19 * pow(material.mh / PhysConst.me, 3. / 2.) * pow(T / 300, 3. / 2.);
	}

	double Phys_plot::Nc(Material_base material, double T)
	{
		return 2.51e19 * pow(material.me / PhysConst.me, 3. / 2.) * pow(T / 300, 3. / 2.);
	}

	double Phys_plot::p(Material_base material, double T, double mu)
	{
		return Nv(material, T) * exp(-mu / PhysConst.k / T);
	}

	double Phys_plot::n(Material_base material, double T, double mu, double Eg)
	{
		return Nc(material, T) * exp((mu - Eg) / PhysConst.k / T);
	}

	double Phys_plot::mu_e(Material_base material, double T, double Ndp, double Nam)
	{
		return material.electron.a / (pow(T, 3. / 2.) + material.electron.b * (Ndp + Nam) / pow(T, 3. / 2.));
	}

	double Phys_plot::mu_p(Material_base material, double T, double Ndp, double Nam)
	{
		return material.hole.a / (pow(T, 3. / 2.) + material.hole.b * (Ndp + Nam) / pow(T, 3. / 2.));
	}

	double Phys_plot::Ndp(Material_base material, double Ndo, double Eg, double Ed, double mu, double T)
	{
		return Ndo / (1. + exp((Eg - Ed - mu) / (PhysConst.k * T)));
	}
	bool sign_compare(double x, double y)
	{
		return  x / fabs(x) - y / fabs(y) < 10e-15;
	}
	double mean(std::vector<double> b)
	{
		return (b[1] + b[0]) / 2.;
	}

	double dichotomy(const std::function<double(double)>& func, double l_bound, double r_bound, double exp_error)
	{
		std::vector<double> bounds = { l_bound, r_bound };
		double middle_x = mean(bounds);
		double middle_val = func(middle_x);
		double lb_val = func(bounds[0]);
		double rb_val = func(bounds[1]);

		if (sign_compare(lb_val, rb_val))
		{
			throw new std::exception("Bad range for dichotomy method : f(a)* f(b) > 0");
		}
		while (fabs(bounds[1] - bounds[0]) >= exp_error)
		{
			if (fabs(middle_val) == 0)
				break;
			else if (!sign_compare(lb_val, middle_val))
			{
				bounds[1] = middle_x;
			}
			else
			{
				bounds[0] = middle_x;
				lb_val = func(bounds[0]);
			}
			middle_x = mean(bounds);
			middle_val = func(middle_x);
		}
		return middle_x;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_sigma_or_rho_ndo(Material_base material, double T, double Ndo_step, double Ed, bool isSigma)
	{
		right_boundary = material.Eg;
		double Ndo = 1e10;
		std::vector<std::pair<double, double>> result;
		double sigma = 0.;
		double Nam = 0.;
		double Ndp_val = 0.;
		double mu_e_val = 0.;
		double mu_p_val = 0.;
		double p_val = 0.;
		double n_val = 0.;
		std::function<double(double)> func = [](double sigma_) {return sigma_; };
		if (!isSigma)
			func = [](double sigma_) {return 1. / sigma_; };
		while (Ndo < 10e20)
		{
			try 
			{
				double temp =
					dichotomy([Ndo, T, material, Ed, this](double mu) 
						{ return equation(material, mu, Ndo, T, material.Eg, Ed); },
						left_boundary, right_boundary, 1e-15);
				Ndp_val = Ndp(material, Ndo, material.Eg, Ed, temp, T);
				mu_e_val = mu_e(material, T, Ndp_val, Nam);
				mu_p_val = mu_p(material, T, Ndp_val, Nam);
				p_val = p(material, T, temp);
				n_val = n(material, T, temp, material.Eg);
				sigma = PhysConst.e * (n_val * mu_e_val + p_val * mu_p_val);
				result.push_back({ Ndo, sigma });
				Ndo += Ndo_step;
			}
			catch(...)
			{
				break;
			}
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_mu_e_or_mu_p_T(Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step, bool isE)
	{
		right_boundary = material.Eg;
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		double Ndp_val = 0.;
		double Nam = 0.;
		double mu_val = 0.;
		std::function<double(Material_base, double, double, double)> func = [this](Material_base material_, double T_, double Ndp_, double Nam_)
		{
			return mu_p(material_, T_, Ndp_, Nam_);
		};
		if (isE)
			func = [this](Material_base material_, double T_, double Ndp_, double Nam_)
		{
			return mu_e(material_, T_, Ndp_, Nam_);
		};
		while (T < T_End)
		{
			try
			{
				double temp = dichotomy([Ndo, T, material, Ed, this](double mu) 
					{ return equation(material, mu, Ndo, T, material.Eg, Ed); },
						left_boundary, right_boundary, 1e-15);
				Ndp_val = Ndp(material, Ndo, material.Eg, Ed, temp, T);
				mu_val = func(material, T, Ndp_val, Nam);
				result.push_back({ T , mu_val });
				T += T_Step;
			}
			catch (...)
			{
				break;
			}
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_sigma_or_rho_T(Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed, bool isSigma)
	{
		right_boundary = material.Eg;
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		double sigma = 0.;
		double Nam = 0.;
		double Ndp_val = 0.;
		double mu_e_val = 0.;
		double mu_p_val = 0.;
		double p_val = 0.;
		double n_val = 0.;
		std::function<double(double)> func = [](double sigma_) {return sigma_; };
		if (!isSigma)
			func = [](double sigma_) {return 1. / sigma_; };
		while (T < T_End)
		{
			try
			{
				double temp = dichotomy([Ndo, T, material, Ed, this](double mu) 
					{return equation(material, mu, Ndo, T, material.Eg, Ed); },
						left_boundary, right_boundary, 1e-15);
				Ndp_val = Ndp(material, Ndo, material.Eg, Ed, temp, T);
				mu_e_val = mu_e(material, T, Ndp_val, Nam);
				mu_p_val = mu_p(material, T, Ndp_val, Nam);
				p_val = p(material, T, temp);
				n_val = n(material, T, temp, material.Eg);
				sigma = PhysConst.e * (n_val * mu_e_val + p_val * mu_p_val);
				result.push_back({ T, func(sigma) });
				T += T_Step;
			}
			catch(...)
			{
				break;
			}
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_p_or_t_T(Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed, bool isP)
	{
		right_boundary = material.Eg;
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		std::function<double(double, double, Material_base)> func = [this](double T_, double mu_, Material_base material_) {return n(material_, T_, mu_, material_.Eg); };
		if (isP)
			func = [this](double T_, double mu_, Material_base material_) {return p(material_, T_, mu_); };
		while (T < T_End)
		{
			try
			{
				double temp =
					dichotomy([Ndo, T, material, Ed, this](double mu) {return equation(material, mu, Ndo, T, material.Eg, Ed); },
						left_boundary, right_boundary, 1e-15);
				result.push_back({ T, func(T, temp, material) });
				T += T_Step;
			}
			catch (...)
			{
				break;
			}
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::sigma_ndo(
		Material_base material, double T, double Ndo_step, double Ed)
	{
		Ed = Ed_convert(Ed);
		return find_sigma_or_rho_ndo(material, T, Ndo_step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::rho_ndo(
		Material_base material, double T, double Ndo_step, double Ed)
	{
		Ed = Ed_convert(Ed);
		return find_sigma_or_rho_ndo(material, T, Ndo_step, Ed, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::mu_e_T(
		Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step)
	{
		Ed = Ed_convert(Ed);
		return find_mu_e_or_mu_p_T(material, Ndo, Ed, T_Begin, T_End, T_Step, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::mu_p_T(
		Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step)
	{
		Ed = Ed_convert(Ed);
		return find_mu_e_or_mu_p_T(material, Ndo, Ed, T_Begin, T_End, T_Step, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::sigma_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		Ed = Ed_convert(Ed);
		return find_sigma_or_rho_T(material, Ndo, T_Begin, T_End, T_Step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::rho_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		Ed = Ed_convert(Ed);
		return find_sigma_or_rho_T(material, Ndo, T_Begin, T_End, T_Step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::p_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		Ed = Ed_convert(Ed);
		return find_p_or_t_T(material, Ndo, T_Begin, T_End, T_Step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::n_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		Ed = Ed_convert(Ed);
		return find_p_or_t_T(material, Ndo, T_Begin, T_End, T_Step, Ed, false);
	}
}