# VCS - Lightweight Version Control System

VCS is a simple, lightweight version control system written in C++. It mimics basic features of Git, allowing you to create and manage commits, track document changes, and handle repositories in a modular way. This project is designed for educational purposes to demonstrate how a version control system can be built from the ground up.

## 🚀 Features

- Basic commit and repository management
- Document state tracking
- Exception handling for robust operations
- Helper utilities for streamlined I/O
- Lightweight and modular C++ design

## 📁 Project Structure

```
VCS-main/
├── Commit.cpp / .hpp
├── Document.cpp / .hpp
├── Repository.hpp
├── Exception.hpp
├── iostream_helper_functions.cpp / .hpp
├── main.cpp
├── test_system/
│   ├── test.cpp
│   └── cached_data
└── README.md
```

## 🛠️ Build Instructions

Ensure you have a C++17-compatible compiler installed (e.g., g++).

```bash
g++ -std=c++17 -o vcs main.cpp Commit.cpp Document.cpp iostream_helper_functions.cpp
./vcs
```

## 🧪 Running Tests

To run the test suite:

```bash
g++ -std=c++17 -o test test_system/test.cpp Commit.cpp Document.cpp iostream_helper_functions.cpp
./test
```

## 📚 Dependencies

- Standard C++ libraries only
- No third-party dependencies

## 👨‍💻 Author

Developed by [Your Name Here]. Contributions welcome!

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 🙋 About Me

Hi! I'm a passionate C++ developer interested in backend programming. This project showcases my love for clean architecture and strategic logic. If you'd like to collaborate, feel free to reach out!

[🔗 LinkedIn](https://www.linkedin.com/in/anton-burtasenkov-1a44492b1/) | [📧 Email](mailto:aburtasenkov@gmail.com)

---
