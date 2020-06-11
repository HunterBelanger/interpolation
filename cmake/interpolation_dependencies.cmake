include( FetchContent )


########################################################################
# Forward declarations
########################################################################


########################################################################
# Declare project dependencies
########################################################################

FetchContent_Declare( range-v3-adapter
    GIT_REPOSITORY  http://github.com/njoy/range-v3-adapter
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( Log
    GIT_REPOSITORY  http://github.com/njoy/Log
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  http://github.com/njoy/header-utilities
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( dimwits
    GIT_REPOSITORY  http://github.com/njoy/DimensionalAnalysis
    GIT_TAG         origin/build/fetchcontent
    )


########################################################################
# Load dependencies
########################################################################

FetchContent_MakeAvailable(
    range-v3-adapter
    Log
    header-utilities
    dimwits
    )
