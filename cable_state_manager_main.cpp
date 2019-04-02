#include <sdbusplus/bus.hpp>
#include "config.h"
#include "cable_state_manager.hpp"

int main(int argc, char**)
{
    auto bus = sdbusplus::bus::new_default();

	std::string objPathInst = std::string(CABLE_OBJPATH);
	
	sdbusplus::server::manager::manager objManager(bus, objPathInst.c_str());// Add sdbusplus ObjectManager.
	std::vector<std::unique_ptr<phosphor::cable::manager::Cable>> cables;
	int cableNum = 0;
	
    for(int i = 0; i < 12; ++i) {
		++cableNum;
		std::string objPath = objPathInst + std::to_string(cableNum);		
		cables.emplace_back(std::make_unique<phosphor::cable::manager::Cable>(bus, objPath.c_str(), cableNum));
	}

    bus.request_name(CABLE_BUSNAME);

    while (true)
    {
        bus.process_discard();
        bus.wait();
    }

    exit(EXIT_SUCCESS);
}
