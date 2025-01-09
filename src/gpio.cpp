#include "gpio.hpp"

#include <IfxCpu_Intrinsics.h>
#include <IfxPort_reg.h>


void Hal::Gpio::configure(const Pin& pin)
{
	auto* port_ptr = &MODULE_P00 + pin.port;

	const auto pdr_index = pin.number / 8U;
	const auto pdr_shift = pin.number % 8U;
	const auto iocr_index = pin.number / 4U;
	const auto iocr_shift = pin.number % 4;

	// write pad driver
	volatile auto* pdr_list = &port_ptr->PDR0.U;
	Ifx__ldmst(reinterpret_cast<volatile void*>(&(pdr_list[pdr_index])), (0xFUL << pdr_shift), (pin.speed << pdr_shift));

	// write pin mode
	volatile auto* iocr_list = &port_ptr->IOCR0.U;
	Ifx__ldmst(reinterpret_cast<volatile void*>(&(iocr_list[iocr_index])), (0xFFUL << iocr_shift), (pin.mode << iocr_shift));
}
