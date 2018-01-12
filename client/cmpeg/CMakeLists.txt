# define the minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(cmpeg)

# 
SET(CMAKE_VERBOSE_MAKEFILE ON)

# use folder
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDER ON)

# messages
MESSAGE(STATUS "cmpeg build begin")

# set run time path
SET(CMPEG_ROOT_PATH "${PROJECT_SOURCE_DIR}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMPEG_ROOT_PATH}/bin")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMPEG_ROOT_PATH}/lib")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMPEG_ROOT_PATH}/lib")

IF(WIN32)
	
ELSE()
	MESSAGE(STATUS "For now, I only test on windows platform, even i think this should be ok for mac linux ios android")
ENDIF()

# auto group files
MACRO(GROUP_FILES src_files root_path)
    SET(cur_dir ${root_path})
    FOREACH(group_files ${${src_files}})
        STRING(REGEX REPLACE ${cur_dir}/\(.*\) \\1 sgbd_fpath ${group_files})
        STRING(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
        STRING(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
        STRING(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
        IF(sgbd_nogroup)
			SOURCE_GROUP("" FILES ${group_files})   
		ELSE()
			INCLUDE_DIRECTORIES(${sgbd_group_name})
			SOURCE_GROUP(${sgbd_group_name} FILES ${group_files})   
           ENDIF(sgbd_nogroup) 
    ENDFOREACH(group_files)
ENDMACRO(GROUP_FILES)

ADD_SUBDIRECTORY("cmpeg")
ADD_SUBDIRECTORY("examples")

