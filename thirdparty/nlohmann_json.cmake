set(NLOHMANN_PREFIX nlohmann-json-d2dd27d)
set(NLOHMANN_URL https://github.com/nlohmann/json/archive/v3.1.2.tar.gz)
set(NLOHMANN_URL_MD5 557651b017c36ad596ba3b577ba1b539)


ExternalProject_Add(${NLOHMANN_PREFIX}
    PREFIX ${NLOHMANN_PREFIX}
    URL ${NLOHMANN_URL}
    URL_MD5 ${NLOHMANN_URL_MD5}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    BUILD_IN_SOURCE 0
    INSTALL_COMMAND mkdir -p ../../../deps/include/nlohmann && cp ../${NLOHMANN_PREFIX}/single_include/nlohmann/json.hpp ../../../deps/include/nlohmann
    LOG_DOWNLOAD 1
    LOG_BUILD 1
)
