#include "Phys_plot.h"
namespace phfm
{
	double Phys_plot::equation(double mu, double Ndo, double T, double Eg, double Ed)
	{
		return Ndo / (1 + exp((Eg - Ed - mu) / PhysConst.k / T)) +
			Nv(T) * exp(-mu / PhysConst.k / T) -
			Nc(T) * exp((mu - Eg) / PhysConst.k / T);
	}

	double Phys_plot::derivative(double mu, double Ndo, double T, double Eg, double Ed)
	{
		return (Ndo * exp((Eg - Ed - mu) / (PhysConst.k * T)) / pow(1 + exp((Eg - Ed - mu) / (PhysConst.k * T)), 2) -
			Nv(T) * exp(-mu / PhysConst.k / T) -
			Nc(T) * exp((mu - Eg) / PhysConst.k / T)) / (PhysConst.k * T);
	}

	double Phys_plot::Nv(double T)
	{
		return 2.51e19 * pow(PhysConst.mc / PhysConst.m_zero, 3 / 2) * pow(T / 300, 3 / 2);
	}

	double Phys_plot::Nc(double T)
	{
		return 2.51e19 * pow(PhysConst.mc / PhysConst.m_zero, 3 / 2) * pow(T / 300, 3 / 2);
	}

	double Phys_plot::p(double T, double mu)
	{
		return Nv(T) * exp(-mu / PhysConst.k / T);
	}

	double Phys_plot::n(double T, double mu)
	{
		return Nc(T) * exp(-mu / PhysConst.k / T);
	}

	double Phys_plot::mu_e(Material_base material, double T, double Ndp, double Nam)
	{
		return material.electron.a / (pow(T, 3 / 2) + material.electron.b * (Ndp + Nam) / pow(T, 3 / 2));
	}

	double Phys_plot::mu_p(Material_base material, double T, double Ndp, double Nam)
	{
		return material.hole.a / (pow(T, 3 / 2) + material.hole.b * (Ndp + Nam) / pow(T, 3 / 2));
	}

	double Phys_plot::Ndp(double Ndo, double Eg, double Ed, double mu, double T)
	{
		return Ndo / (1 + exp(Eg - Ed - mu / (PhysConst.k * T)));
	}

	std::vector<std::pair<double, double>> Phys_plot::find_sigma_or_rho_ndo(Material_base material, double T, double Ndo_step, double Ed, bool isSigma)
	{
		double Ndo = 10e10;
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
			std::vector<double> rubbish;
			double temp = Dichotomy_method(left_boundary, right_boundary, 1e-20,
				[Ndo, T, material, Ed, this](double mu) {return equation(mu, Ndo, T, material.Eg, Ed); },
				[Ndo, T, material, Ed, this](double mu) {return derivative(mu, Ndo, T, material.Eg, Ed); },
				false).solve(rubbish);
			Ndp_val = Ndp(Ndo, material.Eg, Ed, temp, T);
			mu_e_val = mu_e(spec_material_cont().Si, T, Ndp_val, Nam);
			mu_p_val = mu_p(spec_material_cont().Si, T, Ndp_val, Nam);
			p_val = p(T, temp);
			n_val = n(T, temp);
			sigma = PhysConst.e * (n_val * mu_e_val + p_val * mu_p_val);
			result.push_back({ Ndo, func(sigma) });
			Ndo += Ndo_step;
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_mu_e_or_mu_p_T(Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step, bool isE)
	{
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
			std::vector<double> rubbish;
			double temp = Dichotomy_method(left_boundary, right_boundary, 1e-20,
				[Ndo, T, material, Ed, this](double mu) {return equation(mu, Ndo, T, material.Eg, Ed); },
				[Ndo, T, material, Ed, this](double mu) {return derivative(mu, Ndo, T, material.Eg, Ed); },
				false).solve(rubbish);
			Ndp_val = Ndp(Ndo, material.Eg, Ed, temp, T);
			mu_val = func(material, T, Ndp_val, Nam);
			result.push_back({ T , mu_val });
			T += T_Step;
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_sigma_or_rho_T(Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed, bool isSigma)
	{
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
			func = [](double sigma_) {return 1 / sigma_; };
		while (T < T_End)
		{
			std::vector<double> rubbish;
			double temp = Dichotomy_method(left_boundary, right_boundary, 1e-20,
				[Ndo, T, material, Ed, this](double mu) {return equation(mu, Ndo, T, material.Eg, Ed); },
				[Ndo, T, material, Ed, this](double mu) {return derivative(mu, Ndo, T, material.Eg, Ed); },
				false).solve(rubbish);
			Ndp_val = Ndp(Ndo, material.Eg, Ed, temp, T);
			mu_e_val = mu_e(material, T, Ndp_val, Nam);
			mu_p_val = mu_p(material, T, Ndp_val, Nam);
			p_val = p(T, temp);
			n_val = n(T, temp);
			sigma = PhysConst.e * (n_val * mu_e_val + p_val * mu_p_val);
			result.push_back({ T, func(sigma) });
			T += T_Step;
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_p_or_t_T(Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed, bool isP)
	{
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		std::function<double(double, double)> func = [this](double T_, double mu_) {return n(T_, mu_); };
		if (isP)
			func = [this](double T_, double mu_) {return p(T_, mu_); };
		while (T < T_End)
		{
			std::vector<double> rubbish;
			double temp = Dichotomy_method(left_boundary, right_boundary, 1e-20,
				[Ndo, T, material, Ed, this](double mu) {return equation(mu, Ndo, T, material.Eg, Ed); },
				[Ndo, T, material, Ed, this](double mu) {return derivative(mu, Ndo, T, material.Eg, Ed); },
				false).solve(rubbish);
			result.push_back({ T, func(T, temp) });
			T += T_Step;
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::sigma_ndo(
		Material_base material, double T, double Ndo_step, double Ed)
	{
		return find_sigma_or_rho_ndo(material, T, Ndo_step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::rho_ndo(
		Material_base material, double T, double Ndo_step, double Ed)
	{
		return find_sigma_or_rho_ndo(material, T, Ndo_step, Ed, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::mu_e_T(
		Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step)
	{
		return find_mu_e_or_mu_p_T(material, Ndo, Ed, T_Begin, T_End, T_Step, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::mu_p_T(
		Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step)
	{
		return find_mu_e_or_mu_p_T(material, Ndo, Ed, T_Begin, T_End, T_Step, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::sigma_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		return find_sigma_or_rho_T(material, Ndo, T_Begin, T_End, T_Step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::rho_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		return find_sigma_or_rho_T(material, Ndo, T_Begin, T_End, T_Step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::p_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		return find_p_or_t_T(material, Ndo, T_Begin, T_End, T_Step, Ed, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::n_T(
		Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed)
	{
		return find_p_or_t_T(material, Ndo, T_Begin, T_End, T_Step, Ed, false);
	}
}