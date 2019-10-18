// https://www.hackerrank.com/challenges/find-the-nearest-clone/problem
// O(|E|)

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.stream.*;
import java.util.regex.*;

public class Solution {

    static class Node {
        int id;
        List<Node> neighbors;
        int color = -1; // unknown

        int state = 0; // not visited
        int path = -1; // unknown // path len to nodes with target color
        public Node(int id) {
            this.id = id;
            this.neighbors = new ArrayList();
        }
    }

    static int BFS(ArrayDeque<Node> queue) {
        while (!queue.isEmpty()) {
            Node a = queue.removeFirst();
            a.state = 2; // done
            for (Node n: a.neighbors) {
                if (n.state == 0) {
                    n.state = 1;
                    n.path = a.path + 1;
                    queue.add(n);
                } else if (n.state == 1) {
                    return n.path + 1 + a.path;
                    // assumes: unique neighbors
                    // how do u know n.path is another path
                    // because it's state 1, that means its ancestor is someone else
                    // and state 2 means `n` has checked `a`
                }
            }
        }
        return -1;
    }

    // Complete the findShortest function below.

    /*
     * For the unweighted graph, <name>:
     *
     * 1. The number of nodes is <name>Nodes.
     * 2. The number of edges is <name>Edges.
     * 3. An edge exists between <name>From[i] to <name>To[i].
     *
     */
    static int findShortest(int graphNodes, int[] graphFrom, int[] graphTo, int[] ids, int val) {
        // 0 is a dummy node, 1-indexed
        Node[] nodes = IntStream.rangeClosed(0, graphNodes)
            .mapToObj(i -> new Node(i))
            .toArray(Node[]::new);
        int nEdges = graphFrom.length;
        for (int i = 0; i < nEdges; i++) {
            Node head = nodes[graphFrom[i]];
            Node tail = nodes[graphTo[i]];
            head.neighbors.add(tail);
            tail.neighbors.add(head);
        }

        ArrayDeque<Node> queue = new ArrayDeque<Node>();
        for (int i = 0; i < ids.length; i++) {
            int color = ids[i];
            Node node = nodes[i+1];
            node.color = color;
            if (color == val) {
                queue.add(node);
                node.path = 0;
                node.state = 1; // in queue
            }
        }

        return BFS(queue);
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] graphNodesEdges = br.readLine().split(" ");
        int graphNodes = Integer.parseInt(graphNodesEdges[0].trim());
        int graphEdges = Integer.parseInt(graphNodesEdges[1].trim());

        int[] graphFrom = new int[graphEdges];
        int[] graphTo = new int[graphEdges];

        for (int i = 0; i < graphEdges; i++) {
            String[] graphFromTo = br.readLine().split(" ");
            graphFrom[i] = Integer.parseInt(graphFromTo[0].trim());
            graphTo[i] = Integer.parseInt(graphFromTo[1].trim());
        }

        int[] ids = new int[graphNodes];

        String[] idsItems = br.readLine().split(" ");

        for (int i = 0; i < graphNodes; i++) {
            int idsItem = Integer.parseInt(idsItems[i]);
            ids[i] = idsItem;
        }

        int val = Integer.parseInt(br.readLine().split(" ")[0]);
        br.close();

        int ans = findShortest(graphNodes, graphFrom, graphTo, ids, val);

        bufferedWriter.write(String.valueOf(ans));
        bufferedWriter.newLine();

        bufferedWriter.close();
    }
}
