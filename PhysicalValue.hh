#pragma once

#include "TypeCheck.hh"
#include <iostream>

template <int... Dim, typename Type, typename = std::enable_if_t<(sizeof...(Dim) > 0)>>
constexpr auto PhysicalValue(Type value) -> decltype(auto)
{
    using base_type = remove_all_qualifiers<Type>;
    return PhysicalValueImp<base_type, Dim...>(value);
}

template <typename Type>
constexpr auto PhysicalValue(Type&& value) -> decltype(auto)
{
    return PhysicalValue<0, 0, 0>(std::forward<Type>(value));
}

template <typename NumType, int energyDim, int lengthDim, int timeDim, typename>
class PhysicalValueImp
{
  public:
    template <int... Dim, typename Type, typename>
    constexpr friend auto PhysicalValue(Type) -> decltype(auto);

    template <typename ValueType, typename = decltype(std::declval<NumType&>() *= std::declval<ValueType&>())>
    constexpr auto operator*=(const ValueType& val) -> decltype(auto)
    {
        mData *= val;
        return *this;
    }

    template <typename ValueType, typename = std::enable_if_t<!is_PhysicalType_v<ValueType>>>
    constexpr auto operator*(const ValueType& val)
    {
        // return PhysicalValue<energyDim, lengthDim, timeDim>(mData *= val);
        return (*this) *= val;
    }

    template <typename ValueType, typename = decltype(std::declval<NumType&>() += std::declval<ValueType&>())>
    constexpr auto operator+=(const ValueType& val) -> decltype(auto)
    {
        mData += val;
        return *this;
    }

    template <typename ValueType, typename = std::enable_if_t<!is_PhysicalType_v<ValueType>>>
    constexpr auto operator+(const ValueType& val)
    {
        return (*this) += val;
    }

    template <typename ValueType, typename = decltype(std::declval<NumType&>() /= std::declval<ValueType&>())>
    constexpr auto operator/=(const ValueType& val) -> decltype(auto)
    {
        mData /= val;
        return *this;
    }

    template <typename ValueType, typename = std::enable_if_t<!is_PhysicalType_v<ValueType>>>
    constexpr auto operator/(ValueType val)
    {
        return (*this) /= val;
    }

    template <typename ValueType, typename = decltype(std::declval<NumType&>() -= std::declval<ValueType&>())>
    constexpr auto operator-=(const ValueType& val) -> decltype(auto)
    {
        mData -= val;
        return *this;
    }

    template <typename ValueType, typename = std::enable_if_t<!is_PhysicalType_v<ValueType>>>
    constexpr auto operator-(ValueType val)
    {
        return (*this) -= val;
    }

    // template <typename TypeOther, int eD, int lD, int tD>
    // auto operator*(const PhysicalValueImp<TypeOther, eD, lD, tD>& other) const -> decltype(auto)
    // {
    //     static_assert(is_Multiplicable<NumType, TypeOther>::value, "PhysicalValue: values cannot be multiplied.");
    //     return PhysicalValue<energyDim + eD, lengthDim + lD, timeDim + tD>(other.GetValue() * mData);
    // }

    [[nodiscard]] auto GetValue() const -> NumType { return mData; }

    auto Print()
    {
        std::cout << "Value: " << mData << " Dim: " << energyDim << ", " << lengthDim << ", " << timeDim << std::endl;
    }

  private:
    explicit PhysicalValueImp(NumType value)
        : mData{ value }
    {
    }
    NumType mData;
};

// template <typename Arg1, typename Arg2, typename = has_PhysicalType<Arg1, Arg2>>
// auto operator*(const Arg1& left, const Arg2& right) -> decltype(auto)
// {
//     if constexpr (is_PhysicalType<Arg1>::value)
//     {
//         return left * PhysicalValue(right);
//     }
//     else
//     {
//         return right * PhysicalValue(left);
//     }
// }
