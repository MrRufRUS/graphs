//#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include <istream>
#include <sstream>

using namespace std;


template <typename T>
void remove(std::vector<T>& v, size_t index) {
    v.erase(v.begin() + index);
}
class Graph {
    vector<vector<bool>> matrix;
    //vector<bool> visited;
    int size;

    std::vector <string> split(std::string s, std::string delimiter) {
        std::vector<string> words{};

        std::istringstream iss(s);
        copy(std::istream_iterator<string>(iss),
            std::istream_iterator<string>(),
            std::back_inserter(words));

        return words;
    }
    void reverseGraph(vector<vector<bool>>& reversedGraph) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                reversedGraph[i][j] = matrix[j][i];
            }
        }
        //matrix = reversedGraph;
        //print();
    }


    void dfs(int node, vector<bool>& visited, stack<int>& st) {
        visited[node] = true;

        for (int neighbor = 0; neighbor < size; neighbor++) {
            if (matrix[node][neighbor] && !visited[neighbor]) {
                dfs(neighbor, visited, st);
            }
        }
        //cout << node << " ";
        st.push(node);
    }
public:
    Graph() {
        size = 0;
    }
    Graph(std::string fileName) {
        size = 0;
        std::ifstream fin(fileName);
        if (!fin.is_open()) {
            std::cout << "File doesn't exist\n";
            return;
        }
        std::string s;
        std::getline(fin, s);
        std::vector<bool> vector_buff;
        //std::cout << s << std::endl;
        size = stoi(s);

        for (int i = 0; i < size; i++) {
            std::getline(fin, s);
            vector<string> string_buf = split(s, " ");
            for (auto el : string_buf) {
                bool bool_buf = (el == "1") ? true : false;
                vector_buff.push_back(bool_buf);
            }
            if (vector_buff.size() == size)
                matrix.push_back(vector_buff);
            vector_buff.clear();

            //visited.push_back(false);
        }

    }

    ~Graph() = default; 

    void print() {
        for (int i = 0; i < size; i++) {
            cout << "Node " << i << ": ";
            for (int j = 0; j < size; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    void addNode() {
        vector<bool> newRow;
        for (int i = 0; i < size; i++) {
            matrix[i].push_back(false);
            newRow.push_back(false);
        }
        newRow.push_back(false);
        matrix.push_back(newRow);
        size++;
    }
    void removeNode(int numberOfNode) {
        if(numberOfNode < 0 && numberOfNode >= size) {
            cout << "Cannot delete\n";
            return;
        }
        for (int i = 0; i < size; i++) {
            remove(matrix[i], numberOfNode);

        }
        remove(matrix, numberOfNode);
        size--;
    }

    void addEdge(int from, int to) {
        if (from < size && to < size && from != to && from >= 0 && to >= 0)
            matrix[from][to] = true;
        else
            cout << "Cannot add this Edge\n";
    }
    void removeEdge(int from, int to) {
        if (from < size && to < size && from != to && from >= 0 && to >= 0)
            matrix[from][to] = false;
        else
            cout << "Cannot delete this Edge\n";
    }
    /*
    void DFS(int vertex, vector<bool>& visited) {
        visited[vertex] = true;

        cout << vertex << " ";

        for (int i = 0; i < size; i++) {
            if (!visited[i] && matrix[vertex][i])
                DFS(i, visited);
        }
    }
    */
    void dfsSCC(int node, vector<bool>& visited, vector<vector<bool>>& reversed) {
        visited[node] = true;
        cout << node << " ";

        for (int i = 0; i < size; i++) {
            if (!visited[i] && reversed[node][i])
                dfsSCC(i, visited, reversed);
        }
    }
    void kosarajuAlgorithm() {
        vector<bool> visited(size, false);
        stack<int> st;

        // Step 1: Perform DFS and push nodes into stack based on finishing time
        for (int i = 0; i < size; i++) {
            if (!visited[i]) {
                dfs(i, visited, st);
            }
        }

        // Step 2: Reverse  && from < size && to < sizethe graph
        vector<vector<bool>> reversedGraph(size, vector<bool>(size, false));
        reverseGraph(reversedGraph);

        // Step 3: Perform DFS on reversed graph using nodes from stack
        fill(visited.begin(), visited.end(), false);
        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                cout << "Strongly Connected Component: ";
                dfsSCC(node, visited, reversedGraph);
                cout << endl;
            }
        }
    }

    void dfs(int node) {
        vector<bool> visited(size, false);
        if (node < size && node >= 0) {
            cout << "DFS: ";
            dfsSCC(node, visited, matrix);
            cout << endl;
        }
        else {
            cout << "Forbiden Node\n";
        }
    }
};

int main() {
    Graph gr = Graph("text.txt");
    gr.print();
    gr.kosarajuAlgorithm();
    return 0;
}
