cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(polynomial)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(./function.cmake)

add_subdirectory(include)
add_subdirectory(samples)

option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(test)
    if (NOT googletest) # is googletest defined if already built?
	    include(FetchContent)
	    FetchContent_Declare(
		googletest
		# Specify the commit you depend on and update it regularly.
		URL https://github.com/google/googletest/archive/refs/heads/master.zip
	    )
	    # For Windows: Prevent overriding the parent project's compiler/linker settings
	    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	    FetchContent_MakeAvailable(googletest)
    endif()
endif()