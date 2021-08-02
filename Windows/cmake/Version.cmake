# Get version from include/RealSenseID/Version.h and put it in RSID_VERSION
function(rsid_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/RealSenseID/Version.h" file_contents)
    string(REGEX MATCH "RSID_VER_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from Version.h")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "RSID_VER_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from Version.h")
    endif()

    set(ver_minor ${CMAKE_MATCH_1})
    string(REGEX MATCH "RSID_VER_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from Version.h")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(RSID_VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(RSID_VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(RSID_VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(RSID_VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()
