#!/bin/bash
#export build_3partlib_list='cppcheck cppunit fastcgi redis jsoncpp log4cpp tinyxml yamlcpp zeromq'
#export build_comlib_list='Common Data/MySQL Data/Redis JSON Log'

# 是否截取构建时，需要构建的列表进行校验，且需要提出一些zeromq需要等待的内容
build_3partlib_list='fastcgi redis jsoncpp log4cpp tinyxml yamlcpp'
build_comlib_list='Common JSON Log'
deploy_3partlib_path='deploy/3partlib'
deploy_comlib_path='deploy/comlib'
pass_log='pass.log'
fail_log='fail.log'
curPath=`pwd`

function verify_3partlib() {
    echo "bgein to verify 3partlib"

    for cur_item in $build_3partlib_list; do
        if [ -d ${curPath}/../${deploy_3partlib_path}/${cur_item} ]; then
            echo "$cur_item verify"
            cd ${curPath}/../${deploy_3partlib_path}/${cur_item}
            need_exec_list=$(ls)
            cur_path=$(pwd)
            for need_exec in $need_exec_list; do
                echo "$need_exec result:" >>${curPath}/${pass_log}
                echo "$need_exec result:" >>${curPath}/${fail_log}
                ./${need_exec} 1>>${curPath}/${pass_log} 2>>${curPath}/${fail_log}
            done
        fi
    done

    echo "end to verify 3partlib"
}

function verify_comlib() {
    echo "bgein to verify comlib"

    for cur_item in $build_comlib_list; do
        if [ -d ${curPath}/../${deploy_comlib_path}/${cur_item} ]; then
            echo "$cur_item verify"
            cd ${curPath}/../${deploy_comlib_path}/${cur_item}
            need_exec_list=$(ls)
            cur_path=$(pwd)
            for need_exec in $need_exec_list; do
                echo "$need_exec result:" >>${curPath}/${pass_log}
                echo "$need_exec result:" >>${curPath}/${fail_log}
                ./${need_exec} 1>>${curPath}/${pass_log} 2>>${curPath}/${fail_log}
            done
        fi
    done

    echo "end to verify comlib"
}

function MAIN() {
    echo "verify_result MAIN begin"
    verify_3partlib
    verify_comlib
    echo "verify_result MAIN end"
}

MAIN