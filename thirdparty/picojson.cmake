set(PICOJSON_PREFIX kazuho-picojson-25fc213)
set(PICOJSON_URL https://api.github.com/repos/kazuho/picojson/tarball/v1.3.0)
set(PICOJSON_URL_MD5 b809f659a9036f93a8ca938dc386b47f)


ExternalProject_Add(${PICOJSON_PREFIX}
    PREFIX ${PICOJSON_PREFIX}
    URL ${PICOJSON_URL}
    URL_MD5 ${PICOJSON_URL_MD5}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    BUILD_IN_SOURCE 0
    INSTALL_COMMAND mkdir ../../../deps/include/picojson && cp ../kazuho-picojson-25fc213/picojson.h ../../../deps/include/picojson
    LOG_DOWNLOAD 1
    LOG_BUILD 1
)
