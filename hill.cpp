#include "hill.hpp"

Hill::Hill(const ProfileData &pd) : m_profile_type(pd.type), m_alpha(osj::deg2rad(pd.alpha)), m_gamma(osj::deg2rad(pd.gamma)),
                                    m_beta_0(osj::deg2rad(pd.beta0)), m_beta_p(osj::deg2rad(pd.betaP)),
                                    m_beta_k(osj::deg2rad(pd.betaK)), m_beta_l(osj::deg2rad(pd.betaL)), m_beta_a(osj::deg2rad(pd.betaA)),
                                    m_e2_data(-m_alpha), m_e1_data(-m_gamma), m_f_data(-m_beta_0), m_p_data(-m_beta_p), m_k_data(-m_beta_k),
                                    m_l_data(-m_beta_l),
                                    m_r1(pd.r1), m_r2(pd.r2), m_rl(pd.rL), m_r2l(pd.r2L), m_ra(pd.rA),
                                    m_gates(pd.gates), m_t(pd.t), m_a(pd.a), m_e(pd.e), m_es(pd.es), m_s(pd.s), m_h(pd.h), m_n(pd.n), m_l1(pd.l1)

{
    if (m_profile_type == ProfileType::ICR1992)
    {
        m_beta_p = m_beta_l = m_beta_k;
    }

    E2 = -m_t * m_e2_data.tangent();
    double diff_angle = m_gamma - m_alpha;

    if (m_profile_type == ProfileType::ICR1992 || m_profile_type == ProfileType::ICR1996)
    {
        C1 = E2 + m_r1 * m_e2_data.normal();
        E1 = C2 - m_r1 * m_e1_data.normal();
        inrun.l = m_r1 * diff_angle;
    }
    else
    {
        inrun.d = 2.0 * m_r1 * std::sin(diff_angle) * std::cos(diff_angle) * std::cos(diff_angle);
        inrun.C = std::tan(diff_angle) / 3.0 / inrun.d / inrun.d;
        inrun.f = std::tan(diff_angle) * inrun.d / 3.0;
        inrun.l = inrun.d * (1.0 + 0.1 * std::tan(diff_angle) * std::tan(diff_angle));
        E1 = E2 - inrun.f * m_e1_data.normal() - inrun.d * m_e1_data.tangent();
    }

    A = E1 - m_e1_data.tangent() * (m_e - inrun.l);
    B = A + m_es * m_e1_data.tangent();

    T = osj::vec2{0, 0};

    // Landing Area
    F = {0, -m_s};
    K = {m_n, -m_h};

    if (m_profile_type == ProfileType::ICR1992)
    {
        P = K - pd.l1 * m_k_data.tangent();
        L = K;
    }
    else
    {
        CL = K + m_rl * m_k_data.normal();
        P = CL - m_rl * m_p_data.normal();
        L = CL - m_rl * m_l_data.normal();
    }

    knoll.u = -P.y + F.y - P.x * std::tan(m_beta_0);
    knoll.v = P.x * (std::tan(m_beta_p) - std::tan(m_beta_0));

    if (m_profile_type == ProfileType::ICR1992 || m_profile_type == ProfileType::ICR1996)
    {
        C2 = L + m_r2 * m_l_data.normal();
        U = osj::vec2{C2.x, C2.y - m_r2};
    }
    else
    {
        outrun.tau = std::atan((std::cos(m_beta_l) - std::pow(m_r2 / m_r2l, 1.0 / 3.0)) / std::sin(m_beta_l));
        outrun.c = 1.0 / (2.0 * m_r2 * std::cos(outrun.tau) * std::cos(outrun.tau) * std::cos(outrun.tau));
        outrun.a = -std::tan(m_beta_l + outrun.tau) / 2.0 / outrun.c;
        outrun.b = -std::tan(outrun.tau) / 2.0f / outrun.c;

        U = L + osj::vec2{outrun.c * std::sin(outrun.tau) * (outrun.a * outrun.a - outrun.b * outrun.b) + std::cos(outrun.tau) * (outrun.b - outrun.a),
                     -outrun.c * std::cos(outrun.tau) * (outrun.a * outrun.a - outrun.b * outrun.b) + std::sin(outrun.tau) * (outrun.b - outrun.a)};
    }

    if (m_beta_a > 0)
    {
        CV = U + osj::vec2{0, m_ra};
        V = CV - m_ra * osj::vec2(-std::sin(m_beta_a), std::cos(m_beta_a));
        double len = m_a - m_beta_a * m_ra;
        X = V + len * osj::vec2(std::cos(m_beta_a), std::sin(m_beta_a));
    }
    else
    {
        V = U;
        X = U + osj::vec2{m_a, 0};
    }
}

double Hill::Inrun(double x) const
{
    if (x >= E2.x)
    {
        return -x * std::tan(m_alpha);
    }

    if (E2.x > x && x >= E1.x)
    {
        if (m_profile_type == ProfileType::ICR1992 || m_profile_type == ProfileType::ICR1996)
        {
            return -std::sqrt(m_r1 * m_r1 - (x - C1.x) * (x - C1.x)) + C1.y;
        }

        double p = 1.0 / (std::tan(m_gamma) * 3.0 * inrun.C);
        double q = (x + m_t * std::cos(m_alpha) + inrun.f * std::sin(m_gamma) + inrun.d * std::cos(m_gamma)) / 2.0f / inrun.C /
                   std::sin(m_gamma);
        double ksi = std::pow((std::sqrt(q * q + p * p * p) + q), (1.0 / 3.0)) -
                     std::pow((std::sqrt(q * q + p * p * p) - q), (1.0 / 3.0));
        return m_t * std::sin(m_alpha) - inrun.f * std::cos(m_gamma) + inrun.d * std::sin(m_gamma) -
               ksi * std::sin(m_gamma) + inrun.C * ksi * ksi * ksi * std::cos(m_gamma);
    }

    return -x * std::tan(m_gamma) + A.y + std::tan(m_gamma) * A.x;
}

double Hill::LandingArea(double x) const
{
    if (x <= P.x)
    {
        return F.y - x * std::tan(m_beta_0) - (3 * knoll.u - knoll.v) * (x / P.x) * (x / P.x) +
               (2 * knoll.u - knoll.v) * (x / P.x) * (x / P.x) * (x / P.x);
    }

    if (P.x < x && x <= L.x)
    {
        if (m_profile_type == ProfileType::ICR1992)
        {
            return std::tan(m_beta_k) * (K.x - x) + K.y;
        }

        return -std::sqrt(m_rl * m_rl - (x - CL.x) * (x - CL.x)) + CL.y;
    }

    if (L.x <= x && x <= U.x)
    {
        if (m_profile_type == ProfileType::ICR2008)
        {
            double ksi = (std::cos(outrun.tau) - std::sqrt(std::cos(outrun.tau) * std::cos(outrun.tau) - 4.0 * outrun.c * (x - L.x - outrun.c * outrun.a * outrun.a * std::sin(outrun.tau) + outrun.a * std::cos(outrun.tau)) * std::sin(outrun.tau))) /
                         2.0 / outrun.c / std::sin(outrun.tau);
            return L.y - outrun.c * std::cos(outrun.tau) * (outrun.a * outrun.a - ksi * ksi) - std::sin(outrun.tau) * (outrun.a - ksi);
        }

        return -std::sqrt(m_r2 * m_r2 - (x - C2.x) * (x - C2.x)) + C2.y;
    }

    if (U.x < x && x < V.x)
    {
        return -std::sqrt(m_ra * m_ra - (x - CV.x) * (x - CV.x)) + CV.y;
    }

    return V.y + std::sin(m_beta_a) * (x - V.x);
}

std::vector<osj::vec2> Hill::GenerateLandingAreaPoints(int accuracy = 1000) const
{
    std::vector<osj::vec2> points{};

    double distance = 0.0;
    int meter = 0;

    auto last = F;

    for (size_t i = 0; i < accuracy * (X.x); i++)
    {
        osj::vec2 curr = {i / (float)accuracy, LandingArea(i / (float)accuracy)};

        if (distance + (curr - last).magnitude() >= meter)
        {
            if (meter - distance < distance + (curr - last).magnitude() - meter)
            {
                points.push_back(curr);
            }
            else
            {
                points.push_back(last);
            }

            meter++;
        }

        distance += (curr - last).magnitude();
        last = curr;
    }

    return points;
}

std::vector<osj::vec2> Hill::GenerateInrunPoints() const
{
    std::vector<osj::vec2> points{T};

    // add points between E2 and E1 (inclusive)
    double delta = E1.x - E2.x;
    int segments = (int)(inrun.l);
    for (size_t i = 0; i <= segments; i++)
    {
        points.emplace_back(i * delta / segments + E2.x, Inrun(i * delta / segments + E2.x));
    }

    points.push_back(B);
    points.push_back(A);
    return points;
}

osj::vec2 Hill::GatePoint(int nr)
{
    return (A - B) * (nr - 1) / (m_gates - 1) + B;
}