#include "CurlWrapper.h"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <sstream>
#include <iomanip>

const std::string CurlWrapper::TOKEN_FETCH_COMMAND = "curl -u 4d1523a468c5465682c5598ae88b3d65:d8ad072df8c44ed69b73f1ed0055a85b \
        -d \"grant_type=client_credentials&scope=basic\" \
        -X POST https://oauth.fatsecret.com/connect/token;";


/*
curl --location --request POST 'https://platform.fatsecret.com/rest/server.api?method=food.get.v3&format=json&food_id=1782781' \
*/
std::string CurlWrapper::assembleGetFoodCommand(const std::string &token, std::string &foodId)
{
    std::stringstream ss;
    ss << "curl -d --location --request POST 'https://platform.fatsecret.com/rest/server.api?method=food.get.v3&format=json&food_id=" 
        << foodId << "'"
        << " --header 'Content-Type: application/json' --header 'Authorization: Bearer " 
        << token << "'";

    return ss.str();
}

std::string CurlWrapper::assembleFoodSearchCommand(const std::string &token, std::string &foodQuery)
{
    urlEncode(foodQuery);
    
    // curl -d --location --request POST 'https://platform.fatsecret.com/rest/server.api?method=foods.search&format=json&search_expression=chicken%20breast' --header 'Content-Type: application/json' --header 'Authorization: Bearer '"$token"''
    std::stringstream ss;
    ss << "curl -d --location --request POST 'https://platform.fatsecret.com/rest/server.api?method=foods.search&format=json&search_expression=" 
        << foodQuery << "'"
        << " --header 'Content-Type: application/json' --header 'Authorization: Bearer " 
        << token << "'";

    return ss.str();
}

void CurlWrapper::urlEncode(std::string &str)
{
    // Trim the given string
    str.erase(str.find_last_not_of(" \n\r\t")+1);

    // Replace All space (unicode is \\s) to %20
    size_t pos = str.find(" ");
    while (pos != std::string::npos)
    {
    str.replace(pos, 1, "%20");
    pos = str.find(" ", pos + 3);
    }
}

std::string CurlWrapper::executeCurl(const std::string &command)
{
    char buffer[128];
    std::string result = "";

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

/* 
curl -d --location --request POST 'https://platform.fatsecret.com/rest/server.api?method=foods.search&format=json&search_expression=cauliflower' \
--header 'Content-Type: application/json' \
--header 'Authorization: Bearer eyJhbGciOiJSUzI1NiIsImtpZCI6IjVGQUQ4RTE5MjMwOURFRUJCNzBCMzU5M0E2MDU3OUFEMUM5NjgzNDkiLCJ0eXAiOiJhdCtqd3QiLCJ4NXQiOiJYNjJPR1NNSjN1dTNDeldUcGdWNXJSeVdnMGsifQ.eyJuYmYiOjE2OTAwNDc5NDAsImV4cCI6MTY5MDEzNDM0MCwiaXNzIjoiaHR0cHM6Ly9vYXV0aC5mYXRzZWNyZXQuY29tIiwiYXVkIjoiYmFzaWMiLCJjbGllbnRfaWQiOiI0ZDE1MjNhNDY4YzU0NjU2ODJjNTU5OGFlODhiM2Q2NSIsInNjb3BlIjpbImJhc2ljIl19.MTpPMFNEXMju5r6-Ovr5We9h_Em58uwSWqDD3DG0vmtlxYppV499nBg9vQ7qD0J9MRFTlAaXlM0mkIKBQ9fAG-JeGn_qRRyaTKMmONqOnY4OQugz2np3h99VftnvNZfg3VtrSBYzyzfuv-9YLnjygnfJ8bq3tUwGzkc3pxxolHnUOorLCsNkcO7QEiND-BoYvZAdQuxf9FCbMtLlcxTALQlzJbs9yYyfxQVz6HhoVLXTLxArmhX1IVVJ__B7w2fhRLPj5lMYdBODgEyq27ji-QA-d0CS3tC1JZyD92VKIuRTwlNoML9a5V06ejLMos3Z2AR-X9lmZ6sjY36sS9kWvg'

*/