# author f35f22fan at gmail dot com
# extensions:
# .hh, .cc:  namespace with functions
# .cpp, hpp: classes
# .hxx:      (const) declarations
message(STATUS ${CMAKE_CURRENT_LIST_FILE})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(${QOds_SOURCE_DIR})
link_directories(${QOds_BINARY_DIR}/lib)

if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (NOT MSVC)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

set(lib_files
    Attr.cpp Attr.hpp
    Attrs.cpp Attrs.hpp
    Book.cpp Book.hpp
    Cell.cpp Cell.hpp cell.hxx
    CellRef.cpp CellRef.hpp
    Column.cpp Column.hpp
    CompareNumbers.hh
    Content.cpp Content.hpp
    Country.cpp Country.hpp
    CurrencyInfo.cpp CurrencyInfo.hpp
    DateInfo.cpp DateInfo.hpp
    decl.hxx
    DrawFrame.cpp DrawFrame.hpp
    Duration.cpp Duration.hpp
    DurationInfo.cpp DurationInfo.hpp
    err.hpp
    filename.hxx
    Formula.cpp Formula.hpp formula.hxx
    global.hxx
    i18n.hxx
    Manifest.cpp Manifest.hpp
    meta.cc meta.hh
    Meta.cpp Meta.hpp
    Node.cpp Node.hpp node.hxx
    Ns.cpp Ns.hpp ns.hxx
    ods
    ods.cc ods.hh ods.hxx
    Prefix.cpp Prefix.hpp
    Region.cpp Region.hpp region.hxx
    Row.cpp Row.hpp
    Settings.cpp Settings.hpp
    Sheet.cpp Sheet.hpp
    Style.cpp Style.hpp
    tag.cc tag.hh
    Tag.cpp Tag.hpp
    util.cc util.hh
    Value.cpp Value.hpp
    
    style/Border.cpp style/Border.hpp
    style/Currency.cpp style/Currency.hpp
    style/Date.cpp style/Date.hpp
    style/decl.hxx
    style/Duration.cpp style/Duration.hpp
    style/Manager.cpp style/Manager.hpp
    style/Percent.cpp style/Percent.hpp
    style/style.hxx
    style/StyleFamily.cpp style/StyleFamily.hpp
    style/Substyle.cpp style/Substyle.hpp
    style/tag.cc style/tag.hh
	)

foreach(f IN LISTS lib_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

if (DEFINED ODS_STATIC)
	set(lib_type STATIC)
else (DEFINED ODS_STATIC)
	set(lib_type SHARED)
	add_definitions(-DODS_SHARED -DODS_BUILDING)
endif (DEFINED ODS_STATIC)

add_library(ods ${lib_type} ${lib_files})
target_link_libraries(ods quazip Qt5::Core Qt5::Gui)



 
