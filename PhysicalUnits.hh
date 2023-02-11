#pragma once

#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
using remove_all_qualifiers = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename NumType,
          int energyDim,
          int lengthDim,
          int timeDim,
          typename = typename std::is_arithmetic<NumType>::type>
class PhysicalValueImp
{
  public:
    template <int... Dim, typename Type>
    friend auto PhysicalValue(Type value) -> decltype(auto);

    template <typename RType, typename = typename std::is_arithmetic<RType>::type>
    auto operator*(RType value) -> decltype(auto)
    {
        return PhysicalValueImp<NumType, energyDim, lengthDim, timeDim>(value * mData);
    }

    [[nodiscard]] auto GetValue() const -> NumType { return mData; }

  private:
    explicit PhysicalValueImp(NumType value)
        : mData{ value }
    {
    }
    NumType mData;
};

template <int... Dim, typename Type>
auto PhysicalValue(Type value) -> decltype(auto)
{
    return PhysicalValueImp<Type, Dim...>(value);
}

template <typename>
struct is_PhysicalType : std::false_type
{
};

template <typename NumType, int energyDim, int lengthDim, int timeDim>
struct is_PhysicalType<PhysicalValueImp<NumType, energyDim, lengthDim, timeDim>> : std::true_type
{
};

template <typename... Args>
using has_PhysicalType = typename std::enable_if_t<(is_PhysicalType<remove_all_qualifiers<Args>>::value || ...)>;

template <typename LeftType, typename RightType, typename = void>
struct Multiply
{
    Multiply(LeftType&& left, RightType&& right)
        : result{ left * right.GetValue() }
    {
    }
    remove_all_qualifiers<RightType> result{};
};

template <typename LeftType, typename RightType>
struct Multiply<LeftType,
                RightType,
                std::void_t<typename std::enable_if_t<std::is_arithmetic<remove_all_qualifiers<LeftType>>::value>>>
    : std::true_type
{
    Multiply(LeftType&& left, RightType&& right)
        : result{ right * left }
    {
        std::cout << "specail: " << std::endl;
    }
    remove_all_qualifiers<RightType> result;
};

template <typename Arg1, typename Arg2, typename = has_PhysicalType<Arg1, Arg2>>
auto operator*(Arg1&& left, Arg2&& right) -> decltype(auto)
{
    return Multiply<Arg1, Arg2>(std::forward<Arg1>(left), std::forward<Arg2>(right)).result;
}

inline auto operator""_m(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value)); }
inline auto operator""_km(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value * 1e3)); }
inline auto operator""_cm(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value * 1e-2)); }
inline auto operator""_mm(long double value) { return PhysicalValue<0, 1, 0>(static_cast<double>(value * 1e-3)); }

inline auto operator""_ns(long double value) { return PhysicalValue<0, 0, 1>(static_cast<double>(value)); }
inline auto operator""_ps(long double value) { return PhysicalValue<0, 0, 1>(static_cast<double>(value * 1e-3)); }

inline auto operator""_MeV(long double value) { return PhysicalValue<1, 0, 0>(static_cast<double>(value)); }
inline auto operator""_keV(long double value) { return PhysicalValue<1, 0, 0>(static_cast<double>(value * 1e-3)); }
inline auto operator""_GeV(long double value) { return PhysicalValue<1, 0, 0>(static_cast<double>(value * 1e3)); }
