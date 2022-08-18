cmake_minimum_required(VERSION 3.12)

project(PhotoBatch)

add_executable( PhotoBatch 
                "PhotoBatch.cpp" 
                "ArgumentParser.h"
                "ArgumentParser.cpp"
                "Utils.h"
                "Utils.cpp"
                "Mode.h"
                "Mode.cpp"
                "RenameMode.h"
                "RenameMode.cpp"
                "ConvertMode.h"
                "ConvertMode.cpp"
                "ResizeMode.h"
                "ResizeMode.cpp"
                "ScaleMode.h"
                "ScaleMode.cpp"
                "Args.h"
                "ModesFactory.h"
                "ModesFactory.cpp"
                "STB.cpp"


)

function( set_required_build_settings_for_GCC8 )
    # Always link with libstdc++fs.a when using GCC 8.
    # Note: This command makes sure that this option comes pretty late on the cmdline.
    link_libraries( "$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:-lstdc++fs>" )
endfunction()

set_target_properties(PhotoBatch PROPERTIES CXX_STANDARD 17)

set(FETCHCONTENT_QUIET OFF CACHE BOOL "Desabilita o modo quiet to FetchContent" FORCE)

include(FetchContent)

add_subdirectory(Tests/UnitTests)

add_subdirectory(External)

target_link_libraries(PhotoBatch PRIVATE stb)