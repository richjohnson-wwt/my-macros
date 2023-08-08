#ifndef DB_GOAL_H
#define DB_GOAL_H

#include "DbBase.h"
#include "../MyMacroTypes.h"
#include <string>

class DbGoal : public DbBase
{
public:
    DbGoal(const std::string& dbfile);

    Goal getGoal();
};


#endif // DB_GOAL_H