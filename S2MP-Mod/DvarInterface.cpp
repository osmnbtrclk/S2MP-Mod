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
    addMapping("r_displacementMap", "4388");
    addMapping("r_normalMap", "5467");
    addMapping("r_specularMap", "2427");
    addMapping("r_specOccMap", "5620");
    addMapping("r_envBrdLutMap", "3818");
    addMapping("r_emissiveMap", "769");
    addMapping("r_depthPrepass", "4600");
    addMapping("r_depthHackPrepass", "1342");
    addMapping("r_volumetricDepth", "3395");
    addMapping("r_forceLod", "3361");
    addMapping("r_useAerialLod", "1841");
    addMapping("sm_spotEnable", "2030");
    addMapping("sm_spotLightScoreRadiusPower", "1475");
    addMapping("sm_dynlightAllSModels", "5657");
    addMapping("sm_sunShadowBoundsOverride", "1064");
    addMapping("sm_sunShadowBoundsMin", "2611");
    addMapping("sm_sunShadowBoundsMax", "419");
    addMapping("sm_spotShadowMapSize", "935");
    addMapping("sm_sunPolygonOffsetScale", "2428");
    addMapping("sm_sunPolygonOffsetBias", "5142");
    addMapping("sm_sunPolygonOffsetClamp", "3266");
    addMapping("sm_spotPolygonOffsetScale", "4087");
    addMapping("sm_spotPolygonOffsetBias", "3357");
    addMapping("sm_spotPolygonOffsetClamp", "136");
    addMapping("sm_sunShadowCenter", "450");
    addMapping("sm_sunShadowCenterMode", "775");
    addMapping("r_filmGrainUseTweaks", "4316");
    addMapping("r_filmGrainIntensity", "4276");
    addMapping("r_filmGrainFps", "3289");
    addMapping("r_postfx_enable", "5605");
    addMapping("r_sunPostDrawBeforeTrans", "849");
    addMapping("r_dof_enable", "2046");
    addMapping("r_dof_tweak", "2");
    addMapping("r_dof_nearBlur", "2208");
    addMapping("r_dof_farBlur", "1256");
    addMapping("r_dof_viewModelStart", "231");
    addMapping("r_dof_viewModelEnd", "5414");
    addMapping("r_dof_nearStart", "875");
    addMapping("r_dof_nearEnd", "2580");
    addMapping("r_dof_farStart", "756");
    addMapping("r_dof_farEnd", "4058");
    addMapping("r_dof_bias", "97");
    addMapping("r_dof_physical_filmDiagonal", "4419");
    addMapping("r_dof_physical_hipEnable", "1972");
    addMapping("r_dof_physical_hipFstop", "2186");
    addMapping("r_dof_physical_hipSharpCocDiameter", "275");//ayo?
    addMapping("r_dof_physicalHipFocusSpeed", "5398");
    addMapping("r_dof_physical_fstop", "3380");
    addMapping("r_dof_physical_focusDistance", "1920");
    addMapping("r_dof_physical_viewModelFstop", "1077");
    addMapping("r_dof_physical_viewModelFocusDistance", "1052");
    addMapping("r_dof_physical_adsFocusSpeed", "4854");
    addMapping("r_dof_physical_adsMinFstop", "4242");
    addMapping("r_dof_physical_adsMaxFstop", "1315");
    addMapping("r_dof_physical_minFocusDistance", "2386");
    addMapping("r_dof_physical_maxCocDiameter", "2888");//AYO
    addMapping("r_colorGradingEnable", "523");
    addMapping("r_colorimetrySDRForcePQ", "5246");
    addMapping("r_colorimetryHDRForcePQ", "5322");
    addMapping("r_colorimetryHDRDisableBlackLevelAdjust", "4268");
    addMapping("r_colorimetryHDRExposureAdjust", "2268");
    addMapping("r_outdoorFeather", "161");
    addMapping("r_sun_from_dvars", "2255");
    addMapping("r_atlasAnimFPS", "1289");
    addMapping("developer", "1147");
    addMapping("r_tessellationHeightAuto", "75");
    addMapping("r_tessellationHeightScale", "672");
    addMapping("r_tessellationHybrid", "551");
    addMapping("r_tessellationEyeScale", "330");
    addMapping("r_offchipTessellationAllowed", "1938");
    addMapping("r_offchipTessellationTfThreshold", "635");
    addMapping("r_offchipTessellationWaveThreshold", "4679");
    addMapping("r_patchCountAllowed", "3925");
    addMapping("r_subdivPatchCount", "4902");
    addMapping("r_displacementPatchCount", "3287");
    addMapping("r_defaultPatchCount", "3923");
}