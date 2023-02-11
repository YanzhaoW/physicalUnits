#pragma once
#include "PhysicalValue.hh"

inline auto operator""_m(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value)); }
inline auto operator""_km(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value * 1e3)); }
inline auto operator""_cm(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value * 1e-2)); }
inline auto operator""_mm(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value * 1e-3)); }

inline auto operator""_ns(long double value) { return PhysicalValue<0, 0, 1>(static_cast<double>(value)); }
inline auto operator""_ps(long double value) { return PhysicalValue<0, 0, 1>(static_cast<double>(value * 1e-3)); }

inline auto operator""_MeV(long double value) { return PhysicalValue<1, 0, 0>(static_cast<double>(value)); }
inline auto operator""_keV(long double value) { return PhysicalValue<1, 0, 0>(static_cast<double>(value * 1e-3)); }
inline auto operator""_GeV(long double value) { return PhysicalValue<1, 0, 0>(static_cast<double>(value * 1e3)); }
