#解决后续cmake文件路径问题
CMAKE_3PART_LIB_PATH=/home/test/examples/lib/3partlib/lib64
CMAKE_3PART_INC_PATH=/home/test/examples/include/3partlib

DROGON_PATH=${CMAKE_3PART_INC_PATH}/drogon
sed -i "/INTERFACE_INCLUDE_DIRECTORIES*/c\INTERFACE_INCLUDE_DIRECTORIES \"${DROGON_PATH}/include/\"" ${CMAKE_3PART_LIB_PATH}/cmake/Drogon/DrogonTargets.cmake

TRANTOR_PATH=${CMAKE_3PART_INC_PATH}/trantor
sed -i "/INTERFACE_INCLUDE_DIRECTORIES*/c\INTERFACE_INCLUDE_DIRECTORIES \"${TRANTOR_PATH}/include/\"" ${CMAKE_3PART_LIB_PATH}/cmake/Trantor/TrantorTargets.cmake
