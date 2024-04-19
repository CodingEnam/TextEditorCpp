# TextEditorCpp
This Text Editor is created using two very fundamental data structures: Linked Lists and Stacks. Feel free to update the features and modify the project for a better version.

#Overview
#So, what exactly is this project all about?
#Well, we’ve all used text editors like Notepad, Visual Studio Code, or Sublime Text. They allow us to create, edit, and manipulate text files.
#In this project, I’ve built a simplified version of a text editor using two fundamental data structures: Linked Lists and Stacks.
#Key Features
#Linked Lists for Text Lines
#Each line of text is represented as a node in a linked list.
#We can efficiently insert, delete, and navigate through lines using pointers.
#Linked lists allow us to handle dynamic text length without wasting memory.
#Stacks for Undo/Redo Operations
#Stacks are essential for maintaining the undo and redo functionality.
#When a user modifies the text (e.g., adds, deletes, or edits a line), we push the current state onto the undo stack.
#If the user wants to undo, we pop from the undo stack and push onto the redo stack.
#Redo works similarly but in reverse.
#Basic Text Editing Commands
#Our text editor supports common commands:
#Insert: Add a new line at the cursor position.
#Delete: Remove the line at the cursor position.
#Move Up and Move Down: Navigate through lines.
#Undo and Redo: Revert or reapply changes.
