//#pragma once
//#define _USE_MATH_DEFINES
//#include <functional>
//#include <map>
//#include <math.h>
//#include <vector>
//
//namespace fompy
//{
//	/// <summary>
//	/// The electron charge
//	/// </summary>
//	const double e = 4.803e-10;
//	/// <summary>
//	/// The Boltzmann constant.
//	/// </summary>
//	const double k = 1.381e-16;
//	/// <summary>
//	/// The reduced plank constant
//	/// </summary>
//	const double h_bar = 1.055e-27;
//
//	const double me = 9.109e-28;
//
//	const double eV = 1.602e-12;
//
//	const double angstrom = 1e-8;
//
//	const double amu = 1.661e-24;
//	/// <summary>
//	/// EN:Calculate the conductivity of a material.
//	/// If there are several types of charge carriers,
//	/// you should sum up the conductivities calculated for these types.
//	/// </summary>
//	/// <param name="n">EN:The carrier concentration(cm^-3)</param>
//	/// <param name="mobility">EN:The carrier mobility(cm^2/(Volt*second))</param>
//	/// <returns>The carrier concentration(cm^3)</returns>
//	double conductivity(double n, double mobility)
//	{
//		return e * n * mobility;
//	}
//
//	/// <summary>
//	/// Calculate the concentration of charge carriers.
//	/// </summary>
//	/// <param name="resistivity">The resistivity of the material(??)</param>
//	/// <param name="mobility">The carrier mobility(cm^2/(Volt*second))</param>
//	/// <returns>The width of the depletion region(cm)</returns>
//	double concentration(double resistivity, double mobility)
//	{
//		return 1 / (resistivity * mobility * e);
//	}
//
//	/// <summary>
//	/// Calculate the width of the depletion region,
//	/// using the approximation of full depletion.
//	/// </summary>
//	/// <param name="eps">The dielectric constant</param>
//	/// <param name="n">EN:The carrier concentration(cm^-3)</param>
//	/// <param name="d_phi">The difference of potentials(Volt)</param>
//	/// <returns>The width of the depletion region(cm)</returns>
//	double depletion_width(double eps, double n, double d_phi)
//	{
//		return sqrt(eps * d_phi / (2 * M_PI * e * n));
//	}
//
//	/// <summary>
//	/// Calculate the Debye length (screening length).
//	/// </summary>
//	/// <param name="eps">The dielectric constant</param>
//	/// <param name="n">EN:The carrier concentration(cm^-3)</param>
//	/// <param name="T"> The temperature(K)</param>
//	/// <returns>The Debye length(cm)</returns>
//	double debye_length(double eps, double n, double T)
//	{
//		return sqrt(eps * k * T / (4 * M_PI * pow(e, 2) * n));
//	}
//
//	/// <summary>
//	/// Calculate the energy of the electron in a hydrogen-like atom.
//	/// </summary>
//	/// <param name="eps"></param>
//	/// <param name="m">The reduced (effective) mass of the electron</param>
//	/// <returns> The energy of the electron(erg)</returns>
//	double hydrogen_like_energy(double eps, double m)
//	{
//		return pow(e, 4) * m / (2 * pow(h_bar, 2)) / pow(eps, 2);
//	}
//
//	/// <summary>
//	/// 
//	/// </summary>
//	/// <param name="eps"></param>
//	/// <param name="m"></param>
//	/// <returns></returns>
//	double hydrogen_like_radius(double eps, double m)
//	{
//		return eps * pow(h_bar, 2) / (m * pow(e, 2));
//	}
//
//	/// <summary>
//	/// A class to calculate properties of a crystal lattice.
//	/// </summary>
//	class CrystalLattice
//	{
//	public:
//		double a;
//		double m;
//		double r;
//		double N;
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <param name="a_"> The lattice parameter [cm]</param>
//		/// <param name="m_">The mass of an atom (the average mass in case of there being several types of atoms) [g]</param>
//		/// <param name="r_">The maximum radius of non-intersecting spheres around atoms [cm]</param>
//		/// <param name="N_">The number of atoms in a cell [1]</param>
//		CrystalLattice(double a_, double m_, double r_, double N_)
//		{
//			a = a_;
//			m = m_;
//			r = r_;
//			N = N_;
//		}
//
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <returns>Get the packing density [1]</returns>
//		double packing_density() const
//		{
//			return N * 4 / 3 * M_PI * pow(r, 3) / pow(a, 3);
//		}
//
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <returns>Get the concentration [cm<sup>&minus;3</sup>]</returns>
//		double concentration() const
//		{
//			return N / pow(a, 3);
//		}
//
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <returns>Get the density [g cm<sup>&minus;3</sup>]</returns>
//		double density() const
//		{
//			return concentration() * m;
//		}
//	};
//
//	/// <summary>
//	/// A class to calculate properties of a primitive cubic lattice (extends `CrystalLattice`).
//	/// </summary>
//	class PrimitiveCubicLattice : public CrystalLattice
//	{
//	public:
//		/// <summary>
//		/// Construct the necessary parameters for the `PrimitiveCubicLattice` object.
//		/// Calls the base class constructor, replacing the following parameters :
//		/// </summary>
//		/// <param name="a_">The lattice parameter [cm]</param>
//		/// <param name="m_">The mass of an atom (the average mass in case of there being several types of atoms) [g]</param>
//		PrimitiveCubicLattice(double a_, double m_) :CrystalLattice(a_, m_, a_ / 2, 1)
//		{
//
//		}
//	};
//
//	/// <summary>
//	/// A class to calculate properties of a face-centered cubic lattice (extends `CrystalLattice`).
//	/// </summary>
//	class FaceCenteredCubicLattice : public CrystalLattice
//	{
//		/// <summary>
//		/// Construct the necessary parameters for the `BodyCenteredCubicLattice` object.
//		/// Calls the base class constructor, replacing the following parameters :
//		/// </summary>
//		/// <param name="a_">The lattice parameter [cm]</param>
//		/// <param name="m_">The mass of an atom (the average mass in case of there being several types of atoms) [g]</param>
//		FaceCenteredCubicLattice(double a_, double m_) :CrystalLattice(a_, m_, a_* sqrt(2) / 4, 4)
//		{
//
//		}
//	};
//
//	/// <summary>
//	/// A class to calculate properties of a body-centered cubic lattice (extends `CrystalLattice`).
//	/// </summary>
//	class BodyCenteredCubicLattice :public CrystalLattice
//	{
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <param name="a_">The lattice parameter [cm].</param>
//		/// <param name="m_">The mass of an atom (the average mass in case of there being several types of atoms) [g].</param>
//		BodyCenteredCubicLattice(double a_, double m_) :CrystalLattice(a_, m_, a_* sqrt(3) / 4, 2)
//		{
//
//		}
//	};
//
//	/// <summary>
//	/// A class to calculate properties of a diamond-like lattice.
//	/// </summary>
//	class DiamondLikeLattice :public CrystalLattice
//	{
//	public:
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <param name="a_"></param>
//		/// <param name="m_"></param>
//		DiamondLikeLattice(double a_, double m_) :CrystalLattice(a_, m_, a_* sqrt(3) / 8, 8)
//		{
//
//		}
//	};
//
//	class Entity
//	{
//	protected:
//		const size_t number_of_iteration = 1000000;
//
//		double left_boundary;
//		double right_boundary;
//		const double precision;
//		const std::function<double(double)>& function;
//		const std::function<double(double)>& derivative;
//		bool need_to_border_cuttoff;
//		virtual void checkingFunctionExisting() { }
//		virtual double get_next_value(double current)
//		{
//			return WRONG_SOLUTION;
//		}
//		virtual double get_initial_value()
//		{
//			return WRONG_SOLUTION;
//		}
//		virtual bool is_valid()
//		{
//			return false;
//		}
//		virtual bool check_result(double current, double previous)
//		{
//			return abs(current - previous) < precision;
//		}
//	public:
//		explicit Entity(const double left_boundary_, const double right_boundary_,
//			const double precision_, const std::function<double(double)>& function_,
//			const std::function<double(double)>& derivative_ = nullptr, bool need_to_border_cuttoff_ = false) :
//			left_boundary(left_boundary_), right_boundary(right_boundary_),
//			precision(precision_), function(function_), derivative(derivative_), need_to_border_cuttoff(need_to_border_cuttoff_)
//		{
//		}
//
//		double solve(std::vector<double>& values)
//		{
//			if (!is_valid()) {
//				return WRONG_SOLUTION;
//			}
//			double prev = get_initial_value();
//			values.push_back(prev); \
//				for (size_t i = 0; i < number_of_iteration; ++i)
//				{
//					auto curr = get_next_value(prev);
//					values.push_back(curr);
//					if (curr < left_boundary)
//					{
//						curr = left_boundary;
//					}
//					if (curr > right_boundary)
//					{
//						curr = right_boundary;
//					}
//					if (abs(curr) > 1e-20 && !std::isnormal(curr)) {
//						break;
//					}
//					if (check_result(curr, prev)) {
//						return curr;
//					}
//					prev = curr;
//				}
//			return WRONG_SOLUTION;
//		}
//		const double WRONG_SOLUTION = nan("");
//	};
//
//	class Dichotomy_method final :public Entity
//	{
//		double split_ratio = 2;
//
//		double middle_of_interval(const double left_boundary_, const double right_boundary_)
//		{
//			return  right_boundary_ - (right_boundary_ - left_boundary_) / split_ratio;
//		}
//
//		bool is_valid()override
//		{
//			if (left_boundary > right_boundary || precision > 1 || precision < 0 ||
//				left_boundary == right_boundary || function == nullptr) {
//				return false;
//			}
//			double f_l = function(left_boundary);
//			double f_r = function(right_boundary);
//			if (std::isnan(f_l) || std::isnan(f_r)) {
//				return  false;
//			}
//
//			return true;
//		}
//
//		double get_initial_value() override
//		{
//			return middle_of_interval(left_boundary, right_boundary);
//		}
//
//		double get_next_value(double current) override
//		{
//			double x = function(current);
//			x = x * right_boundary;
//			if (x > 0)
//			{
//				right_boundary = current;
//				return middle_of_interval(left_boundary, right_boundary);
//			}
//			if (x < 0)
//			{
//				left_boundary = current;
//				return middle_of_interval(left_boundary, right_boundary);
//			}
//			return current;
//		}
//	public:
//		explicit Dichotomy_method(const double left_boundary_, const double right_boundary_,
//			const double precision_, const std::function<double(double)>& function_,
//			const std::function<double(double)>& derivative_, bool need_to_border_cuttoff_ = false)
//			: Entity(left_boundary_, right_boundary_, precision_, function_, derivative_, need_to_border_cuttoff_)
//		{}
//	};
//
//	double _fd1h_lt_m2(double phi)
//	{
//		double exp_phi = exp(phi);
//		double t = exp_phi * 7.38905609893065023e0;
//		return exp_phi * (0.886226925452758014e0
//			- exp_phi * (19894.4553386951666e0
//				+ t * (4509.64329955948557e0
//					+ t * (303.461789035142376e0
//						+ t * (5.7574879114754736e0
//							+ t * 0.00275088986849762610e0
//							)))) / (63493.915041308052e0
//								+ t * (19070.1178243603945e0
//									+ t * (1962.19362141235102e0
//										+ t * (79.250704958640158e0
//											+ t)))));
//	}
//
//	double _fd1h_m2_to_0(double phi)
//	{
//		double s = -0.5e0 * phi;
//		double t = 1e0 - s;
//		return (149.462587768865243e0
//			+ t * (22.8125889885050154e0
//				+ t * (-0.629256395534285422e0
//					+ t * (9.08120441515995244e0
//						+ t * (3.35357478401835299e0
//							+ t * (-0.473677696915555805e0
//								+ t * (-0.467190913556185953e0
//									+ t * (-0.0880610317272330793e0
//										- t * 0.00262208080491572673e0
//										)))))))) / (269.94660938022644e0
//											+ s * (343.6419926336247e0
//												+ s * (323.9049470901941e0
//													+ s * (218.89170769294024e0
//														+ s * (102.31331350098315e0
//															+ s * (36.319337289702664e0
//																+ s * (8.3317401231389461e0
//																	+ s)))))));
//	}
//
//	double _fd1h_0_to_2(double phi)
//	{
//		double t = 0.5e0 * phi;
//		return (71652.717119215557e0
//			+ t * (134954.734070223743e0
//				+ t * (153693.833350315645e0
//					+ t * (123247.280745703400e0
//						+ t * (72886.293647930726e0
//							+ t * (32081.2499422362952e0
//								+ t * (10210.9967337762918e0
//									+ t * (2152.71110381320778e0
//										+ t * 232.906588165205042e0
//										)))))))) / (105667.839854298798e0
//											+ t * (31946.0752989314444e0
//												+ t * (71158.788776422211e0
//													+ t * (15650.8990138187414e0
//														+ t * (13521.8033657783433e0
//															+ t * (1646.98258283527892e0
//																+ t * (618.90691969249409e0
//																	+ t * (-3.36319591755394735e0
//																		+ t))))))));
//	}
//
//	double _fd1h_2_to_5(double phi) {
//		double t = 0.3333333333333333333e0 * (phi - 2e0);
//		return (23744.8706993314289e0
//			+ t * (68257.8589855623002e0
//				+ t * (89327.4467683334597e0
//					+ t * (62766.3415600442563e0
//						+ t * (20093.6622609901994e0
//							+ t * (-2213.89084119777949e0
//								+ t * (-3901.66057267577389e0
//									- t * 948.642895944858861e0
//									))))))) / (9488.61972919565851e0
//										+ t * (12514.8125526953073e0
//											+ t * (9903.44088207450946e0
//												+ t * (2138.15420910334305e0
//													+ t * (-528.394863730838233e0
//														+ t * (-661.033633995449691e0
//															+ t * (-51.4481470250962337e0
//																+ t)))))));
//	}
//
//	double _fd1h_5_to_10(double phi) {
//		double t = 0.2e0 * phi - 1e0;
//		return (311337.452661582536e0
//			+ t * (1.11267074416648198e6
//				+ t * (1.75638628895671735e6
//					+ t * (1.59630855803772449e6
//						+ t * (910818.935456183774e0
//							+ t * (326492.733550701245e0
//								+ t * (65507.2624972852908e0
//									+ t * 4809.45649527286889e0
//									))))))) / (39721.6641625089685e0
//										+ t * (86424.7529107662431e0
//											+ t * (88163.7255252151780e0
//												+ t * (50615.7363511157353e0
//													+ t * (17334.9774805008209e0
//														+ t * (2712.13170809042550e0
//															+ t * (82.2205828354629102e0
//																- t))))))) * 0.999999999999999877e0;
//	}
//
//	double _fd1h_10_to_20(double phi)
//	{
//		double t = 0.1e0 * phi - 1e0;
//		return (7.26870063003059784e6
//			+ t * (2.79049734854776025e7
//				+ t * (4.42791767759742390e7
//					+ t * (3.63735017512363365e7
//						+ t * (1.55766342463679795e7
//							+ t * (2.97469357085299505e6
//								+ t * 154516.447031598403e0
//								)))))) / (340542.544360209743e0
//									+ t * (805021.468647620047e0
//										+ t * (759088.235455002605e0
//											+ t * (304686.671371640343e0
//												+ t * (39289.4061400542309e0
//													+ t * (582.426138126398363e0
//														+ t * (11.2728194581586028e0
//															- t)))))));
//	}
//
//	double _fd1h_20_to_40(double phi)
//	{
//		double t = 0.05e0 * phi - 1e0;
//		return (4.81449797541963104e6
//			+ t * (1.85162850713127602e7
//				+ t * (2.77630967522574435e7
//					+ t * (2.03275937688070624e7
//						+ t * (7.41578871589369361e6
//							+ t * (1.21193113596189034e6
//								+ t * 63211.9545144644852e0
//								)))))) / (80492.7765975237449e0
//									+ t * (189328.678152654840e0
//										+ t * (151155.890651482570e0
//											+ t * (48146.3242253837259e0
//												+ t * (5407.08878394180588e0
//													+ t * (112.195044410775577e0
//														- t))))));
//	}
//
//	double _fd1h_gt_40(double phi)
//	{
//		double factor = 2e0 / 3e0;
//		double w = 1e0 / (phi * phi);
//		double s = 1e0 - 1600e0 * w;
//		return phi * sqrt(phi) * factor * (1e0 + w
//			* (8109.79390744477921e0
//				+ s * (342.069867454704106e0
//					+ s * 1.07141702293504595e0))
//			/ (6569.98472532829094e0
//				+ s * (280.706465851683809e0
//					+ s)));
//	}
//
//	double fd1(double phi)
//	{
//		if (phi < -2e0)
//			return _fd1h_lt_m2(phi);
//		if (phi < 0e0)
//			return _fd1h_m2_to_0(phi);
//		if (phi < 2e0)
//			return _fd1h_0_to_2(phi);
//		if (phi < 5e0)
//			return _fd1h_2_to_5(phi);
//		if (phi < 10e0)
//			return _fd1h_5_to_10(phi);
//		if (phi < 20e0)
//			return _fd1h_10_to_20(phi);
//		if (phi < 40e0)
//			return _fd1h_20_to_40(phi);
//		return _fd1h_gt_40(phi);
//	}
//
//	class Semiconductor
//	{
//	public:
//		// The crystal lattice.
//		CrystalLattice* lattice;
//		// The effective mass of electrons
//		double me;
//		// The effective mass of holes
//		double mh;
//		// The engergy gap
//		double Eg;
//		// The electron affinity
//		double chi;
//		// The dielectron constant
//		double eps;
//		std::map<std::string, double> donor_energy;
//		std::map<std::string, double> acceptor_energy;
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <param name="me_eff">The effective mass of an electron [g].</param>
//		/// <param name="mh_eff">The effective mass of a hole [g].</param>
//		/// <param name="Eg">The energy gap [erg].</param>
//		/// <param name="chi">The electron affinity [erg].</param>
//		/// <param name="eps">The dielectric constant [1].</param>
//		/// <param name="lattice">The crystal lattice.</param>
//		Semiconductor(double me_eff, double mh_eff, double Eg,
//			double chi = std::numeric_limits<double>::min(),
//			double eps = std::numeric_limits<double>::min(),
//			CrystalLattice* lattice = nullptr) :
//			lattice(lattice), me(me_eff), mh(mh_eff), Eg(Eg), chi(chi), eps(eps)
//		{
//
//		}
//
//		/// <summary>
//		///  Calculate the effective density of states.
//		/// </summary>
//		/// <param name="m_eff">The effective mass [g].</param>
//		/// <param name="T">The temperature [K].</param>
//		/// <returns>The effective density of states [cm<sup>&minus;3</sup>].</returns>
//		double effective_state_density(double m_eff, double T)
//		{
//			return 2 * pow(2 * M_PI * m_eff * k * T / pow(2 * M_PI * h_bar, 2), 3 / 2);
//		}
//
//		/// <summary>
//		/// Calculate the effective density of states for electrons in the conduction band.
//		/// </summary>
//		/// <param name="T">The temperature [K].</param>
//		/// <returns>The effective density of states for electrons in the conduction band [cm<sup>&minus;3</sup>].</returns>
//		double Nc(double T = 300)
//		{
//			return effective_state_density(me, T);
//		}
//
//		/// <summary>
//		///  Calculate the effective density of states for holes in the valence band.
//		/// </summary>
//		/// <param name="T">The temperature [K].</param>
//		/// <returns>   The effective density of states for holes in the valence band [cm<sup>&minus;3</sup>]. </returns>
//		double Nv(double T = 300)
//		{
//			effective_state_density(mh, T);
//		}
//
//		double intrinsic_charge_imbalance(double Ef, double T)
//		{
//			return p_concentration(Ef, T) - n_concentration(Ef, T);
//		}
//
//		virtual double charge_imbalance(double Ef, double T)
//		{
//			return p_concentration(Ef, T) - n_concentration(Ef, T);
//		}
//
//		double solve_electroneutrality_equation(std::function<double(double, double)> equation, double T)
//		{
//			std::vector<double> solves;
//			return  Dichotomy_method(-Eg, 2 * Eg, 1e-12,
//				[T, this](double x) {return charge_imbalance(x, T); }, nullptr, false).solve(solves);
//		}
//
//		double fermi_level(double T = 300)
//		{
//			return solve_electroneutrality_equation([this](double Ef_, double T_) {return charge_imbalance(Ef_, T_); }, T);
//		}
//
//		double n_concentration(double Ef = std::numeric_limits<double>::min(), double T = 300)
//		{
//			if (abs(Ef - std::numeric_limits<double>::min()) < 0.1)
//			{
//				Ef = fermi_level(T);
//			}
//			return Nc(T) * fd1((Ef - Eg) / (k * T));
//		}
//
//		double p_concentration(double Ef = std::numeric_limits<double>::min(), double T = 300)
//		{
//			if (abs(Ef - std::numeric_limits<double>::min()) < 0.1)
//			{
//				Ef = fermi_level(T);
//			}
//			return Nc(T) * fd1((-Ef) / (k * T));
//		}
//
//		double intrinsic_fermi_level(double T = 300)
//		{
//			return solve_electroneutrality_equation([this](double Ef_, double T_) {return intrinsic_charge_imbalance(Ef_, T_); }, T);
//		}
//
//		double i_concentration(double T)
//		{
//			return n_concentration(intrinsic_fermi_level(T), T);
//		}
//
//		~Semiconductor()
//		{
//			delete lattice;
//		}
//	};
//
//	double fermi(double E, double Ef, double T)
//	{
//		double arg = (E - Ef) / (k * T);
//		if (arg > 500)
//			return 0;
//		return 1 / (1 + exp(arg));
//	}
//
//	class DopedSemiconductor : public Semiconductor
//	{
//	public:
//		double Na;
//		double Ea;
//		double Nd;
//		double Ed;
//		DopedSemiconductor(Semiconductor mat, double Na, double Ea, double Nd, double Ed) :
//			Semiconductor(mat.me, mat.mh, mat.Eg, mat.chi, mat.eps, mat.lattice), Na(Na), Ea(Ea), Nd(Nd), Ed(Ed)
//		{
//		}
//
//		/// <summary>
//		/// 
//		/// </summary>
//		/// <param name="material"></param>
//		/// <param name="mobility"></param>
//		/// <param name="dopant"></param>
//		/// <param name="resistiviry"></param>
//		/// <returns></returns>
//		static DopedSemiconductor from_materials(Semiconductor material, double mobility, std::string dopant, double resistivity)
//		{
//			double N = concentration(resistivity, mobility);
//			double Na = 0, Nd = 0;
//			double Ea = 0;
//			double Ed = material.Eg;
//			if (material.acceptor_energy.find(dopant) != material.acceptor_energy.end())
//			{
//				Ea = material.acceptor_energy[dopant];
//				Na = N;
//			}
//			else if (material.donor_energy.find(dopant) != material.donor_energy.end())
//			{
//				Ed = material.donor_energy[dopant];
//				Nd = N;
//			}
//			else
//				throw new std::exception("Unknown dopant");
//			return DopedSemiconductor(material, Na, Ea, Nd, Ed);
//		}
//
//		double p_donor_concentration(double Ef = std::numeric_limits<double>::min(), double T = 300)
//		{
//			if (abs(Ef - std::numeric_limits<double>::min()) < 0.001)
//			{
//				Ef = fermi_level(T);
//			}
//			return Nd * (1 - fermi(Ed, Ef, T));
//		}
//
//		double n_acceptor_concentration(double Ef = std::numeric_limits<double>::min(), double T = 300)
//		{
//			if (abs(Ef - std::numeric_limits<double>::min()) < 0.001)
//			{
//				Ef = fermi_level(T);
//			}
//			return Na * (1 - fermi(Ea, Ef, T));
//		}
//
//		double  charge_imbalance(double Ef, double T) override
//		{
//			return p_concentration(Ef, T) + p_donor_concentration(Ef, T)
//				- n_concentration(Ef, T) - n_acceptor_concentration(Ef, T);
//		}
//	};
//
//	struct Materials
//	{
//		//http://www.ioffe.ru/SVA/NSM/Semicond/Si/index.html
//		Semiconductor* Si = new Semiconductor(0.36 * me, 0.81 * me, 1.12 * eV, 4.05 * eV, 11.7, new DiamondLikeLattice(5.4307 * angstrom, 28 * amu));
//		//http://www.ioffe.ru/SVA/NSM/Semicond/Ge/index.html
//		Semiconductor* Ge = new Semiconductor(0.22 * me, 0.34 * me, 0.661 * eV, 4.0 * eV, 16.2, new DiamondLikeLattice(5.660 * angstrom, 72.6 * amu));
//		//http://www.ioffe.ru/SVA/NSM/Semicond/GaAs/index.html
//		Semiconductor* GaAs = new Semiconductor(0.063 * me, 0.53 * me, 1.424 * eV, 4.07 * eV, 12.9, new DiamondLikeLattice(5.6533 * angstrom, (69.723 + 74.922) / 2 * amu));
//		Materials()
//		{
//			//Si
//			Si->donor_energy.insert({ "As", Si->Eg - 0.054 * eV });
//			Si->donor_energy.insert({ "P", Si->Eg - 0.045 * eV });
//			Si->donor_energy.insert({ "Sb", Si->Eg - 0.043 * eV });
//			Si->acceptor_energy.insert({ "Al",  0.072 * eV });
//			Si->acceptor_energy.insert({ "B",  0.045 * eV });
//			Si->acceptor_energy.insert({ "Ga",  0.074 * eV });
//			Si->acceptor_energy.insert({ "In",  0.157 * eV });
//			//Ge
//			Ge->donor_energy.insert({ "As", Ge->Eg - 0.014 * eV });
//			Ge->donor_energy.insert({ "P", Ge->Eg - 0.013 * eV });
//			Ge->donor_energy.insert({ "Sb", Ge->Eg - 0.010 * eV });
//			Ge->donor_energy.insert({ "Bi", Ge->Eg - 0.013 * eV });
//			Ge->donor_energy.insert({ "Li'", Ge->Eg - 0.093 * eV });
//			Ge->acceptor_energy.insert({ "Al", 0.011 * eV });
//			Ge->acceptor_energy.insert({ "B'", 0.011 * eV });
//			Ge->acceptor_energy.insert({ "Ga", 0.011 * eV });
//			Ge->acceptor_energy.insert({ "In", 0.012 * eV });
//			Ge->acceptor_energy.insert({ "Tl", 0.013 * eV });
//			//GaAs
//			GaAs->donor_energy.insert({ "S", GaAs->Eg - 0.006 * eV });
//			GaAs->donor_energy.insert({ "Se", GaAs->Eg - 0.006 * eV });
//			GaAs->donor_energy.insert({ "Si", GaAs->Eg - 0.006 * eV });
//			GaAs->donor_energy.insert({ "Ge", GaAs->Eg - 0.006 * eV });
//			GaAs->donor_energy.insert({ "Sn", GaAs->Eg - 0.006 * eV });
//			GaAs->donor_energy.insert({ "Te", GaAs->Eg - 0.03 * eV });
//			GaAs->donor_energy.insert({ "C'",0.02 * eV });
//			GaAs->donor_energy.insert({ "Ge",0.03 * eV });
//			GaAs->donor_energy.insert({ "Zn",0.025 * eV });
//			GaAs->donor_energy.insert({ "Sn",0.02 * eV });
//		}
//		~Materials()
//		{
//			delete Si;
//			delete Ge;
//			delete GaAs;
//		}
//	};
//}