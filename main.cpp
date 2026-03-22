#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class TextEditor {
private:
    string fileName; // To store the file name
    string content[1000]; // Fixed-size array to store text content
    int lineCount; // To track the number of lines in the content

public:
    TextEditor() {
        fileName = "";
        lineCount = 0;
    }

    void createFile() {
        cout << "Enter the file name to create: ";
        cin >> fileName;
        ofstream file(fileName);
        if (file) {
            cout << "File created successfully: " << fileName << endl;
        } else {
            cerr << "Error: Unable to create file." << endl;
        }
        file.close();
    }

    void writeFile() {
        if (fileName.empty()) {
            cout << "No file is open. Use the create/open option first.\n";
            return;
        }

        cout << "Enter text (type 'END' to finish):" << endl;
        string line;
        cin.ignore();
        while (getline(cin, line) && line != "END") {
            if (lineCount < 1000) {
                content[lineCount++] = line;
            } else {
                cout << "Maximum file size reached!" << endl;
                break;
            }
        }

        cout << "Content added to memory. Use 'Save File' to save it.\n";
    }

    void openFile() {
        cout << "Enter the file name to open: ";
        cin >> fileName;

        ifstream file(fileName);
        if (!file) {
            cerr << "Error: File not found or unable to open." << endl;
            return;
        }

        lineCount = 0;
        string line;
        while (getline(file, line) && lineCount < 1000) {
            content[lineCount++] = line;
        }
        file.close();
        cout << "File opened successfully: " << fileName << endl;
    }

    void saveFile() {
        if (fileName.empty()) {
            cout << "No file is open. Use the create/open option first.\n";
            return;
        }

        ofstream file(fileName);
        if (!file) {
            cerr << "Error: Unable to save the file." << endl;
            return;
        }

        for (int i = 0; i < lineCount; i++) {
            file << content[i] << endl;
        }
        file.close();
        cout << "File saved successfully: " << fileName << endl;
    }

    void searchText() {
        if (lineCount == 0) {
            cout << "No content available. Use 'Write File' or 'Open File' first.\n";
            return;
        }

        cout << "Enter the text to search: ";
        string searchText;
        cin.ignore();
        getline(cin, searchText);

        bool found = false;
        for (int i = 0; i < lineCount; i++) {
            if (content[i].find(searchText) != string::npos) {
                cout << "Found at line " << i + 1 << ": " << content[i] << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Text not found.\n";
        }
    }

    void printContent() {
        if (lineCount == 0) {
            cout << "No content available. Use 'Write File' or 'Open File' first.\n";
            return;
        }

        cout << "File Content:" << endl;
        for (int i = 0; i < lineCount; i++) {
            cout << i + 1 << ": " << content[i] << endl;
        }
    }

    void deleteText() {
        if (lineCount == 0) {
            cout << "No content available to delete.\n";
            return;
        }

        cout << "Enter the line number to delete (1 to " << lineCount << "): ";
        int lineNum;
        cin >> lineNum;

        if (lineNum < 1 || lineNum > lineCount) {
            cout << "Invalid line number.\n";
            return;
        }

        for (int i = lineNum - 1; i < lineCount - 1; i++) {
            content[i] = content[i + 1];
        }
        lineCount--;
        cout << "Line " << lineNum << " deleted successfully.\n";
    }
};

int main() {
    TextEditor editor;
    int choice;

    while (true) {
        cout << "\n--- Text Editor ---\n";
        cout << "1. Create File\n";
        cout << "2. Write File\n";
        cout << "3. Open File\n";
        cout << "4. Save File\n";
        cout << "5. Search Text\n";
        cout << "6. Print Content\n";
        cout << "7. Delete Text\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                editor.createFile();
                break;
            case 2:
                editor.writeFile();
                break;
            case 3:
                editor.openFile();
                break;
            case 4:
                editor.saveFile();
                break;
            case 5:
                editor.searchText();
                break;
            case 6:
                editor.printContent();
                break;
            case 7:
                editor.deleteText();
                break;
            case 8:
                cout << "Exiting the Text Editor. Goodbye!\n";
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
