f = open("example.txt","r") 
myList =[]
for line in f:
	myList.append(line);

finallist=list(reversed(myList))


qa=[]

for x in finallist:
	x=x[1:]
	qa=qa+[x]
	print(x)
	print(str(x))

re=[]
for x in qa:
	x=str(x).replace("-",",")
	re=re+[str(str(x).replace("-",",")).replace("\n","")]

ans=[]
for x in re:
	i=x.find(',')
	ans=ans+[(x[:i],x[i+1:])]

print(ans)