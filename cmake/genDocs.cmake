
find_package(Doxygen
    REQUIRED dot
    OPTIONAL_COMPONENTS mscgen dia)


# checks for documentation build
if(${BUILD_DOCS} AND ${Doxygen_FOUND})

    set(DOXYGEN_EXCLUDE_PATTERNS
    */build/*
    */out/*

    */.vscode/*
    */.vs/*
    
    */deps/*
    */cmake/*
    */tests/*
    )

    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)

    doxygen_add_docs(chitra_docs  ${CMAKE_SOURCE_DIR} ALL )

endif()
