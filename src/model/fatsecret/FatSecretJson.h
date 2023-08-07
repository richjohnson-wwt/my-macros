#ifndef FAT_SECRET_JSON_H
#define FAT_SECRET_JSON_H

#include "../MyMacroTypes.h"
#include <nlohmann/json.hpp>
#include <vector>

namespace FatSecret
{
    using json = nlohmann::json;
    using std::string;
    using std::vector;

    // BEGIN SEARCH JSON
    struct SearchFood
    {
        string food_description;
        string food_id;
        string food_name;
        string food_type;
        string food_url;
    };

    struct SearchFoods
    {
        vector<SearchFood> food;
        string max_results;
        string page_number;
        string total_results;
    };

    void to_json(json &j, const Food &food);
    void from_json(const json &j, Food &food);

    void to_json(json &j, const SearchFoods &foods);
    void from_json(const json &j, SearchFoods &foods);

    // END SEARCH JSON

    // BEGIN GET JSON
    struct Serving
    {
        string calories;
        string carbohydrate;
        string fat;
        string protein;
        string metric_serving_unit;
        string metric_serving_amount;
        string fiber;
        string serving_description;
    };

    struct Servings
    {
        vector<Serving> serving;
    };

    struct GetFood
    {
        Servings servings;
        string food_id;
        string food_name;
        string brand_name;
    };

    void to_json(json &j, const Serving &serving);
    void from_json(const json &j, Serving &serving);

    void to_json(json &j, const Servings &servings);
    void from_json(const json &j, Servings &servings);

    void to_json(json &j, const GetFood &food);
    void from_json(const json &j, GetFood &food);

    // END GET JSON

    class FatSecretJson {
    private:
        SearchFoods m_searchFoodsResponse;
        GetFood m_getFoodResponse;

    public:
        SearchFoods handleSearchResponse(const string &response);
        SearchFood retrieveFoodById(std::string foodId);

        GetFood handleGetResponse(const string &response);
        GetFood retrieveGetFood(int servingIndex);
        
    };
}


#endif // FAT_SECRET_JSON_H