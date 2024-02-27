n = int(input())
m = int(input())

# Reading maximum matrix of size nxm
maxim = []
for i in range(n):        
    a =[]
    for j in range(m):    
         a.append(int(input()))
    maxim.append(a)

maxim = ((maxim))

# Write code here to read allocation matrix and total vectors.

def findID(finish, id, n):
    # Write code here that could return -2, -1, and 0.
    # -2 if all the processes finished their tasks.
    # -1 if the current process id finished its task.
    # 0 if scope is there to explore the current process.

def computeAvail(total, alloc, n, m):
    # Write code here that could return the available vector.

def printTable(maxim, alloc, need, rem):
    print('\nMax      Alloc     Need      Avail')
    # Write code to print the output table 
    # See example test case for reference.

def bankers(maxim, alloc, total, n, m):
    finish = [False]*n
    safe = [-1]*n
    need = []
    for i in range(n):        
        a =[]
        for j in range(m):    
            a.append(maxim[i][j]-alloc[i][j])
        need.append(a)
    
    avail = computeAvail(total, alloc, n, m)
    
    work = [row.copy() for row in avail]
    id = 0
    k = 0
    iter = 0;
    while (True):
        status = findID(finish, id, n)
        if (status == -2):
            # Write code here
        elif (status == -1):
            # Write code here.
        else:
            # Write code here.
    return need, avail, safe

need, avail, safe = bankers(maxim, alloc, total, n, m)

printTable(maxim, alloc, need, avail)
seq = [];
for i in range(0, n):
    seq.append('P'+str(safe[i]))
print('\nSafe Seequence is : ',tuple(seq))