#解决后续cmake文件路径问题
CMAKE_3PART_LIB_PATH=/home/test/examples/lib/3partlib/lib64
CMAKE_3PART_INC_PATH=/home/test/examples/include/3partlib
cd ${CMAKE_3PART_LIB_PATH}/cmake/Drogon/
DROGON_PATH=${CMAKE_3PART_INC_PATH}/drogon
sed -i "/INTERFACE_INCLUDE_DIRECTORIES*/c\INTERFACE_INCLUDE_DIRECTORIES \"${DROGON_PATH}/include/\"" DrogonTargets.cmake

cd ${CMAKE_3PART_LIB_PATH}/cmake/Trantor/
TRANTOR_PATH=${CMAKE_3PART_INC_PATH}/trantor
sed -i "/INTERFACE_INCLUDE_DIRECTORIES*/c\INTERFACE_INCLUDE_DIRECTORIES \"${TRANTOR_PATH}/include/\"" TrantorTargets.cmake
