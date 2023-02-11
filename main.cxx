#include "PhysicalUnits.hh"

auto main() -> int
{
    auto fac1 = 3.0;
    auto fac2 = 9.0;
    auto fac3 = fac1 * fac2;
    auto value0 = 1.0_m;
    auto value1 = 3.0 * value0;
    auto value2 = value0 * 3.0;
    auto value3 = value1 * value1;
    std::cout << value2.GetValue() << std::endl;
    std::cout << value3.GetValue() << std::endl;
    return 0;
}
