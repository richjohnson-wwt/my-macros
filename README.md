# My Macros MVP (Model View Presenter)

This is an app that builds recipes and calculates the macros per serving.

Dependencies
------------

* [Conan](https://conan.io/)
* [wxWidgets]([www.](https://docs.wxwidgets.org/3.0/index.html)) (installed locally)
* [SQLite](https://www.sqlite.org/index.html) (Mac comes with it)
* [CMake](https://cmake.org/)
  

Build Notes
-------------

    virtualenv venv
    source venv/bin/activate
    pip install -r requirements.txt
    conan install . --output-folder=build --build=missing
    cd build
    . ./conanbuild.sh 
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
    cmake --build .
    . ./deactivate_conanbuild.sh

DB
----

    sqlite3 recipe.sqlite3 < recipe.sql
    sqlite3 macro.sqlite3 < macro.sql

Stories
-----

    * X Explorer - Add popularity to Food list
    * X Explorer - Food/Recipe Search (filter)
    * X Recipe - Add Build Recipe
    * X Food - Add Unit ComboBox
    * X Food - FoodItem Add Food manually
    * Food - Update Food manually
    * Recipe - Update Recipe
    * X Food - Delete
    * X Recipe - Delete
    * X Daily - Auto-create Today Date DailyFood in Db
    * Daily - Add Daily Food
    * Macro - 3rd panel macro breakdown
    * Food - StaticText for FoodItem. Use FoodItemEdit and FoodItemView panels
    * Recipe - StaticText for RecipeItem