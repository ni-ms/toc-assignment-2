#include <stdio.h>
#include <stdlib.h>

// Define a node in the parse tree.
typedef struct Node {
    char* value;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node with the given value.
Node* create_node(char* value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Add a left child to the given parent node.
void add_left_child(Node* parent, Node* child) {
    parent->left = child;
}

// Add a right child to the given parent node.
void add_right_child(Node* parent, Node* child) {
    parent->right = child;
}

// Print the parse tree in a human-readable form.
void print_parse_tree(Node* root, int indent) {
    if (root == NULL) return;

    // Print the current node's value.
    for (int i = 0; i < indent; i++) printf(" ");
    printf("%s\n", root->value);

    // Print the left and right subtrees.
    print_parse_tree(root->left, indent + 2);
    print_parse_tree(root->right, indent + 2);
}

int main() {
    // Create a parse tree for the expression "1 + 2 * 3".
    Node* one = create_node("1");
    Node* two = create_node("2");
    Node* three = create_node("3");
    Node* plus = create_node("+");
    Node* times = create_node("*");

    add_left_child(plus, one);
    add_right_child(plus, times);
    add_left_child(times, two);
    add_right_child(times, three);

    // Print the parse tree.
    print_parse_tree(plus, 0);

    return 0;
}
