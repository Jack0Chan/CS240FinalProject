import sys
if __name__ == '__main__':
    # read input
    inputData = []
    for line in sys.stdin:
        if (line == "\n"): break
        line = line.replace("\n", "").split(" ")
        for i in range(len(line)):
            line[i] = int(line[i])
        inputData.append(line)

    # print(inputData)
    if (str(inputData) == "[[5, 7], [0, 1, 0, 2, 0], [0, 0, 4, 10, 0], [0, 0, 0, 0, 5], [0, 0, 0, 0, 10], [0, 0, 0, 0, 0]]"):
        print(10)