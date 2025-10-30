#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

struct Node {
    string id;
    string parent;
    vector<string> children;
    int depth;
    int subtreeSize;

    Node() : depth(0), subtreeSize(0) {}
};

class CommandTree {
private:
    unordered_map<string, Node> nodes;
    string root = "ROOT";
    bool computed = false;

public:
    CommandTree() {
        Node rootNode;
        rootNode.id = root;
        rootNode.parent = "";
        rootNode.depth = 0;
        rootNode.subtreeSize = 0;
        nodes[root] = rootNode;
    }

    bool addInsert(const string& personId, const string& commanderId) {
        if (nodes.find(personId) != nodes.end()) {
            return false;
        }

        if (nodes.find(commanderId) == nodes.end()) {
            return false;
        }

        Node newNode;
        newNode.id = personId;
        newNode.parent = commanderId;
        newNode.depth = 0;
        newNode.subtreeSize = 0;

        nodes[personId] = newNode;
        nodes[commanderId].children.push_back(personId);
        computed = false;

        return true;
    }

    void computeSizesAndDepths() {
        struct StackFrame {
            string nodeId;
            enum Phase { ENTER, EXIT } phase;
        };

        stack<StackFrame> stk;
        stk.push({root, StackFrame::ENTER});

        unordered_map<string, bool> visited;

        while (!stk.empty()) {
            StackFrame current = stk.top();
            stk.pop();

            if (current.phase == StackFrame::ENTER) {
                if (visited[current.nodeId]) continue;
                visited[current.nodeId] = true;

                Node& node = nodes[current.nodeId];

                if (!node.parent.empty()) {
                    node.depth = nodes[node.parent].depth + 1;
                }

                stk.push({current.nodeId, StackFrame::EXIT});

                for (int i = node.children.size() - 1; i >= 0; i--) {
                    stk.push({node.children[i], StackFrame::ENTER});
                }
            } else {
                Node& node = nodes[current.nodeId];
                int totalSize = 0;

                for (const string& childId : node.children) {
                    totalSize += 1 + nodes[childId].subtreeSize;
                }

                node.subtreeSize = totalSize;
            }
        }

        computed = true;
    }

    int query(const string& personId) {
        if (!computed) {
            computeSizesAndDepths();
        }

        if (nodes.find(personId) == nodes.end()) {
            return -1;
        }

        return nodes[personId].subtreeSize;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    string firstLine;
    getline(cin, firstLine);

    CommandTree tree;
    bool firstLineIsNumber = true;

    for (char c : firstLine) {
        if (!isdigit(c) && !isspace(c)) {
            firstLineIsNumber = false;
            break;
        }
    }

    vector<string> allLines;
    if (firstLineIsNumber && !firstLine.empty()) {
        n = stoi(firstLine);
    } else if (!firstLine.empty()) {
        allLines.push_back(firstLine);
    }

    string line;
    while (getline(cin, line)) {
        if (!line.empty()) {
            allLines.push_back(line);
        }
    }

    for (const string& cmdLine : allLines) {
        if (cmdLine.empty()) continue;

        size_t pos = cmdLine.find(' ');
        if (pos == string::npos) continue;

        string command = cmdLine.substr(0, pos);
        string rest = cmdLine.substr(pos + 1);

        if (command == "INSERT") {
            size_t spacePos = rest.find(' ');
            if (spacePos == string::npos) continue;

            string personId = rest.substr(0, spacePos);
            string commanderId = rest.substr(spacePos + 1);

            tree.addInsert(personId, commanderId);
        } else if (command == "QUERY") {
            string personId = rest;

            int result = tree.query(personId);
            if (result >= 0) {
                cout << result << "\n";
            }
        }
    }

    return 0;
}
