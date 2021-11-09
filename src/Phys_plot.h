#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include "Dichotomy_method.h"
#include "Newton_method.h"
namespace phfm
{
	static struct phys_const
	{
		/// <summary>
		/// The electron charge
		/// </summary>
		double e = 4.803e-10;
		/// <summary>
		/// The Boltzmann constant.
		/// </summary>
		//const double k = 1.381e-16;
		const double k = 1.381e-23;
		/// <summary>
		/// The reduced plank constant
		/// </summary>
		const double h_bar = 1.055e-27;
		/// <summary>
		/// The mass of an electron.
		/// </summary>
		const double me = 9.109e-28;
		const double eV = 1.6021e-12;
		const double angstrom = 1e-8;
		const double amu = 1.661e-24;
		//
	}PhysConst;

	static struct charge_carrier
	{
		double a;
		double b;
	};

	static struct Material_base
	{
		// coefficients for electrons
		charge_carrier electron;
		// coefficients for holes
		charge_carrier hole;
		// The effective mass of electrons
		double me;
		// The effective mass of holes
		double mh;
		// The engergy gap
		double Eg;
		// The electron affinity
		double chi;
		// The dielectron constant
		double epsilon;
		Material_base(double ae, double be, double ah, double bh,
			double Eg, double chi, double epsilon, double me, double mh) :Eg(Eg), chi(chi), epsilon(epsilon), me(me), mh(mh)
		{
			electron.a = ae;
			electron.b = be;
			hole.a = ah;
			hole.b = bh;
		}
	};
	//Коэфы для электронов и дырок взяты уже высчитанные другими,
	//остальные значения стандартные и взяты с сайта http://www.ioffe.ru/SVA/NSM/Semicond/
	// Si/index.html
	// Ge/index.html
	// GaAs/index.html
	static struct spec_material_cont
	{
		Material_base Si = Material_base(6.43e6, 7.13e-12, 1.8e6, 1.04e-12,
			1.12 * 1.60218e-19, 4.05 * PhysConst.eV, 11.7, 0.36 * PhysConst.me, 0.81 * PhysConst.me);
		Material_base Ge = Material_base(18.7e6, 30.6e-12, 8.02e6, 21.3e-12,
			0.661 * 1.60218e-19, 4.0 * PhysConst.eV, 16.2, 0.22 * PhysConst.me, 0.34 * PhysConst.me);
		Material_base GaAs = Material_base(53.5e6, 14.8e-12, 1.8e6, 2.38e-12,
			1.424 * 1.60218e-19, 4.07 * PhysConst.eV, 12.9, 0.063 * PhysConst.me, 0.53 * PhysConst.me);
	}Materials;

	/// <summary>
	/// TODO: add method for changing type of numerical method of calculation
	/// </summary>
	class Phys_plot final
	{
		double left_boundary = 0;
		double right_boundary = 10. - left_boundary;
		double precision = 10e-30;
		double Ed_convert(double Ed);

		double equation(Material_base material, double mu, double Ndo, double T, double Eg, double Ed);

		double derivative(Material_base material, double mu, double Ndo, double T, double Eg, double Ed);

		double Nv(Material_base material, double T);

		double Nc(Material_base material, double T);

		double p(Material_base material, double T, double mu);

		double n(Material_base material, double T, double mu, double Eg);

		double mu_e(Material_base material, double T, double Ndp, double Nam);

		double mu_p(Material_base material, double T, double Ndp, double Nam);

		double Ndp(Material_base material, double Ndo, double Eg, double Ed, double mu, double T);

		std::vector<std::pair<double, double>> find_sigma_or_rho_ndo(
			Material_base material, double T, double Ndo_step, double Ed, bool isSigma);

		std::vector<std::pair<double, double>> find_mu_e_or_mu_p_T(
			Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step, bool isE);
		std::vector<std::pair<double, double>> find_sigma_or_rho_T(
			Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed, bool isSigma);
		std::vector<std::pair<double, double>> find_p_or_t_T(
			Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed, bool isP);
	public:
		std::vector<std::pair<double, double>> sigma_ndo(
			Material_base material, double T, double Ndo_step, double Ed);

		std::vector<std::pair<double, double>> rho_ndo(
			Material_base material, double T, double Ndo_step, double Ed);

		std::vector<std::pair<double, double>> mu_e_T(
			Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step);
		std::vector<std::pair<double, double>> mu_p_T(
			Material_base material, double Ndo, double Ed, double T_Begin, double T_End, double T_Step);

		std::vector<std::pair<double, double>> sigma_T(
			Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed);

		std::vector<std::pair<double, double>> rho_T(
			Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed);

		std::vector<std::pair<double, double>> p_T(
			Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed);

		std::vector<std::pair<double, double>> n_T(
			Material_base material, double Ndo, double T_Begin, double T_End, double T_Step, double Ed);
	};
}

//How to use
//#include "Phys_plot.h"
//
//int main()
//{
//	auto si = phfm::Materials.Si;
//	auto fome = new phfm::Phys_plot();
//	auto result = fome->sigma_ndo(si, 300, 1e15, 0.5);
//	delete fome;
//	return 0;
//}