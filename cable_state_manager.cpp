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
	
	std::string Cable::cableType() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData =  GetCableData(cableName);
		
		std::string cabType;
		uint32_t result = (cableData & 0x07);
		if(result == 2) {
			cabType = "defalut";
		} else {
			cabType = "reserved";
		}
		return (cabType);
	}
	
	std::string Cable::present() const {

		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);		
		
		std::string cabPresent;
		uint32_t result = ((cableData >> 7) & 0x01);
		if(result == 0) {
			cabPresent = "absent";
		} else {
			cabPresent = "present";
		}
		
		return (cabPresent);
	}
	
	std::string Cable::linkStatus() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		std::string linkSt;
		uint32_t result = ((cableData >> 8) & 0x07);
		
		switch(result) {
			case 0:
				linkSt = "link ok";
				break;
			case 1:
				linkSt = "absent";
				break;
			case 2:
				linkSt = "link fail";
				break;
			case 3:
				linkSt = "not link";
				break;
			case 4:
				linkSt = "status value invalid";
				break;
			default:
				break;
		}
		
		return (linkSt);
	}
	
	std::string Cable::linkWidth() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData =  GetCableData(cableName);		
		
		std::string linkWd;
		uint32_t result = ((cableData >> 11) & 0x0f);
		
		switch(result) {
			case 0:
				linkWd = "not link";
				break;
			case 1:
				linkWd = "x1.";
				break;
			case 2:
				linkWd = "x2.";
				break;
			case 3:
				linkWd = "x4.";
				break;
			case 4:
				linkWd = "x8.";
				break;
			case 5:
				linkWd = "x12.";
				break;
			case 6:
				linkWd = "x16.";
				break;
			case 7:
				linkWd = "x32.";
				break;
			case 8:
				linkWd = "Unknow.";
				break;
			default:
				break;
		}
		
		return (linkWd);
	}
	
	std::string Cable::linkActive() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData =  GetCableData(cableName);
		
		std::string linkAct;
		uint32_t result = ((cableData >> 15) & 0x01);
		if(result == 1) {
			linkAct = "active";
		} else {
			linkAct = "not active";
		}
		
		return (linkAct);
	}

	uint32_t Cable::partitionID() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 16) & 0x0f);
	}
	
	std::string Cable::invalid() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		std::string valid;
		uint32_t result = ((cableData >> 20) & 0x0f);
		if(result == 0) {
			valid = "physical port is valid in partition.";
		} else {
			valid = "physical port is invalid in partition.";
		}
		return (valid);
	}
	
	std::string Cable::uspDsp() const {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);

		std::string uspOrDsp;
		uint32_t result = ((cableData >> 24) & 0x0f);
		if(result == 1) {
			uspOrDsp = "upstream port";
		} else if (result == 2) {
			uspOrDsp = "downstream port";
		} else {
			uspOrDsp = "fail or abnormal";
		}
		
		return (uspOrDsp);
	}

	std::string Cable::status() const {

		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		std::string state;
		uint32_t result = ((cableData >> 28) & 0x0f);
		if(result == 0) {
			state = "valid cable.";
		} else {
			state = "invalid cable.";
		}
		
		return (state);
	}

} // namespace manager
} // namespace cable
} // namespace phosphor

