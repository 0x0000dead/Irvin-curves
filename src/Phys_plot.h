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
		double e = 1.6e-19;//4.803e-10
		/// <summary>
		/// The Boltzmann constant.
		/// </summary>
		//const double k = 1.381e-16;
		const double k = 9.617e-5;
		/// <summary>
		/// The reduced plank constant
		/// </summary> 
		const double h_bar = 1.054571817e-27; // 1.055e-27
		/// <summary>
		/// The mass of an electron.
		/// </summary>
		const double me = 0.510999895e6; // 9.109e-28 gramm
		const double eV = 1.6021e-12; // to transfer to sgs
		const double angstrom = 1e-8;
		const double amu = 1.661e-24; // ?
		const double c = 3e10; // [cm / s]
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
			1.12, 4.05 * PhysConst.eV, 11.7, 0.36 * PhysConst.me, 0.81 * PhysConst.me);
		Material_base Ge = Material_base(18.7e6, 30.6e-12, 8.02e6, 21.3e-12,
			0.661, 4.0 * PhysConst.eV, 16.2, 0.22 * PhysConst.me, 0.34 * PhysConst.me);
		Material_base GaAs = Material_base(5.35399e7, 1.48331e-11, 1.13786e6, 2.37672e-12,
			1.424, 4.07 * PhysConst.eV, 12.9, 0.063 * PhysConst.me, 0.53 * PhysConst.me);
	}Materials;

	/// <summary>
	/// TODO: add method for changing type of numerical method of calculation
	/// </summary>
	class Phys_plot final
	{

		double Nv(Material_base material, double T);

		double Nc(Material_base material, double T);
		std::vector<std::pair<double, double>> find_sigma_or_rho_ndo(
			Material_base material, double T, double Ed, double begin, double end, double Ndo_step, double Nam, bool isSigma);

		std::vector<std::pair<double, double>> find_mu_e_or_mu_p_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, double Nam = 1e+16, bool isE = false);
		std::vector<std::pair<double, double>> find_sigma_or_rho_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, double Nam = 1e+16, bool isSigma = false);
		std::vector<std::pair<double, double>> find_p_or_n_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, bool isP = false);
	public:
		std::vector<std::pair<double, double>> sigma_ndo(
			Material_base material, double T, double Ed, double begin = 1e+10, double end = 1e+20, double Ndo_step = 1e+18, double Nam = 1e+16);

		std::vector<std::pair<double, double>> rho_ndo(
			Material_base material, double T, double Ed, double begin = 1e+10, double end = 1e+20, double Ndo_step = 1e+18, double Nam = 1e+16);

		std::vector<std::pair<double, double>> mu_e_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, double Nam = 1e+16);
		std::vector<std::pair<double, double>> mu_p_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, double Nam = 1e+16);

		std::vector<std::pair<double, double>> sigma_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, double Nam = 1e+16);

		std::vector<std::pair<double, double>> rho_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18, double Nam = 1e+16);

		std::vector<std::pair<double, double>> p_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18);

		std::vector<std::pair<double, double>> n_T(
			Material_base material, double Ed, double T_Begin = 100, double T_End = 500, double T_Step = 10, double Ndo = 1e+18);
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
