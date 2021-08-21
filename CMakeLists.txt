CMAKE_MINIMUM_REQUIRED(VERSION 3.16) #cmake最低版本
PROJECT("zhixueUtilities") #Project name
SET(CMAKE_CXX_STANDARD 17)
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
SET(CMAKE_CXX_FLAGS "-ljsoncpp")#编译选项，非紧急情况不要动。
IF(WIN32)
    SET(CMAKE_CXX_FLAGS "-lcurldll")
ELSEIF(APPLE)
    SET(CMAKE_CXX_FLAGS "-lcurl")
ELSEIF(UNIX)
    SET(CMAKE_CXX_FLAGS "-lcurl")
ENDIF()
SET(SRC_LISTS ${DIR_SRCS})#将源文件整理进一个变量，方便管理。文件之间用半角分号分割。
ADD_EXECUTABLE(zhixueUtilities ${SRC_LISTS})#同上。
IF(WIN32)
    TARGET_LINK_LIBRARIES(zhixueUtilities jsoncpp curldll)
ELSEIF(APPLE)
    TARGET_LINK_LIBRARIES(zhixueUtilities jsoncpp curl)
ELSEIF(UNIX)
    TARGET_LINK_LIBRARIES(zhixueUtilities jsoncpp curl)
ENDIF()
