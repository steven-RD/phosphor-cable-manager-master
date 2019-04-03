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

	
	uint32_t Cable::GetCableData(const std::string& cableName) const{

		char line[128] = {0};
		std::pair<std::string, uint32_t> oneCable;
		std::map<std::string, uint32_t> cableInfo;
		std::map<std::string, uint32_t>::iterator iter; 
		
		FILE* fp = popen("i2cusi -c cbinfo", "r");
		
		while(NULL != fgets(line, sizeof(line), fp)) {
			
			std::string lineStr = line;
			if(lineStr.substr(0, 3) == "CAB") {
				oneCable = Split(lineStr, ":");
				cableInfo.insert(oneCable);
			}
		}
		
		if((iter = cableInfo.find(cableName)) == cableInfo.end()) {
			std::cout << "not find" << cableName << std::endl;
			return 0;
		}
		
		if(fp != NULL)
			pclose(fp);
		
		return iter->second;
	}
	
	
	std::pair<std::string, uint32_t> Cable::Split(std::string& info, const std::string& pattern) const{		
	
		std::string name;
		uint32_t value = 0;
		std::pair<std::string, uint32_t> cableInfo;
		
		if(!info.empty()) {	
			char * strc = new char[strlen(info.c_str()) + 1];
			strcpy(strc, info.c_str());
			char* tmpStr = strtok(strc, pattern.c_str());	
			while(tmpStr != NULL) {
				string str = tmpStr;
				if(str.substr(0, 3) == "CAB"){
					name = tmpStr;
				} else {
					sscanf(tmpStr, "%x", &value); 
				}
				
				tmpStr = strtok(NULL, pattern.c_str());
			}
			
			cableInfo = make_pair(name, value);
			delete[] strc;
		}
		
		return cableInfo;
	}
	
	uint32_t Cable::cableType() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		const std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData =  GetCableData(cableName);
				
		return  (cableData & 0x07);
	}

	uint32_t Cable::present() const {

		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData = GetCableData(cableName);		
		
		return  ((cableData >> 7) & 0x01);
	}
	
	uint32_t Cable::linkStatus() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 8) & 0x07);
	}
	
	uint32_t Cable::linkWidth() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData =  GetCableData(cableName);		
		
		return  ((cableData >> 11) & 0x0f);
	}
	
	uint32_t Cable::linkActive() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData =  GetCableData(cableName);
		
		return  ((cableData >> 15) & 0x01);
	}

	uint32_t Cable::partitionID() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 16) & 0x0f);
	}
	
	uint32_t Cable::invalid() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 20) & 0x0f);
	}
	
	uint32_t Cable::uspDsp() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData = GetCableData(cableName);

		return  ((cableData >> 24) & 0x0f);
	}

	uint32_t Cable::status() const {

		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + std::to_string(slotNum);
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 28) & 0x0f);
	}


} // namespace manager
} // namespace cable
} // namespace phosphor
