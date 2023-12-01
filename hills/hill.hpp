#pragma once
#include <string>
#include <vector>
#include "../osj_math.hpp"

enum class ProfileType
{
    ICR1992,
    ICR1996,
    ICR2008
};

struct ProfileData
{
    std::string name = "";
    ProfileType type;

    int gates;
    double w;
    double hS;
    double h;
    double n;
    double gamma;
    double alpha;
    double e;
    double es;
    double t;
    double r1;
    double beta0;
    double betaP;
    double betaK;
    double betaL;
    double s;
    double l1;
    double l2;
    double rL;
    double r2L;
    double r2;
    double a;
    double rA;
    double betaA;
    double b1;
    double b2;
    double bK;
    double bU;
    double d;
    double q;
    double g;
};

class AngleData
{
    double m_radians;
    osj::vec2 m_tangent;
    osj::vec2 m_normal;

public:
    AngleData(double angle, bool degrees = false)
    {
        m_radians = (degrees ? osj::deg2rad(angle) : angle);
        m_tangent = osj::from_radians(m_radians);
        m_normal = m_tangent.perp();
    }

    osj::vec2 normal() const noexcept { return m_normal; }
    osj::vec2 tangent() const noexcept { return m_tangent; }
};

class Hill
{
private:
    ProfileType m_profile_type;
    osj::vec2 A, B, C1, C2, CL, CV, E1, E2, T, F, P, K, L, U, V, X;
    double m_gamma, m_alpha, m_beta_0, m_beta_k, m_beta_p, m_beta_l, m_beta_a;
    double m_r1, m_r2, m_rl, m_r2l, m_ra;
    double m_t, m_a, m_e, m_es, m_s, m_h, m_n, m_l1;
    double m_b1, m_b2, m_bk, m_bu;
    int m_gates;

    struct
    {
        double d;
        double f;
        double l;
        double C;
    } inrun;

    struct
    {
        double u;
        double v;
    } knoll;

    struct
    {
        double tau;
        double a;
        double b;
        double c;
    } outrun;

    AngleData m_e1_data, m_e2_data, m_f_data, m_p_data, m_k_data, m_l_data;

public:
    Hill(const ProfileData &pd);
    double inrun_height(double x) const;
    double inrun_width() const;
    double lhill_height(double x) const;
    double lhill_width(double x) const;
    std::vector<osj::vec2> generate_lhill_points(int accuracy = 1000) const;
    std::vector<osj::vec2> generate_inrun_points() const;
    osj::vec2 gate_point(int nr);
};
