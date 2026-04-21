# Contact Book (C++ Console Application)

## Overview

This project is a **Contact Book system** built using C++. It allows users to manage contacts efficiently through a console-based interface.

The application supports full CRUD operations (Create, Read, Update, Delete) along with input validation and structured data handling.

---

## Features

* Add new contacts
* Display all contacts in a formatted table
* Search contacts (by name or phone)
* Update existing contact details
* Delete contacts with confirmation
* Categorize contacts:

  * Friend
  * Family
  * Work
  * Others

---

## Concepts Used

* **Enums** for menu systems and categories
* **Structs** for modeling contact data
* **Vectors** for dynamic storage
* **Input validation** and error handling
* **Modular functions** for clean architecture
* **Algorithm library (`std::transform`)** for case-insensitive comparisons

---

## First Use of Custom Library

This project introduces my **first usage of a custom-built library:**

### `myLib.h`

Used for:

* Validated numeric input within ranges
* Cleaner and reusable input handling

This marks an important step toward:
Code reuse
Separation of concerns
Building scalable systems

---

## Sample Functionalities

### Add Contact

* Name input
* Phone validation (10 digits, starts with 0)
* Email validation (basic format check)
* Category selection

### Search Contact

* By name (case-insensitive)
* By phone number

### Update Contact

* Modify:

  * Name
  * Phone
  * Email
  * Category

---

## Project Structure

```
ContactBook-Project/
│── main.cpp
│── myLib.h
```

---

## Future Improvements

* File handling (save/load contacts)
* Database integration
* Better validation (regex)
* Transition to full OOP class-based design
* GUI or web interface

---

## Author

**Mohammed Hejjam**

---

## License

This project is for learning purposes and open for improvements.

---

## How to Run

### Compile:
```bash
g++ -std=c++11 main.cpp -o contact
./contact
