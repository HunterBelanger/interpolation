########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( interpolation LANGUAGES CXX )

########################################################################
# Dependencies
########################################################################

include( cmake/interpolation_dependencies.cmake )

########################################################################
# Project targets
########################################################################

add_library( interpolation INTERFACE )
target_include_directories( interpolation INTERFACE src/ )
target_link_libraries( interpolation
    INTERFACE range-v3-adapter
    INTERFACE Log
    INTERFACE header-utilities
    INTERFACE dimwits
    )
