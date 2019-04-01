#pragma once

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
     * @param[in] busName   - The Dbus name to own
     * @param[in] objPath   - The Dbus object path
     */
    Cable(sdbusplus::bus::bus& bus, const char* objPath) :
        CableInherit(bus, objPath, true), bus(bus), fp(NULL) {    
			if(Open() == -1) {
				std::cerr << "Open error!" <<std::endl;
		}
		
		SlotAddr(ssdaddr);

		emit_object_added();
    };
	
	Cable() {
	};

	~Close() {
		Close();
	};
	
	int Open();
	uint32_t GetCableData(const std::string cableName)
	vector<string> Split(const string& info,const string& pattern);
	void Close();
	
	uint32_t CableType() const override;
	uint32_t Present() const override;
	uint32_t LinkSpeed() const override;
	uint32_t LinkWidth() const override;
	uint32_t LinkActive() const override;
	uint32_t PartitionID() const override;
	uint32_t Invalid() const override;
	uint32_t UspDsp() const override;
	uint32_t Status() const override;
	

	
  private:
  
	FILE* fp;
	
    /** @brief Persistent sdbusplus DBus bus connection. **/
    sdbusplus::bus::bus& bus;
	

};

} // namespace manager
} // namespace Cable
} // namespace phosphor
