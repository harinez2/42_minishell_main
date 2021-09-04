import os
import re

path = os.path.dirname(__file__) + '/../srcs'
prototype_h = os.path.dirname(__file__) +'/../inc/prototypes.h'

files = os.listdir(path)
files_file = [f for f in files if os.path.isfile(os.path.join(path, f))]

l = list()
for file in files_file:
	with open(path + '/' + file) as f:
		l.append('// ' + file)
		l_strip = [s.rstrip() for s in f.readlines()]
		flg = 0
		for s in l_strip:
			if flg == 1:
				l.append(s + ';')
				flg = 0
				continue
			if re.fullmatch('^[vitcs][^t].*\)', s):
				l.append(s + ';')
			if re.fullmatch('^[vitcs][^t].*[^\)]', s):
				l.append(s)
				flg = 1

with open(prototype_h, mode='w') as f:
	f.write('#ifndef PROTOTYPES_H\n')
	f.write('# define PROTOTYPES_H\n')
	f.write('\n')
	for line in l:
		f.write(line + '\n')
	f.write('\n')
	f.write('#endif\n')

