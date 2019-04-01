#include <cassert>
#include <phosphor-logging/log.hpp>
#include <sdbusplus/exception.hpp>
#include <sys/sysinfo.h>
#include "cable_state_manager.hpp"

namespace phosphor
{
namespace cable
{
namespace manager
{

// When you see server:: you know we're referencing our base class
namespace server = sdbusplus::xyz::openbmc_project::Cable::server;

	int Cable::Open() {
		fp = popen("i2cusi -c cbinfo", "r");
		return  fp != NULL ? 0 : -1;
	}
	
	void Cable::Close(){
		if(fp != NULL)
			pclose(fp);
		fp = NULL;
	}
	
	uint32_t Cable::GetCableData(const std::string cableName) {

		std::string line;
		std::vector<std::string> value;
		std::map<std::string, uint32_t> cableInfo;
		std::map<std::string, uint32_t>::iterator iter; 
		
		while(getline(fp, line)) {
			
			if(line.substr(0, 3) == "CAB") {
				value = Split(line, ":");
				cableInfo.insert(make_pair(value.front(), value.back()));
			}		
		}
		
		if((iter = cableInfo.find(cableName)) == cableInfo.end()) {
			std::cerr << "CableInformation not exit!" << std::endl;
			return -1;
		} 
		
		return iter->second;
	}
	
	
	std::vector<std::string> Cable::Split(const std::string& info,const std::string& pattern) {		
		std::vector<std::string> value;
		
		if(!info.empty()) {		
			char* tmpStr = strtok(info.c_str(), pattern.c_str());			
			while(tmpStr != NULL) {
				value.push_back(std::string(tmpStr));
				tmpStr = strtok(NULL, pattern.c_str());
			}			
		}
		
		return value;
	}
	
	uint32_t Cable::CableType() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);
		if(cableData == -1) {
			std::cerr << "GetCableData error!" <<std::endl;
			return -1;
		}
		
		return  (cableData & 0x07);
	}

	uint32_t Present() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);		
		
		return  ((cableData >> 7) & 0x01);
	}
	
	uint32_t LinkSpeed() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);
		
		return  ((cableData >> 8) & 0x07);
	}
	
	uint32_t LinkWidth() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);		
		
		return  ((cableData >> 11) & 0x0f);
	}
	
	uint32_t LinkActive() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);
		
		return  ((cableData >> 15) & 0x01);
	}

	uint32_t PartitionID() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);
		
		return  ((cableData >> 16) & 0x0f);
	}
	
	uint32_t Invalid() const  {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);
		
		return  ((cableData >> 20) & 0x0f);
	}
	
	uint32_t UspDsp() const  {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);

		return  ((cableData >> 24) & 0x0f);
	}

	uint32_t Status() const {
		
		Cable cable;
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::SlotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = cable.GetCableData(cableName);
		
		return  ((cableData >> 28) & 0x0f);
	}

} // namespace manager
} // namespace cable
} // namespace phosphor
