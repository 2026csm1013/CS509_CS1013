import random
import os

# generate test file for bellman ford
def genBFTest(fName, numNodes, deg=3):

    totalEdges = numNodes * deg
    edgesSet = set()

    # connect nodes in a line
    for i in range(numNodes - 1):

        edgesSet.add((i, i + 1))

    # add remaining random edges
    while len(edgesSet) < totalEdges:

        uNode = random.randint(0, numNodes - 1)
        vNode = random.randint(0, numNodes - 1)

        if uNode != vNode:

            edgesSet.add((uNode, vNode))

    # build adjacency list
    adjList = {}
    for i in range(numNodes):

        adjList[i] = []

    for uNode, vNode in edgesSet:

        # positive weights between 1 and 20
        wt = random.randint(1, 20)
        adjList[uNode].append((vNode, wt))

    # write to output file format
    f = open(fName, "w")

    f.write(str(numNodes) + " " + str(len(edgesSet)) + "\n")

    for uNode in range(numNodes):

        curEdges = adjList[uNode]
        dCount = len(curEdges)

        lineStr = str(uNode) + " " + str(dCount)

        for vNode, wt in curEdges:

            lineStr = lineStr + " " + str(vNode) + " " + str(wt)

        f.write(lineStr + "\n")

    f.write("SOURCE 0\n")
    f.close()

    print("Generated " + fName + " successfully.")


if __name__ == "__main__":

    os.makedirs("assignment_02/tests", exist_ok=True)

    nodeSizes = [10, 100, 10000, 50000, 100000]

    for nVal in nodeSizes:

        outPath = "assignment_02/tests/bf_" + str(nVal) + ".txt"
        genBFTest(outPath, nVal, 3)