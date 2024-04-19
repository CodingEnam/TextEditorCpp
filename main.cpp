#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <windows.h>


bool fileExists(const std::string& fileName) {
	DWORD attributes = GetFileAttributesA(fileName.c_str());
	return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}
class TextNode {
public:
    std::string text;
    TextNode* next;

    TextNode(const std::string& content) : text(content), next(nullptr) {}
};

class TextEditor {
private:
    TextNode* first;
    std::stack<TextNode*> undoStack;
    std::stack<TextNode*> redoStack;

public:
    TextEditor() : first(nullptr) {}

    void showText() {
        TextNode* current = first;
        int lineNumber = 0;
        while (current) {
            std::cout << "   > " << current->text << std::endl;
            current = current->next;
            lineNumber++;
        }
    }

    void insertLine(const std::string& line) {
        saveState();
        TextNode* newNode = new TextNode(line);
        newNode->next = first;
        first = newNode;
    }

    void deleteLine(int lineNumber) {
        saveState();
        if (lineNumber == 1) {
            TextNode* temp = first;
            first = first->next;
            delete temp;
        } else {
            TextNode* current = first;
            for (int i = 1; i < lineNumber - 1 && current; ++i) {
                current = current->next;
            }
            if (current && current->next) {
                TextNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
    }

    void modifyLine(int lineNumber, const std::string& newLine) {
        saveState();
        TextNode* current = first;
        for (int i = 1; i < lineNumber && current; ++i) {
            current = current->next;
        }
        if (current) {
            current->text = newLine;
        }
    }

    void searchAndReplace(const std::string& searchStr, const std::string& replaceStr) {
        saveState();
        TextNode* current = first;
        while (current) {
            size_t pos = current->text.find(searchStr);
            while (pos != std::string::npos) {
                current->text.replace(pos, searchStr.length(), replaceStr);
                pos = current->text.find(searchStr, pos + replaceStr.length());
            }
            current = current->next;
        }
    }

    void undo() {
    	
        if (!undoStack.empty()) {
            redoStack.push(copyState());
            first = undoStack.top();
            undoStack.pop();
            std::cout<<"Undoing Completed!\nYour editor now looks like:\n";
            showText();
        } else {
            std::cerr << "Error: Nothing to undo." << std::endl;
        }
    }

    void redo() {
    	
        if (!redoStack.empty()) {
            undoStack.push(copyState());
            first = redoStack.top();
            redoStack.pop();
            std::cout<<"Redoing Completed!\nYour editor now looks like:\n";
            showText();
        } else {
            std::cerr << "Error: Nothing to redo." << std::endl;
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        TextNode* current = first;
        while (current) {
            outputFile << current->text << "\n";
            current = current->next;
        }
        outputFile.close();
    }

    void loadFromFile(const std::string& filename) {
        saveState();
        clear();
        std::ifstream inputFile(filename);
        std::string line;
        while (std::getline(inputFile, line)) {
            insertLine(line);
        }
        inputFile.close();
    }

private:
    void saveState() {
        undoStack.push(copyState());
        while (!redoStack.empty()) {
            delete redoStack.top();
            redoStack.pop();
        }
    }

    TextNode* copyState() {
        TextNode* current = first;
        TextNode* newFirst = nullptr;
        TextNode* tail = nullptr;

        while (current) {
            TextNode* newNode = new TextNode(current->text);
            if (tail) {
                tail->next = newNode;
                tail = tail->next;
            } else {
                newFirst = newNode;
                tail = newFirst;
            }
            current = current->next;
        }
        return newFirst;
    }

    void clear() {
        while (first) {
            TextNode* temp = first;
            first = first->next;
            delete temp;
        }
    }
};

int main() {
    TextEditor editor;
    int choice;
	std::cout<<"### ###  ### ###  ####       ####   ###  ##  ##  ###           #### ##  ### ###   ## ##   ###  ##\n"  
					" ##  ##   ##  ##   ##         ##      ## ##  ##   ##           # ## ##   ##  ##  ##   ##   ##  ##\n"  
					"  ##  ##   ##       ##         ##     # ## #  ##   ##             ##      ##      ##        ##  ##\n"  
					"   ##  ##   ## ##    ##         ##     ## ##   ##   ##             ##      ## ##   ##        ## ###\n" 
					"    ### ##   ##       ##         ##     ##  ##  ##   ##             ##      ##      ##        ##  ##\n" 
					"     ###     ##  ##   ##  ##     ##     ##  ##  ##   ##             ##      ##  ##  ##   ##   ##  ##\n" 
					"      ##    ### ###  ### ###    ####   ###  ##   ## ##             ####    ### ###   ## ##   ###  ##\n";
		std::cout<<"-------------------------------------------------------------------------------------------------------\n";
		std::cout<<"|                             Created by: Enamullah Mehrabi                                           |\n";
		std::cout<<"-------------------------------------------------------------------------------------------------------\n";
		std::cout<<"";
		std::cout<<"-------------------------------------------------------------------------------------------------------\n";
		std::cout<<"|                                 Instructor: Prof. Dr. Umut Tosun                                    |\n";
		std::cout<<"-------------------------------------------------------------------------------------------------------\n";
    do {
    	
        std::cout << "\n------ Text Editor Menu ------\n";
        std::cout << "1. Insert Line\n";
        std::cout << "2. Display Text\n";
        std::cout << "3. Undo\n";
        std::cout << "4. Redo\n";
        std::cout << "5. Search and Replace\n";
        std::cout << "6. Save to File\n";
        std::cout << "7. Load from File\n";
        std::cout << "0. Exit\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Ignore the newline character in the buffer

        switch (choice) {
            case 1: {
                std::cout << "Enter line to insert: ";
                std::string line;
                std::getline(std::cin, line);
                editor.insertLine(line);
                std::cout<< "\nThe line: '"<<line<<"' was added to the Editor.\n";
                break;
            }
            case 2:
                std::cout << "Displaying Text:\n";
                editor.showText();
                break;
            case 3:
                std::cout << "Undoing...\n";
                editor.undo();
                
                break;
            case 4:
                std::cout << "Redoing...\n";
                editor.redo();
                
                break;
            case 5: {
                std::cout << "Enter search string: ";
                std::string searchStr;
                std::getline(std::cin, searchStr);
                std::cout << "Enter replace string: ";
                std::string replaceStr;
                std::getline(std::cin, replaceStr);
                editor.searchAndReplace(searchStr, replaceStr);
                std::cout<<"The line: '"<<searchStr<<"' was replaced with '"<<replaceStr<<"'.";
                std::cout<<"Your editor now looks like:\n";
                editor.showText();
                break;
            }
            case 6: {
                std::cout << "Enter file name to save: ";
                std::string filename;
                std::getline(std::cin, filename);
                editor.saveToFile(filename);
                break;
            }
            case 7: {
                std::cout << "Enter file name to load: ";
                std::string fileName;
                std::getline(std::cin, fileName);
                if (fileExists(fileName)){
                	editor.loadFromFile(fileName);
                	std::cout<<"The content was loaded successfully!\n";
                	editor.showText();
				}else{
					std::cout<<"Error 404: A file with such name does not exist!";
				}
                
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

