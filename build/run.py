import xlrd
from xlrd import xldate_as_tuple
import datetime
import json
import os
import sys
sys.path.append('D:\CODE\klc\markdown\python\excel')
from  pythonUtil.util import FileUtil,Util

'''
xlrd中单元格的数据类型
数字一律按浮点型输出，日期输出成一串小数，布尔型输出0或1，所以我们必须在程序中做判断处理转换
成我们想要的数据类型
0 empty,1 string, 2 number, 3 date, 4 boolean, 5 error

pip install xlrd==1.2.0
'''
class ExcelData():
    # 初始化方法
    def __init__(self, data_path, sheetname):
        self.data_path = data_path #定义一个属性接收文件路径
        self.sheetname = sheetname # 定义一个属性接收工作表名称
        self.data = xlrd.open_workbook(self.data_path) # 使用xlrd模块打开excel表读取数据
        self.table = self.data.sheet_by_name(self.sheetname) # 根据工作表的名称获取工作表中的内容（方式①）
        # self.table = self.data.sheet_by_name(0) # 根据工作表的索引获取工作表的内容（方式②）
        self.keys = self.table.row_values(0)# 获取第一行所有内容,如果括号中1就是第二行，这点跟列表索引类似
        self.rowNum = self.table.nrows # 获取工作表的有效行数
        self.colNum = self.table.ncols # 获取工作表的有效列数

    def readSheetDataByName(self,sheetname):
        return self.data.sheet_by_name(sheetname)

    def readSheetDataByIndex(self,index):
        return self.data.sheet_by_name(index)

    def parseSheetData(self):
        datas = []
        for i in range(1, self.rowNum):
            sheet_data = {}
            for j in range(self.colNum):
                sheet_data[self.keys[j]] = self.table.cell_value(i, j)
            datas.append(sheet_data)
        return datas

    def getDefKeyAndValue(self,keyIndex,valueIndex):
        datas = []
        sheet_data = {}
        for i in range(1, self.rowNum):
            sheet_data[self.getCellTypeValue(i, keyIndex)] = self.getCellTypeValue(i, valueIndex)
        datas.append(sheet_data)
        return datas

    def getCellTypeValue(self,i,j):
        c_type = self.table.cell(i, j).ctype  # 获取单元格数据类型
        c_cell = self.table.cell_value(i, j)  # 获取单元格数据
        if c_type == 2 and c_cell % 1 == 0:  # 如果是整形
            c_cell = int(c_cell)
        elif c_type == 3:
            date = datetime.datetime(*xldate_as_tuple(c_cell, 0)) # 转成datetime对象
            c_cell = date.strftime('%Y/%d/%m %H:%M:%S')
        elif c_type == 4:
            c_cell = True if c_cell == 1 else False
        return c_cell

    def getColNameIndex(self,ColName):
        index = -1
        for j in range(self.colNum):
            if self.keys[j] == ColName :
                return j
        return index

    def save_json_file(self, data, path):
        with open(path, 'w', encoding="utf-8") as fp:
            json.dump(data, fp, ensure_ascii=False)
        print('final data save in ',path)

    def replaceFilesContent(file_name_list, old_content, new_content):
        for file_name in file_name_list:
            with open(file_name, mode="r", encoding="UTF-8") as f1, \
                    open(file_name + "_new", mode="w", encoding="UTF-8") as f2:
                for line in f1:
                    line = line.replace(old_content, new_content)
                    f2.write(line)
            os.remove(file_name)
            os.rename(file_name + "_new", file_name)

if __name__ == "__main__":
    data_path = "3part.xlsx"

    #获取3part.xlsx中 第三方组件列表 页的内容，包含全部内容和关键信息
    sheetname = "第三方组件列表"
    get_comp3partinfo_data = ExcelData(data_path, sheetname)
    comp3partinfo_full_datas = get_comp3partinfo_data.parseSheetData()
    get_comp3partinfo_data.save_json_file(comp3partinfo_full_datas, "comp3partinfo_full_datas.json")
    comp3partinfo_key = get_comp3partinfo_data.getColNameIndex('组件宏定义')
    comp3partinfo_value = get_comp3partinfo_data.getColNameIndex('文件名')
    comp3partinfo_key_datas = get_comp3partinfo_data.getDefKeyAndValue(comp3partinfo_key, comp3partinfo_value)
    get_comp3partinfo_data.save_json_file(comp3partinfo_key_datas, "comp3partinfo_key_datas.json")
    print(comp3partinfo_key_datas)

    #获取3part.xlsx中 变量信息 页的内容，包含全部内容和关键信息
    sheetname = "变量信息"
    get_varinfo_data = ExcelData(data_path, sheetname)
    varinfo_full_datas = get_varinfo_data.parseSheetData()
    get_varinfo_data.save_json_file(varinfo_full_datas, "varinfo_full_datas.json")
    varinfo_key=get_varinfo_data.getColNameIndex('宏定义')
    varinfo_value =get_varinfo_data.getColNameIndex('变量值')
    varinfo_key_datas=get_varinfo_data.getDefKeyAndValue(varinfo_key,varinfo_value)
    get_varinfo_data.save_json_file(varinfo_key_datas,"varinfo_key_datas.json")
    print(varinfo_key_datas)

    print(Util.get_path())
    FileUtil.replaceFilesContent(["common.sh"], comp3partinfo_key_datas[0])
    FileUtil.replaceFilesContent(["common.sh"],varinfo_key_datas[0])

