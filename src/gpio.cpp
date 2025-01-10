#include "gpio.hpp"

#include <IfxPort_reg.h>

namespace
{

inline void ldmst(volatile auto* address, u32 mask, u32 value)
{
    __asm__ volatile("mov %H2,%1 \n    ldmst [%0]0,%A2" ::"a"(address), "d"(mask), "d"((long long)value));
}

} // anonymous namespace

void Hal::Gpio::configure(const Pin& pin)
{
    auto* port_ptr = &MODULE_P00 + pin.port;

    const auto pdr_index  = pin.number / 8U;
    const auto pdr_shift  = (pin.number % 8U) * 4U;
    const auto iocr_index = pin.number / 4U;
    const auto iocr_shift = (pin.number % 4) * 8U;

    // write pad driver
    volatile auto* pdr_list = &port_ptr->PDR0.U;
    ldmst(reinterpret_cast<volatile void*>(&(pdr_list[pdr_index])), (0xFUL << pdr_shift), (pin.speed << pdr_shift));

    // write pin mode
    volatile auto* iocr_list = &port_ptr->IOCR0.U;
    ldmst(reinterpret_cast<volatile void*>(&(iocr_list[iocr_index])), (0xFFUL << iocr_shift), (pin.mode << iocr_shift));
}
