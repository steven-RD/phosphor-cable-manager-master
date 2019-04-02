
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
	~Cable();	
    Cable(sdbusplus::bus::bus& bus, const char* objPath, const uint32_t cableNum) :
        CableInherit(bus, objPath, true), fp(NULL) { 
		
		if(Open() == -1) {
			std::cerr << "Open error!" << std::endl;
		}
		
		slotAddr(cableNum);
		emit_object_added();
    };
	
	
	
	int Open();
	uint32_t GetCableData(const std::string& cableName);
	vector<string> Split(string& info, const string& pattern);
	void Close();
	
	uint32_t cableType() ;
	uint32_t present() ;
	uint32_t linkSpeed() ;
	uint32_t linkWidth() ;
	uint32_t linkActive() ;
	uint32_t partitionID() ;
	uint32_t invalid() ;
	uint32_t uspDsp() ;
	uint32_t status() ;
	

  private:
  
	FILE* fp;
	
    /** @brief Persistent sdbusplus DBus bus connection. **/
    //sdbusplus::bus::bus& bus;
	

};

} // namespace manager
} // namespace Cable
} // namespace phosphor
