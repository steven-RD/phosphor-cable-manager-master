
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <functional>
#include <sdbusplus/bus.hpp>
#include <xyz/openbmc_project/Cable/Cable/server.hpp>
		
namespace phosphor
{
namespace cable
{
namespace manager
{

using CableInherit = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Cable::server::Cable>;
	
using namespace std;

/** @class Cable
 *  @brief OpenBMC Cable state management implementation.
 *  @details A concrete implementation for xyz.openbmc_project.State.Cable
 *  DBus API.
 */
class Cable : public CableInherit
{
  public:
    /** @brief Constructs Cable State Manager
     *
     * @param[in] bus       - The Dbus bus object
     * @param[in] objPath   - The Dbus object path
     * @param[in] cableNum  - The cable number
     */ 
	Cable() = delete;
	Cable(const Cable&) = delete;
	Cable& operator=(const Cable&) = delete;
	Cable(Cable&&) = delete;
	Cable& operator=(Cable&&) = delete;
	~Cable(){		
	}	
    Cable(sdbusplus::bus::bus& bus, const char* objPath, const uint32_t cableNum) :
        CableInherit(bus, objPath, true) { 
		
		slotAddr(cableNum);
		emit_object_added();
    };
		
	std::string cableType() const override;
	std::string present()  const override;
	std::string linkStatus() const override;
	std::string linkWidth() const override;
	std::string linkActive() const override;
	uint32_t partitionID() const override;
	std::string invalid() const override;
	std::string uspDsp() const override;
	std::string status() const override;
	

  private:
  
    /** @brief Persistent sdbusplus DBus bus connection. **/
    //sdbusplus::bus::bus& bus;

};

class CableValue {

public:

	uint32_t GetCableData(const std::string& cableName) const;
	std::pair<std::string, uint32_t> Split(string& info, const string& pattern) const;
	
};

} // namespace manager
} // namespace Cable
} // namespace phosphor



