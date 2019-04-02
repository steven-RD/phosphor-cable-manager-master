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
	
	Cable::~Cable() {
		Close();
	}
	
	int Cable::Open() {
		fp = popen("i2cusi -c cbinfo", "r");
		return  fp != NULL ? 0 : -1;
	}
	
	void Cable::Close(){
		if(fp != NULL)
			pclose(fp);
		fp = NULL;
	}
	
	uint32_t Cable::GetCableData(const std::string& cableName) {

		char* line = NULL;
		uint32_t len = 0;
		std::vector<std::string> value;
		std::map<std::string, std::string> cableInfo;
		std::map<std::string, std::string>::iterator iter; 
		
		//while(getline(fp, line)) {
		while(getline(&line, &len, fp) != -1) {
			
			std::string lineStr = line;
			if(lineStr.substr(0, 3) == "CAB") {
				value = Split(lineStr, ":");
				cableInfo.insert(make_pair(value.front(), value.back()));
			}
		}
		
		if(line != NULL) {
			free(line);	
			line = NULL;
		}
		

		if((iter = cableInfo.find(cableName)) == cableInfo.end()) {
			std::cerr << "CableInformation not exit!" << std::endl;
			return 0;
		} 
		
		uint32_t data = 0;
		stringstream ss;
		ss << iter->second;
		ss >> data;
		ss.clear();
		
		return data;
	}
	
	
	std::vector<std::string> Cable::Split(std::string& info, const std::string& pattern) {		
		std::vector<std::string> value;
		
		if(!info.empty()) {	
			char * strc = new char[strlen(info.c_str()) + 1];
			strcpy(strc, info.c_str());
			char* tmpStr = strtok(strc, pattern.c_str());			
			while(tmpStr != NULL) {
				value.push_back(std::string(tmpStr));
				tmpStr = strtok(NULL, pattern.c_str());
			}
			delete[] strc;
		}
		
		return value;
	}
	
	uint32_t Cable::cableType() {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData =  GetCableData(cableName);
		
		
		return  (cableData & 0x07);
	}

	uint32_t Cable::present() {

		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);		
		
		return  ((cableData >> 7) & 0x01);
	}
	
	uint32_t Cable::linkSpeed() {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 8) & 0x07);
	}
	
	uint32_t Cable::linkWidth() {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData =  GetCableData(cableName);		
		
		return  ((cableData >> 11) & 0x0f);
	}
	
	uint32_t Cable::linkActive() {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData =  GetCableData(cableName);
		
		return  ((cableData >> 15) & 0x01);
	}

	uint32_t Cable::partitionID() {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 16) & 0x0f);
	}
	
	uint32_t Cable::invalid() {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 20) & 0x0f);
	}
	
	uint32_t Cable::uspDsp()  {
		
		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);

		return  ((cableData >> 24) & 0x0f);
	}

	uint32_t Cable::status() {

		auto slotNum = sdbusplus::xyz::openbmc_project::Cable::server::Cable::slotAddr();
		std::string cableName = "CAB" + slotNum;
		uint32_t cableData = GetCableData(cableName);
		
		return  ((cableData >> 28) & 0x0f);
	}

} // namespace manager
} // namespace cable
} // namespace phosphor
