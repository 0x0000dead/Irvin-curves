#include "Phys_plot.h"
namespace phfm
{
	double Phys_plot::Nv(Material_base material, double T)
	{
		return 2.51e19 * pow(material.mh * T / PhysConst.me / 300., 1.5);
	}

	double Phys_plot::Nc(Material_base material, double T)
	{
		return 2.51e19 * pow(material.me * T / PhysConst.me / 300., 1.5);
	}
	
	double get_n(double Nc, double Eg, double Ef, double T)
	{
		return Nc * exp((Ef - Eg) / (PhysConst.k * T));
	}

	double get_p(double Nv, double Ef, double T)
	{
		return Nv * exp((-Ef) / (PhysConst.k * T));
	}
	double get_NaMinus(double Na0, double Ea, double Ef, double T)
	{
		return Na0 / (1. + exp((Ea - Ef) / (PhysConst.k * T)));
	}

	double get_NdPlus(double Eg, double Nd0, double Ed, double Ef, double T)
	{
		return Nd0 / (1. + exp((Eg - Ef - Ed) / (PhysConst.k * T)));
	}

	double func(double Ef, double Nc, double Nv, double T, double Na0, double Nd0, double Eg,
		double Ea, double Ed)
	{
		const double n = get_n(Nc, Eg, Ef, T);
		const double p = get_p(Nv, Ef, T);
		const double NdPlus = get_NdPlus(Eg, Nd0, Ed, Ef, T);
		const double NaMinus = get_NaMinus(Na0, Ea, Ef, T);
		return NdPlus + p - n - NaMinus;
	}

	double get_fermi(double Nc, double Nv, double T, double Na0, double Nd0, double Eg, double Ea,
		double Ed)
	{
		double left = 0;
		double right = 10.0;
		double middle = (left + right) * 0.5;
		double fm = func(middle, Nc, Nv, T, Na0, Nd0, Eg, Ea, Ed);
		double iterations = 0;
		while (fabs(fm) > 1 && iterations < 1000)
		{
			double fleft = func(left, Nc, Nv, T, Na0, Nd0, Eg, Ea, Ed);
			double fright = func(right, Nc, Nv, T, Na0, Nd0, Eg, Ea, Ed);
			if (fleft * fm < 0)
			{
				right = middle;
			}
			else if (fright * fm < 0)
			{
				left = middle;
			}
			else
			{
				break;
			}
			middle = (left + right) * 0.5;
			fm = func(middle, Nc, Nv, T, Na0, Nd0, Eg, Ea, Ed);
			++iterations;
		}
		return middle;
	}

	double get_mobility(double a, double b, double NdPlus, double NaMinus, double T)
	{
		double temp = pow(T, 1.5);
		return a / (temp + b * (NdPlus + NaMinus) / temp);
	}

	std::vector<std::pair<double, double>> Phys_plot::find_sigma_or_rho_ndo(Material_base material, double T, double Ed, double begin, double end, double Ndo_step, double Nam, bool isSigma)
	{
		double Ndo = begin;
		std::vector<std::pair<double, double>> result;
		double Nv_vals = Nv(material, T);
		double Nc_vals = Nc(material, T);
		double sigma = 0.;
		double Ndp_val = 0.;
		double mu_e_val = 0.;
		double mu_p_val = 0.;
		double p_val = 0.;
		double n_val = 0.;
		std::function<double(double)> func = [](double sigma_) {return sigma_; };
		if (!isSigma)
			func = [](double sigma_) {return 1. / sigma_; };
		while (Ndo < end)
		{
			try
			{
				double temp = get_fermi(Nc_vals, Nv_vals, T, Ndo, 1e16,
					material.Eg, 0.1, Ed);
				mu_e_val = get_mobility(material.electron.a, material.electron.b,
					Ndo, Nam, T);
				mu_p_val = get_mobility(material.hole.a, material.hole.b,
					Ndo, Nam, T);
				p_val = get_p(Nv_vals, temp, T);
				n_val = get_n(Nc_vals, material.Eg, temp, T);
				sigma = 100 * PhysConst.e * (n_val * mu_e_val + p_val * mu_p_val);
				result.push_back({ Ndo, func(sigma) });
				Ndo += Ndo_step;
			}
			catch (...)
			{
				break;
			}
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_mu_e_or_mu_p_T(Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, double Nam, bool isE)
	{
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		double Nv_vals;
		double Nc_vals;
		double mu_val = 0.;
		std::function<double(Material_base, double, double, double)> func_ = [this](Material_base material_, double T_, double Ndp_, double Nam_)
		{
			return get_mobility(material_.electron.a, material_.electron.b, Ndp_, Nam_, T_);
		};
		if (isE)
			func_ = [this](Material_base material_, double T_, double Ndp_, double Nam_)
		{
			return get_mobility(material_.hole.a, material_.hole.b, Ndp_, Nam_, T_);
		};
		while (T < T_End)
		{
			try
			{
				Nv_vals = Nv(material, T);
				Nc_vals = Nc(material, T);
				double temp = get_fermi(Nc_vals, Nv_vals, T, Ndo, 1e16,
					material.Eg, 0.1, Ed);
				mu_val = func_(material, T, 0, Nam);
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

	std::vector<std::pair<double, double>> Phys_plot::find_sigma_or_rho_T(Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, double Nam, bool isSigma)
	{
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		double sigma = 0.;
		double Nv_vals;
		double Nc_vals;
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
				Nv_vals = Nv(material, T);
				Nc_vals = Nc(material, T);
				double temp = get_fermi(Nc_vals, Nv_vals, T, Ndo, 1e16,
					material.Eg, 0.1, Ed);
				mu_e_val = get_mobility(material.electron.a, material.electron.b,
					Ndo, Nam, T);
				mu_p_val = get_mobility(material.hole.a, material.hole.b,
					Ndo, Nam, T);
				p_val = get_p(Nv_vals, temp, T);
				n_val = get_n(Nc_vals, material.Eg, temp, T);
				sigma = 100 * PhysConst.e * (n_val * mu_e_val + p_val * mu_p_val);
				result.push_back({ T, func(sigma) });
				T += T_Step;
			}
			catch (...)
			{
				break;
			}
		}
		return result;
	}

	std::vector<std::pair<double, double>> Phys_plot::find_p_or_n_T(Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, bool isP)
	{
		double T = T_Begin;
		std::vector<std::pair<double, double>> result;
		double Nv_vals;
		double Nc_vals;
		std::function<double(double, double, double, double, Material_base)> func =
			[this](double T_, double mu_, double Nv, double Nc, Material_base material_)
		{return get_n(Nc, material_.Eg, mu_, T_); };
		if (isP)
			func = [this](double T_, double mu_, double Nv, double Nc, Material_base material_) {return get_p(Nv, mu_, T_); };
		while (T < T_End)
		{
			try
			{
				Nv_vals = Nv(material, T);
				Nc_vals = Nc(material, T);
				double temp = get_fermi(Nc_vals, Nv_vals, T, Ndo, 1e16,
					material.Eg, 0.1, Ed);
				result.push_back({ T, func(T, temp, Nv_vals, Nc_vals, material) });
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
		Material_base material, double T, double Ed, double begin, double end, double Ndo_step, double Nam)
	{
		return find_sigma_or_rho_ndo(material, T, Ed, begin, end, Ndo_step, Nam, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::rho_ndo(
		Material_base material, double T, double Ed, double begin, double end, double Ndo_step, double Nam)
	{
		return find_sigma_or_rho_ndo(material, T, Ed, begin, end, Ndo_step, Nam, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::mu_e_T(
		Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, double Nam)
	{
		return find_mu_e_or_mu_p_T(material, Ndo, Ed, T_Begin, T_End, T_Step, Nam, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::mu_p_T(
		Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, double Nam)
	{
		return find_mu_e_or_mu_p_T(material, Ndo, Ed, T_Begin, T_End, T_Step, Nam, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::sigma_T(
		Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, double Nam)
	{
		return find_sigma_or_rho_T(material, Ed, T_Begin, T_End, T_Step, Ndo, Nam, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::rho_T(
		Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo, double Nam)
	{
		return find_sigma_or_rho_T(material, Ed, T_Begin, T_End, T_Step, Ndo, Nam, false);
	}

	std::vector<std::pair<double, double>> Phys_plot::p_T(
		Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo)
	{
		return find_p_or_n_T(material, Ed, T_Begin, T_End, T_Step, Ndo, true);
	}

	std::vector<std::pair<double, double>> Phys_plot::n_T(
		Material_base material, double Ed, double T_Begin, double T_End, double T_Step, double Ndo)
	{
		return find_p_or_n_T(material, Ed, T_Begin, T_End, T_Step, Ndo, false);
	}
}