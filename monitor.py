import os
import glob
import codecs
import re
import datetime
import argparse
import matplotlib.pyplot as plt
#from matplotlib import dates as mdates

filepath = '../*.mca'
file_list = glob.glob(filepath)#, recursive=True)

rate = plt.figure(figsize=(12,8))
ax_rate = rate.add_subplot(111)
ax_rate.set_xlabel('date')
ax_rate.set_ylabel('rate[/s]')
spec = plt.figure(figsize=(12,8))
ax_spec = spec.add_subplot(111)
ax_spec.set_xlabel('channel')
ax_spec.set_ylabel('rate[/s]')
ax_spec.set_yscale('log')

parser = argparse.ArgumentParser()
parser.add_argument("-s",help="start date. for example 2021-01-09-00:00:00",default='2021-01-09-00:00:00',type=str)
parser.add_argument("-e",help="end date. for example 2021-01-11-00:00:00 or now",default='now',type=str)
args = parser.parse_args()
start = datetime.datetime.strptime(args.s, '%Y-%m-%d-%H:%M:%S')
if args.e=='now':
	end = datetime.datetime.now()
else:
	end = datetime.datetime.strptime(args.e, '%Y-%m-%d-%H:%M:%S')
#start = args.s
#end = args.e

for file_path in file_list:
	print(file_path)
	with codecs.open(file_path, 'r', 'utf-8', 'ignore') as file:
		lines = file.readlines()
	
		spectrum=[]
		flag=False
		draw=False

		for line in lines:
		    if 'LIVE_TIME' in line:
		        livetime = float(re.sub(r"[^\d.]", "", line))
		    if 'START_TIME' in line:
		        runstart = line[14:-2]
		        runstart = datetime.datetime.strptime(runstart, '%m/%d/%Y %H:%M:%S')
				#runend = runstart + datetime.timedelta(seconds=livetime)
		        #start = datetime.date(start.year, start.month, start.day)
		    if '<<DATA>>' in line:
		        flag=True
		        continue
		    elif '<<END>>' in line:
		        flag=False
		        break

		    if flag:
		        #print(line)
		        spectrum.append(int(re.sub(r"\D", "", line)))
		
		bins = len(spectrum)
		counts = sum(spectrum)
		
		if (runstart>start)and(runstart<end):
			draw=True 
		

		ax_rate.scatter(runstart,counts/livetime,c='C0',s=10)
		ax_rate.set_xlim(start,end)
		#ax_rate.xaxis.set_major_formatter(mdates.DateFormatter('%m/%d\n%H:%M'))	
		if draw:
			ax_spec.plot(range(0,bins),spectrum,label=runstart)
		ax_spec.legend()
plt.show()
		#ax_rate.show()
		#ax_spec.show()
