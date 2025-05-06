#include <iostream>     // For input and output
#include <vector>       // For using dynamic arrays (vectors)
#include <string>       // For using string data type
using namespace std;

// TreeNode class to represent each node in the tree (Chapter, Section, Subsection)
class TreeNode {
public:
    string name;                   // Name of the node (e.g., "Chapter: Trees")
    vector<TreeNode*> children;   // List of child nodes (subsections of a section, etc.)

    // Constructor to initialize a node with its name
    TreeNode(string name) {
        this->name = name;
    }

    // Method to add a child to this node
    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    // Method to print the tree structure with proper indentation
    void printTree(int level = 0) {
        for (int i = 0; i < level; ++i)
            cout << "  ";                  // Indentation for hierarchy
        cout << "- " << name << endl;     // Print current node
        for (TreeNode* child : children)  // Recursively print all children
            child->printTree(level + 1);
    }
};

int main() {
    // Create the root node for the book
    TreeNode* book = new TreeNode("Book: Data Structures");

    int chapters;
    cout << "Enter number of chapters: ";
    cin >> chapters;
    cin.ignore();  // Clear leftover newline from input buffer

    // Loop through each chapter
    for (int i = 0; i < chapters; ++i) {
        string chapterName;
        cout << "Enter name of Chapter " << i + 1 << ": ";
        getline(cin, chapterName);  // Read full line including spaces

        // Create a chapter node
        TreeNode* chapter = new TreeNode("Chapter: " + chapterName);

        int sections;
        cout << "Enter number of sections in " << chapterName << ": ";
        cin >> sections;
        cin.ignore();  // Clear buffer

        // Loop through each section in the chapter
        for (int j = 0; j < sections; ++j) {
            string sectionName;
            cout << "Enter name of Section " << j + 1 << ": ";
            getline(cin, sectionName);  // Read full line

            // Create section node
            TreeNode* section = new TreeNode("Section: " + sectionName);

            int subsections;
            cout << "Enter number of subsections in " << sectionName << ": ";
            cin >> subsections;
            cin.ignore();  // Clear buffer

            // Loop through each subsection in the section
            for (int k = 0; k < subsections; ++k) {
                string subsectionName;
                cout << "Enter name of Subsection " << k + 1 << ": ";
                getline(cin, subsectionName);  // Read full line

                // Create subsection node and add to section
                TreeNode* subsection = new TreeNode("Subsection: " + subsectionName);
                section->addChild(subsection);
            }

            // Add section to chapter
            chapter->addChild(section);
        }

        // Add chapter to book
        book->addChild(chapter);
    }

    // Print the entire tree
    cout << "\nBook Structure:\n";
    book->printTree();  // Print recursively with indentation

    return 0;
}

