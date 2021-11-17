# coding:utf-8
import os

import os,shutil

'''
目的:获取目标文件夹下所有类型的指定文件

findAllFilesWithSpecifiedSuffix:寻找特定后缀的所有文件
copyFilesToSpecifiedPath:拷贝文件到特定路径
replaceFilesContent:替换文件列表里old_content为new_content
'''

class FileUtil:
    @staticmethod
    def findAllFilesWithSpecifiedSuffix(target_dir, target_suffix="txt"):
        find_res = []
        target_suffix_dot = "." + target_suffix
        walk_generator = os.walk(target_dir)
        for root_path, dirs, files in walk_generator:
            if len(files) < 1:
                continue
            for file in files:
                file_name, suffix_name = os.path.splitext(file)
                if suffix_name == target_suffix_dot:
                    find_res.append(os.path.join(root_path, file))
        return find_res

    @staticmethod
    def copyFilesToSpecifiedPath(file_name_list,targetPath):
        for file_name in file_name_list:
            shutil.copy(file_name, targetPath)

    @staticmethod
    def findAndCopyPngFileToSpecifiedPath(target_dir,suffix,target_path):
        find_res = FileUtil.findAllFilesWithSpecifiedSuffix(target_dir, suffix)
        print(find_res)
        FileUtil.copyFilesToSpecifiedPath(find_res,target_path)

    @staticmethod
    def replaceFilesContent(file_name_list, old_content, new_content):
        for file_name in file_name_list:
            with open(file_name, mode="r", encoding="UTF-8") as f1, \
                    open(file_name + "_new", mode="w", encoding="UTF-8") as f2:
                for line in f1:
                    line = line.replace(old_content, new_content)
                    f2.write(line)
            os.remove(file_name)
            os.rename(file_name + "_new", file_name)

    @staticmethod
    def replaceFilesContent(file_name_list, dict_content):
        for file_name in file_name_list:
            with open(file_name, mode="r", encoding="UTF-8") as f1, \
                    open(file_name + "_new", mode="w", encoding="UTF-8") as f2:
                for line in f1:
                    for key in dict_content.keys():
                        print( key + ":" + str(dict_content[key]))
                        line = line.replace("$"+key, str(dict_content[key]))
                    f2.write(line)
            os.remove(file_name)
            os.rename(file_name + "_new", file_name)

    @staticmethod
    def findAndReplaceFilesToSpecifiedContent(target_dir,suffix,old_content,new_content):
        find_res = FileUtil.findAllFilesWithSpecifiedSuffix(target_dir, suffix)
        print(find_res)
        FileUtil.replaceFilesContent(find_res,old_content,new_content)


class Util:

    @staticmethod
    def mkdir(path):
        """判断文件夹是否存在，不存在就创建"""
        if not os.path.exists(path):
            os.mkdir(path)

    @staticmethod
    def is_file(path: str, extension: list):
        """
        判断路径是否是文件，且该文件格式是否存在于集合中
        :param path: 文件路径
        :param extension: 文件后缀集合
        :return: boolean
        """
        return os.path.isfile(path) and path.rsplit('.', 1)[1] in extension

    @staticmethod
    def get_path():
        """获取当前文件所处的路径"""
        path = os.getcwd()
        return path

    @staticmethod
    def load_setting_from_obj(obj: object):
        """
        读取对象中所有自定义的属性，保存在一个字典中并返回
        :param obj:对象
        :return: attrs,保存了对象所有自定义属性的字典
        """
        attrs = {key: values for key, values in obj.__dict__.items() if not key.startswith('__')}
        return attrs
