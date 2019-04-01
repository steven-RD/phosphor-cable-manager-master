#include <sdbusplus/bus.hpp>
#include "config.h"
#include "cable_state_manager.hpp"

int main(int argc, char**)
{
    auto bus = sdbusplus::bus::new_default();

	auto objPathInst = std::string(CABLE_OBJPATH);
	
	sdbusplus::server::manager::manager objManager(bus, objPathInst.c_str());// Add sdbusplus ObjectManager.
	std::vector<std::unique_ptr<phosphor::cable::manager::Cable>> cables;
	
    for(int i = 1; i <= 12; i++) {
		auto objPathInst += std::string(i);
		cables.emplace_back(std::make_unique<phosphor::cable::manager::Cable>(bus, objPathInst.c_str()));
	}

    bus.request_name(CABLE_BUSNAME);

    while (true)
    {
        bus.process_discard();
        bus.wait();
    }

    exit(EXIT_SUCCESS);
}
