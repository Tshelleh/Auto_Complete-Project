📌 Overview A C++ implementation of an auto-complete system using the Trie data structure. This project provides real-time word suggestions as the user types, with multiple sorting options (frequency, length, lexicographical order). It supports dynamic dictionary updates, case insensitivity, and robust error handling.

✨ Features ✔ Prefix-based suggestions – Get word completions in real-time. ✔ Multiple sorting methods:

Frequency-based (most searched words first)

Shortest-first (BFS traversal)

Lexicographical order (DFS traversal) ✔ Dynamic dictionary management:

Add new words

Delete existing words

Auto-save changes to file ✔ Case-insensitive matching – Works with "Car", "CAR", or "car". ✔ Exact match highlighting – Bold or colorize exact matches. ✔ Error handling – Handles invalid inputs gracefully.

📂 Project Structure AutoComplete_Project/ ├── src/ # Source code

│ ├── Trie.cpp # Trie implementation

│ ├── Trie.h # Trie header

│ ├── AutoComplete.cpp # Core logic

│ ├── main.cpp # CLI interface

├── data/ # Dictionary files

│ └── dictionary.txt # Default word list

└── README.md # This file

Entering a Prefix Enter a prefix: ca Choose sorting method:

Frequency (default)

Shortest-first (BFS)

Lexicographical (DFS) => 2
Output: car cat care cart

Adding/Deleting Words Options:

Search suggestions

Add a word

Delete a word

2 Enter word to add: coffee "coffee" added successfully!

🔧 Extending the Project

GUI Integration: Use Qt or ImGui for a graphical interface.
Persistent Frequency Tracking: Store word frequencies in a file.
Multilingual Support: Extend for non-English characters.
🤝 Contributers

Gehad Ebrahim
Tassnim Shellah
Habiba Osama
Lina Hisham
Dalia Ahmed
Sondos Khalid
Sara Mohsen
⭐ Star this repo if you find it useful! 🔗 Share with others who might benefit!

🔍 Why Trie? The Trie data structure is ideal for auto-complete because: ✅ Fast prefix searches – O(L) where L is the length of the prefix. ✅ Memory-efficient – Shares common prefixes among words. ✅ Scalable – Handles large dictionaries efficiently.
