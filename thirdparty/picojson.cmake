set(PICOJSON_PREFIX kazuho-picojson-25fc213)
set(PICOJSON_URL https://github.com/kazuho/picojson/archive/v1.3.0.tar.gz)
set(PICOJSON_URL_MD5 98cdf87f486c61794a4b02c4004cfb86)


ExternalProject_Add(${PICOJSON_PREFIX}
    PREFIX ${PICOJSON_PREFIX}
    URL ${PICOJSON_URL}
    URL_MD5 ${PICOJSON_URL_MD5}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    BUILD_IN_SOURCE 0
    INSTALL_COMMAND mkdir -p ../../../deps/include/picojson && cp ../kazuho-picojson-25fc213/picojson.h ../../../deps/include/picojson
    LOG_DOWNLOAD 1
    LOG_BUILD 1
)
