message(STATUS ${CMAKE_CURRENT_LIST_FILE})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(${QOds_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib)

if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (NOT MSVC)

# Set some Win32 Specific Settings
if(WIN32)
	set(GUI_TYPE "") #or WIN32 for no console output
# Set some Apple MacOS Specific settings
elseif (APPLE)
	set(GUI_TYPE MACOSX_BUNDLE)
endif (WIN32)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Test REQUIRED)

set(src_files
	examples1.cpp examples1.hpp
	examples2.cpp examples2.hpp
	Invoice.cpp Invoice.hpp
	Item.cpp Item.hpp
	main.cpp
	util.cpp util.hpp
	)

foreach(f IN LISTS src_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

set (exe_name "ods_example")
add_executable(${exe_name} ${GUI_TYPE} ${src_files})
get_property(zlib_libs GLOBAL PROPERTY zlib_libs_property)
target_link_libraries(${exe_name} ods quazip ${zlib_libs} Qt5::Core Qt5::Gui)

enable_testing()
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

macro(add_test testname testsrc)
set(test_${testname}_SRCS ${testsrc})
add_executable(test_${testname} ${test_${testname}_SRCS})
target_link_libraries(test_${testname} Qt5::Core Qt5::Gui Qt5::Test ods)
endmacro(add_test)

include_directories(test)
add_test(0_read_cells test/ReadCells.cpp test/ReadCells.hpp)
add_test(1_write_out test/WriteOut.cpp test/WriteOut.hpp)

