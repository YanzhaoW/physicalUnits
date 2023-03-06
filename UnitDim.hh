#pragma once

#include "TypeCheck.hh"

enum class Scale
{
    tera = 12,
    giga = 9,
    mega = 6,
    kilo = 3,
    centi = -2,
    mi = -3,
    macro = -6,
    nano = -9,
    pico = -12,
};

template <int E, int L, int T>
struct NonScaleUnit
{
    template <int E2, int L2, int T2>
    auto operator*(NonScaleUnit<E2, L2, T2> /*unused*/)
    {
        return NonScaleUnit<E + E2, L + L2, T + T2>();
    }
    static constexpr int energy = E;
    static constexpr int length = L;
    static constexpr int time = T;
};
namespace dim
{
    static constexpr auto m = NonScaleUnit<0, 0, 1>();
    static constexpr auto m2 = NonScaleUnit<0, 0, 2>();
    static constexpr auto m3 = NonScaleUnit<0, 0, 3>();
} // namespace dim

template <Scale scale, int... dims>
class UnitDim
{
  public:
    UnitDim() = default;

    template <Scale otherScale, int otherPower>
    constexpr auto operator*(const UnitDim<otherScale, otherPower>& other)
    {
    }

    static constexpr NonScaleUnit<dims...> mDim;
};
