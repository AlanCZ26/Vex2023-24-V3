import matplotlib.pyplot as plt
mainListM = []
mainListT = []
listM = []
listT = []

pltListMTarget = []
pltListMTime = []
pltListTTarget = []
pltListTTime = []

sectionType = 0
with open('/Users/alan/Documents/GitHub/Vex2023-24-V3/output.txt', 'r') as file:
    for lineNum, line in enumerate(file):
        print(line.strip())
        if (line.find("--------END-------") != -1):
            sectionType = 0
            if (len(listM)>0): mainListM.append(listM)
            if (len(listT)>0): mainListT.append(listT)
        if (line.find("--------MOV-------") != -1):
            sectionType = 1
            listM = []
        if (line.find("--------TRN-------") != -1):
            sectionType = 2
            listT = []

        if sectionType == 1:
            if (line.find("Target: ")!=-1): listM.insert(0,abs(int(line.replace("Target: ",""))))
            if (line.find("TOOK ")!=-1): listM.insert(1,(int((line.replace("TOOK ","")).replace("MS",""))))
            if (line.find("TIMED OUT")!=-1): listM = [] #.insert(1,(int(((file.readline(lineNum+1).replace("(","")).replace("ms)","")).strip())))

        if sectionType == 2:
            if (line.find("Target: ")!=-1): listT.insert(0,abs(int(line.replace("Target: ",""))))
            if (line.find("TOOK ")!=-1): listT.insert(1,(int((line.replace("TOOK ","")).replace("MS",""))))
            if (line.find("TIMED OUT")!=-1): listT = []

print(mainListM)

for l in mainListM:
    pltListMTarget.append(l[0])
    pltListMTime.append(l[1])
for l in mainListT:
    pltListTTarget.append(l[0])
    pltListTTime.append(l[1])

plt.scatter(pltListMTarget,pltListMTime,None,"red")
#plt.scatter(pltListTTarget,pltListTTime,None,"blue")
plt.show()