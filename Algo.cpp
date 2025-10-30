// File: geass_command_tree.cpp
// Compile: g++ -std=c++17 geass_command_tree.cpp -o geass_command_tree
// Run: ./geass_command_tree


#include <bits/stdc++.h>
using namespace std;


// Tree node representing a commanded person and their children
struct TreeNode {
string person;
string command;
vector<TreeNode*> children;
TreeNode(const string &p, const string &c): person(p), command(c) {}
};


// Influence graph type: person -> list of people they influence
using InfluenceGraph = unordered_map<string, vector<string>>;
// Simple rule to derive a new command for an influenced person
// (In a richer simulation this could depend on roles, probabilities, or other logic.)
string derive_command_for(const string &from_person, const string &base_command, const string &target_person) {
// For demo purposes we append the influencer's name as provenance.
return base_command + " (via " + from_person + ")";
}


// Recursively build the command tree. visited prevents cycles and double-commanding.
void propagate_command(const InfluenceGraph &G,
const string &current_person,
const string &command_for_current,
unordered_set<string> &visited,
TreeNode *parent_node) {
// Mark visited
visited.insert(current_person);

// For each influenced person
auto it = G.find(current_person);
if (it == G.end()) return; // no outgoing influences


for (const string &influenced : it->second) {
if (visited.count(influenced)) continue; // already commanded earlier


// Derive the command that will be handed down
string child_command = derive_command_for(current_person, command_for_current, influenced);


// Create child tree node and attach
TreeNode *child = new TreeNode(influenced, child_command);
parent_node->children.push_back(child);


// Recurse from that child
propagate_command(G, influenced, child_command, visited, child);
}


// Utility to print the tree with indentation
void print_tree(const TreeNode *node, int depth = 0) {
if (!node) return;
string indent(depth * 2, ' ');
cout << indent << "- " << node->person << ": " << node->command << "\n";
for (const TreeNode *ch : node->children) print_tree(ch, depth + 1);
}


// Clean up allocated nodes (post-order)
void free_tree(TreeNode *node) {
if (!node) return;
for (TreeNode *ch : node->children) free_tree(ch);
delete node;
}


int main() {
// 1) Build a sample influence graph
InfluenceGraph G;


// Example social/influence network. Edges mean "A influences B".
G["Lelouch"] = {"Suzaku", "Kallen", "Schneizel"};
G["Suzaku"] = {"ArmyA", "SoldierX"};
G["Kallen"] = {"BlackKnights", "RebelCell1"};
G["Schneizel"] = {"Minister1", "Minister2"};
G["ArmyA"] = {"Civilians"};
G["BlackKnights"] = {"RebelCell1", "RebelCell2"};
G["RebelCell1"] = {"Civilians"};
// Some nodes with no outgoing edges are omitted or empty.


// 2) Prepare for propagation
string initial_target = "Suzaku"; // the person Lelouch uses Geass on
string initial_command = "Follow my order: dismantle the chain of command";


// Root of the printed tree represents the root issuer (Lelouch) for clarity
TreeNode *root = new TreeNode("Lelouch", "(Root issuer)");


// Create the first child representing the commanded target and begin propagation
TreeNode *first = new TreeNode(initial_target, initial_command);
root->children.push_back(first);


unordered_set<string> visited;
// Mark root and the initial target as visited (Lelouch isn't 'commanded' but avoids cycles)
visited.insert("Lelouch");
visited.insert(initial_target);

// Propagate from the initial target
propagate_command(G, initial_target, initial_command, visited, first);


// 3) Print the resulting command tree
cout << "Geass Command Tree:\n";
print_tree(root);


// 4) Cleanup
free_tree(root);


return 0;
}}