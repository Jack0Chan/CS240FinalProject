import sys
if __name__ == '__main__':
    # read input
    N = int(input())

    # if A is already a Bitcon Array
    # then obviously
    # evenList & oddList must be Bitcon Arrays
    # more formally, for i<k<j, 
    # A[i]+A[j]!=2A[k] ==> (2A[i])  +(2A[j])  !=2(2A[k])
    # A[i]+A[j]!=2A[k] ==> (2A[i]-1)+(2A[j]-1)!=2(2A[k]-1)
    A = [1]
    while len(A) < N:
        evenList, oddList = [], []
        for i in range(len(A)):
            evenList.append(2*A[i])
            oddList.append(2*A[i] - 1)
            # print("even:", evenList)
            # print("odd:", oddList)
        # now we connect the two list together
        # 1. for i<k<j, if i,j,k are all in even or odd list
        #    obviously A[i]+A[j]!=2A[k]
        # 2. if i is in even and j is in odd
        #    the A[i]+A[j] must be odd
        #    because 2A[k] is even
        #    odd can not be equal to even!
        A =  evenList + oddList

    # get the first smallest N elements
    resultA = []
    for i in A:
        if i <= N:
            resultA.append(i)
    print(resultA)