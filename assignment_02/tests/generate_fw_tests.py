import random
import os

# generate test file for floyd warshall
def genFWTest(fName, numNodes):

    f = open(fName, "w")
    f.write(str(numNodes) + "\n")

    for i in range(numNodes):

        rowList = []

        for j in range(numNodes):

            if i == j:

                rowList.append("0")
            else:

                # 70% chance edge, 30% INF
                if random.random() < 0.7:

                    wt = random.randint(1, 20)
                    rowList.append(str(wt))
                else:

                    rowList.append("INF")

        lineStr = ""
        for idx in range(len(rowList)):

            lineStr = lineStr + rowList[idx]
            if idx < len(rowList) - 1:

                lineStr = lineStr + " "

        f.write(lineStr + "\n")

    f.close()

    print("Generated " + fName + " successfully.")


if __name__ == "__main__":

    os.makedirs("assignment_02/tests", exist_ok=True)

    nodeSizes = [10, 100, 500, 1000, 2000]

    for nVal in nodeSizes:

        outPath = "assignment_02/tests/fw_" + str(nVal) + ".txt"
        genFWTest(outPath, nVal)