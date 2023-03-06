#pragma once
#include <type_traits>
#include <utility>

template <typename NumType,
          int energyDim,
          int lengthDim,
          int timeDim,
          typename = typename std::is_arithmetic<NumType>::type>
class PhysicalValueImp;

template <typename T>
using remove_all_qualifiers = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename T1, typename T2, typename = void>
struct is_Multiplicable : std::false_type
{
};

template <typename T1, typename T2>
struct is_Multiplicable<T1, T2, std::void_t<decltype(std::declval<T1&>() * std::declval<T2&>())>> : std::true_type
{
};

template <typename T1, typename T2>
inline constexpr bool is_Multiplicable_v = is_Multiplicable<T1, T2>::value;

template <typename>
struct is_PhysicalType : std::false_type
{
};

template <typename NumType, int energyDim, int lengthDim, int timeDim>
struct is_PhysicalType<PhysicalValueImp<NumType, energyDim, lengthDim, timeDim>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_PhysicalType_v = is_PhysicalType<T>::value;

template <typename... Args>
using has_PhysicalType = typename std::enable_if_t<(is_PhysicalType<remove_all_qualifiers<Args>>::value || ...)>;

template <bool value, typename T1, typename T2>
constexpr auto StaticIf(T1&& first, T2&& second) -> decltype(auto)
{
    if constexpr (value)
    {
        return std::forward<T1>(first);
    }
    else
    {
        return std::forward<T2>(second);
    }
}

template <int n, typename = void>
static constexpr double Power10 = Power10<n + 1> / 10;

template <int n>
static constexpr double Power10<n, std::void_t<typename std::enable_if_t<(n > 0)>>> = 10 * Power10<n - 1>;

template <>
static constexpr double Power10<0, void> = 1.0;
