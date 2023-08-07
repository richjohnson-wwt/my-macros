#include "TokenJson.h"
#include <fstream>
#include <spdlog/spdlog.h>

using json = nlohmann::json;



namespace FatSecret {
    void from_json(const json& j, Token& t) {
                j.at("access_token").get_to(t.access_token);
                j.at("expires_in").get_to(t.expires_in);
                j.at("token_type").get_to(t.token_type);
                j.at("scope").get_to(t.scope);
            }

    std::string TokenJson::parseToken()
    {
        // open ../src/data/token.json and parse access_token from the json file
        std::ifstream ifs("../src/data/token.json");
        json j = json::parse(ifs);
        FatSecret::Token t = j;
        spdlog::debug("Token: {}", t.access_token);
        return t.access_token;
    }
} // namespace Macro