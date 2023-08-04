#ifndef TOKENJSON_H
#define TOKENJSON_H

#include <nlohmann/json.hpp>

namespace FatSecret {
    using json = nlohmann::json;
    using std::string;

    struct Token {
        string access_token;
        int expires_in;
        string token_type;
        string scope;
    };

    void from_json(const json& j, Token& t);

    class TokenJson {
    public:
        string parseToken();
        
    };
}



#endif // TOKENJSON_H