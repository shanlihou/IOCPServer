#listdir.py
import os 
import sys
import re
import datetime
import shutil
import string
def FindString(filePath, regex):
	fileObj = open(filePath, 'r', encoding= 'ISO-8859-1')
	j = 0
	for line in fileObj:
		j = j + 1
		if re.search(regex, line, re.I):
			print (j)
			break
def listyoudir(level, path): 
	for i in os.listdir(path): 
		print ('     '*(level+1) + i) 
		if os.path.isdir(path + '\\' + i): 
			listyoudir(level+1, path + '\\' + i)
		else:
			FindString(path + '\\' + i, sys.argv[1])
def patchFile(fileName):
	fileObj = open(fileName, 'r')
	fileNew = open("new.patch", 'w')
	for line in fileObj:
		fileNew.writelines(line[1:])
def cpFileByTime(filePath):
	os.mkdir("tempForCopy")
	for i in os.listdir(filePath):
		if os.path.isdir(filePath + '/' + i):
			print('')
		else:
			useTime = (os.stat(filePath + '/' +i).st_mtime)
			date = datetime.datetime.fromtimestamp(useTime)
			if(date.year == 2014) and (date.month == 3) and (date.day == 21) and (date.hour >= 14):
				print(i)
				shutil.copyfile(filePath + '/' + i, filePath + '/tempForCopy/' + i)

def txtToCsvPath(filePath):
	for i in os.listdir(filePath):
		if i.find('txt') != -1:
			if i.find('new') == -1:
				txtToCsv(i)
#judgeFile(i)
def judgeFile(fileName):
	fileObj = open(fileName, 'r')
	lineCount = 0
	for line in fileObj:
		count = 0
		for c in line:
			if c == '"':
				count = count + 1
		if count == 3:
			print(fileName)
			print(lineCount)
			print(line)
			break
		lineCount = lineCount + 1
def txtToCsv(fileName):
	fileObj = open(fileName, 'r')
	fileNameNew = fileName[0:-3] + 'new' + '.txt'
	fileNew = open('new/' + fileNameNew, 'w')
	pattern = re.compile(r'{\s*[0-9]+')
	number = 0
	flag = 0
	for line in fileObj:
		count = 0
		flag1 = 0
		flag2 = 0
		for c in line:
			if c == '"':
				if flag1 == 0:
					flag1 = count
				elif flag2 == 0:
					flag2 = count
			count = count + 1
		if flag2 != 0:
			str2 = pattern.search(line)
			if str2:
				str3 = str2.group()[1:]
				num = string.atoi(str3)
				if number > num:
					print(number)
					number = num
					
				if number < num:
					print(fileName + str(number) + '  ' + str(num))
					for lineNeed in range(number, num):
						str1 = str(lineNeed) + '{' + '""' + '\n'
						fileNew.writelines(str1)
						number = number + 1
				str1 = str3 + '{' + line[flag1:flag2 + 1] + '\n'
				fileNew.writelines(str1)
				number = number + 1
def SingleConv(fileName):
	fileObj = open(fileName,'r')
	fileNameNew = fileName[0:-3] + 'new' + '.csv'
	fileNew = open(fileNameNew, 'w')
	pattern = re.compile(r'[0-9]+,"')
	
	for line in fileObj:
		str1 = pattern.search(line)
		if(str1):
			print('hello')
		else:
			fileNew.writelines(line)
SingleConv(sys.argv[1])
#txtToCsvPath(sys.argv[1])
#txtToCsv(sys.argv[1])
#Rootpath = os.path.abspath('.') 
#print (Rootpath) 
#listyoudir(0, Rootpath)
#patchFile(sys.argv[1])
#cpFileByTime(sys.argv[1])
