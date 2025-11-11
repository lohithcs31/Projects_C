# 🗂️ Address Book in C

A **menu-driven Address Book application** written in C that allows users to manage their personal contact list efficiently.  
It demonstrates a strong grasp of core C programming concepts such as **conditional logic, loops, arrays, functions, pointers, strings, and structures**.

---

## 🚀 Features

The Address Book provides the following functionalities:

1. **Create Contact** – Add a new contact by entering a name, phone number, and email address.  
2. **Search Contact** – Find a specific contact using their name.  
3. **Edit Contact** – Modify the details (name, phone, or email) of an existing contact.  
4. **Delete Contact** – Remove a contact from the list permanently.  
5. **List Contacts** – Display all saved contacts in a formatted list.  
6. **Save and Exit** – Save all contacts to a file for persistence across program runs.

---

## 🧠 Concepts Demonstrated

This project highlights an in-depth understanding of **C programming fundamentals**:

### 1. Basics (Conditional and Iterative Statements)
- Used `if-else`, `switch`, and looping constructs (`for`, `while`) for menu navigation and user input validation.
- Implemented control flows for search, add, delete, and edit operations.

### 2. Arrays
- Used arrays of structures to store multiple contact records.
- Managed fixed-size character arrays for storing names, phone numbers, and emails.

### 3. Functions
- The code is modularized into multiple functions like:
  - `createContact()`
  - `searchContact()`
  - `editContact()`
  - `deleteContact()`
  - `listContacts()`
  - `saveToFile()` / `loadFromFile()`
- Promotes code reusability and better readability.

### 4. Pointers
- Used pointers for dynamic data manipulation, structure references, and file operations.
- Demonstrated pointer arithmetic when iterating through arrays of contacts.

### 5. Strings
- Used standard C string functions like `strcpy()`, `strcmp()`, `strlen()`, and `strcat()` for managing textual data (name, phone, email).
- Implemented safe input handling using buffers and string validation.

### 6. Structures
- Defined a `struct Contact` that encapsulates all contact details:
  ```c
  struct Contact {
      char name[50];
      char phone[15];
      char email[50];
  };
🧩 How to Run

1. Clone this repository:
    
    git clone https://github.com/lohithcs31/Projects_C.git

2. Navigate to the project directory:
    
    cd Projects_C/AddressBook

3. Compile the program:
    
    gcc address_book.c -o address_book

4. Run the executable:
    
    ./address_book

🧰 Technologies Used

- Language: C
- Compiler: GCC
- IDE/Editor: Any C-compatible IDE (VS Code, Code::Blocks, etc.)

📖 Learning Outcomes

- By completing this project, I gained practical experience in:
- Structuring a C program into modular, reusable components.
- Applying fundamental C concepts to solve a real-world problem.
- Implementing data management and persistence using file handling.
- Debugging and improving code reliability.

🧑‍💻 Author

Lohith C S

GitHub: https://github.com/lohithcs31

⭐ Acknowledgements

This project was built to strengthen my understanding of core C programming and to apply key concepts such as data structures, file I/O, and modular design in a practical application.

