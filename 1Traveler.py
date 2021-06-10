import sys
if __name__ == '__main__':
    # read input
    n = int(sys.stdin.readline())
    # save the balls according to its color
    colorEnds = {}
    for _ in range(n):
        ballPos, ballColor = sys.stdin.readline().split()
        # convert string to int
        # we just need to find the left and right end of each color
        # because the optimal solution must gurantee that
        # each color starts end ends at its two ends.
        # the third element is step length
        # because we have to collect them all
        ballPos = int(ballPos)
        ballColor = int(ballColor)

        # save the balls according to its color
        if not colorEnds.__contains__(ballColor):
            # if the color does not in the dict
            # create a new key setting the two ends as the same
            colorEnds[ballColor] = [ballPos, ballPos]
        else:
            colorEnds[ballColor][0] = min(colorEnds[ballColor][0], ballPos)
            colorEnds[ballColor][1] = max(colorEnds[ballColor][1], ballPos)
    # print(colorEnds)

    # because color id does not start from 1
    # so we firstly collect all the colors and sort
    colors = list(colorEnds.keys())
    colors.sort()
    colors.append(0)
    # we use DP to solve this problem
    # dp[i] means the min time 
    # to collect the balls of the first i colors
    # Note that each dp[i] has four elements,
    # idx 0: num of total steps if start collecting from the left end
    # idx 1: ending position if start collecting from the left end
    # idx 2: num of total steps if start collecting from the right end
    # idx 3: ending position if start collecting from the right end

    # add an [0, 0] to go back to zero
    colorEnds[0] = [0, 0]
    print(colorEnds)

    numOfColors = len(colors)
    # print("num of colors:", numOfColors)
    dp = [[0,0,0,0]]

    # remind that the color id does not start from 1
    # but we have to collect from the smallest color ID
    for i in range(1, numOfColors+1):
        currentDP = [0,0,0,0]

        colorIdx = colors[i-1]
        # leftEnd of current color
        leftEnd = colorEnds[colorIdx][0]
        # rightEnd of current color
        rightEnd = colorEnds[colorIdx][1]
        # stepLen is collecting length
        stepLen = rightEnd - leftEnd
        # print("colorIdx: ", colorIdx, " leftEnd: ", leftEnd, " rightEnd: ", rightEnd, " len: ", stepLen)

        # if we start from the left end
        # steps continuing from the left end of the last step
        lNumSteps = dp[i-1][0] + stepLen + abs(dp[i-1][1] - rightEnd)
        # steps continuing from the right end of the last step
        rNumSteps = dp[i-1][2] + stepLen + abs(dp[i-1][3] - rightEnd)
        # print("lNumSteps1: ", lNumSteps, " rNumSteps1: ", rNumSteps)
        if lNumSteps < rNumSteps:
            currentDP[0] = lNumSteps
        else:
            currentDP[0] = rNumSteps
        # start from right so end at left
        currentDP[1] = leftEnd

        # if we start from the right end
        # steps continuing from the left end of the last step
        lNumSteps = dp[i-1][0] + stepLen + abs(dp[i-1][1] - leftEnd)
        # steps continuing from the right end of the last step
        rNumSteps = dp[i-1][2] + stepLen + abs(dp[i-1][3] - leftEnd)
        # print("lNumSteps2: ", lNumSteps, " rNumSteps2: ", rNumSteps)
        if lNumSteps < rNumSteps:
            currentDP[2] = lNumSteps
        else:
            currentDP[2] = rNumSteps
        # start from left so end at right
        currentDP[3] = rightEnd
        # print(currentDP)
        dp.append(currentDP)
        # print(dp[-1])

    # do not forget to go back to original position
    minSteps = dp[numOfColors][0]
    print(minSteps)
    # print(dp)
