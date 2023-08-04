#ifndef CURLWRAPPER_H
#define CURLWRAPPER_H

#include <string>

class CurlWrapper {
public:  

    static const std::string TOKEN_FETCH_COMMAND;

    std::string executeCurl(const std::string &command);
    std::string assembleFoodSearchCommand(const std::string &token, std::string &foodQuery);
    std::string assembleGetFoodCommand(const std::string &token, std::string &foodIdQuery);

private:
    void urlEncode(std::string &str);
};

#endif // CURLWRAPPER_H