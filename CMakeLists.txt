cmake_minimum_required(VERSION 3.29.0)

include("C:/CXXThirdParty/vcpkg/scripts/buildsystems/vcpkg.cmake") # 导入 vcpkg 工具链

project(dcmjp2k VERSION 1.0.5 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
  	string(APPEND CMAKE_CXX_FLAGS " /utf-8 /Zc:__cplusplus") # 1.指定 msvc 使用 utf8 编码；2.让 msvc 能够正确设置 __cplusplus 的值: 20170301
endif()

set(file_head
	include/dcmjp2k/djcodecd.h
	include/dcmjp2k/djcodece.h
	include/dcmjp2k/djcparam.h
	include/dcmjp2k/djdecode.h
	include/dcmjp2k/djencode.h
	include/dcmjp2k/djerror.h
	include/dcmjp2k/djlsutil.h
	include/dcmjp2k/djrparam.h
	include/dcmjp2k/dldefine.h
	include/dcmjp2k/memory_file.h
)

set(file_impl
	src/djcodecd.cc
	src/djcodece.cc
	src/djcparam.cc
	src/djdecode.cc
	src/djencode.cc
	src/djrparam.cc
	src/djutils.cc
	src/memory_file.cpp
)

add_library(${PROJECT_NAME} ${file_head} ${file_impl})
target_compile_definitions(${PROJECT_NAME} PRIVATE -Ddcmjp2k_EXPORTS)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# OpenJPEG lib
find_package(OpenJPEG CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE openjp2)

# DCMTK lib
find_package(DCMTK CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE DCMTK::DCMTK)
if ("${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" STREQUAL "/")
	message(WARNING "No vcpkg install dir found, DCMTK definitions are not set")
else()
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE
			"DCMTK_PREFIX=${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}"
			"DCM_DICT_DEFAULT_PATH=${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/dcmtk-${DCMTK_VERSION}/dicom.dic:${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/dcmtk-${DCMTK_VERSION}/private.dic"
			"DEFAULT_CONFIGURATION_DIR=${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/etc/dcmtk-${DCMTK_VERSION}/"
			"DEFAULT_SUPPORT_DATA_DIR=${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/dcmtk-${DCMTK_VERSION}/"
	)
endif()

# ADD_EXECUTABLE(dcmcjp2k test/dcmcjp2k.cc)
# TARGET_LINK_LIBRARIES(dcmcjp2k PRIVATE ${PROJECT_NAME})

# ADD_EXECUTABLE(dcmdjp2k test/dcmdjp2k.cc)
# TARGET_LINK_LIBRARIES(dcmdjp2k PRIVATE ${PROJECT_NAME})

# ADD_EXECUTABLE(app test/main.cpp)
# TARGET_LINK_LIBRARIES(app PRIVATE ${PROJECT_NAME})
