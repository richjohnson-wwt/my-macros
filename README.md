# My Macros MVP (Model View Presenter)

This is an app that builds recipes and calculates the macros per serving.


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