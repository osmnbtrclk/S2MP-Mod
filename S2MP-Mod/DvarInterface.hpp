#pragma once
#include <unordered_map>
#include <string>

class DvarInterface {
private:
    static std::unordered_map<std::string, std::string> userToEngineMap;
    static std::unordered_map<std::string, std::string> engineToUserMap;

public:
    static void init();
    static void addMapping(const std::string& userString, const std::string& engineString);

    static std::string toEngineString(const std::string& userString);
    static std::string toUserString(const std::string& engineString);

    static bool hasUserString(const std::string& userString);
    static bool hasEngineString(const std::string& engineString);
};