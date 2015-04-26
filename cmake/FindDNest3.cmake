find_path (DNEST3_INCLUDES
    NAMES "MTSampler.h"
    PATH_SUFFIXES "/include" "include/dnest3"
    HINTS ${DNEST3_ROOT_DIR}
)

find_library (DNEST3_LIBRARY
    NAMES dnest3
    PATH_SUFFIXES "/lib"
    HINTS ${DNEST3_ROOT_DIR}
)

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (DNest3
    DEFAULT_MESG
    DNEST3_INCLUDES
    DNEST3_LIBRARY
)
