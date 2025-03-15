#include "pch.h"
#include "DvarInterface.hpp"
#include "Console.h"

std::unordered_map<std::string, std::string> DvarInterface::userToEngineMap;
std::unordered_map<std::string, std::string> DvarInterface::engineToUserMap;


void DvarInterface::addMapping(const std::string& userString, const std::string& engineString) {
    userToEngineMap[userString] = engineString;
    engineToUserMap[engineString] = userString;
}

std::string DvarInterface::toEngineString(const std::string& userString) {
    auto it = userToEngineMap.find(userString);
    if (it != userToEngineMap.end()) {
        return it->second;
    }
    return userString; //couldnt find
}

std::string DvarInterface::toUserString(const std::string& engineString) {
    auto it = engineToUserMap.find(engineString);
    if (it != engineToUserMap.end()) {
        return it->second;
    }
    return engineString; //couldnt find
}

bool DvarInterface::hasUserString(const std::string& userString) {
    return userToEngineMap.find(userString) != userToEngineMap.end();
}

bool DvarInterface::hasEngineString(const std::string& engineString) {
    return engineToUserMap.find(engineString) != engineToUserMap.end();
}

void DvarInterface::init() {
    Console::infoPrint("Initializing Dvar Interface");
    //only gonna put ones that are actually used
    addMapping("r_disable_clutter", "1841");
    addMapping("r_texFilterDisable", "91");
    addMapping("r_texFilterMipMode", "4107");
    addMapping("r_texShowMipMode", "2416");
    addMapping("r_texFilterMipBias", "3569");
    addMapping("r_texFilterProbeBilinear", "5634");
    addMapping("r_lodDynamicScale", "1111");
    addMapping("r_artUseTweaks", "5690");
    addMapping("r_lightGridTempSmoothingFactor", "2677");
    addMapping("r_globalSecondarySelfVisScale", "1264");
    addMapping("r_globalSecondarySelfVisLerpToFullyOpen", "5139");
    addMapping("r_lightMap", "3271");
    addMapping("r_colorMap", "3391");
    addMapping("r_detailMap", "2194");
}