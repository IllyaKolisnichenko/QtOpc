set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS "${PROJECT_HEADER_DIR}/*.h")


find_package(Qt5 5.15.0 COMPONENTS REQUIRED
    Core Gui Widgets OpcUa
)

add_executable(${PROJECT_NAME}
    # headers
    ${APP_HEADERS}
    # sources
    ${APP_SOURCES}
)

# Automatic Qt related compilers
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    AUTOUIC_SEARCH_PATHS forms)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_HEADER_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpcUa
)
