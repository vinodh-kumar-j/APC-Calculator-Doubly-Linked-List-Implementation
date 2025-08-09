# 🧮 APC Calculator – Doubly Linked List Implementation

**Author:** VINODH KUMAR J  
**Project Name:** APC Calculator

---

## 🗂️ Project Overview

**APC Calculator** is a C-based command-line tool that performs **arithmetic operations on arbitrarily large integers** using a **doubly linked list** to store each digit.  
It supports addition, subtraction, multiplication, and division (with remainder) for numbers far exceeding standard integer limits.

---

## ✅ Features

- **Handles very large integers** beyond the range of built-in C data types.
- **Supports**:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`x`)
  - Division (`/`) – Displays **quotient** and **remainder**.
- **Validates input** to reject non-digit characters.
- **Preserves sign** for subtraction results.

---

## 📁 File Structure

```
.
├── main.c         # CLI interface and main driver
├── calc.h         # Structs and function prototypes
├── dll_utils.c    # Doubly linked list utilities
├── operation.c    # Arithmetic operations
├── Makefile       # Build automation
├── README_APC_Calculator.md  # This README
```

---

## ⚙️ Build Instructions

Compile using GCC:

```bash
gcc main.c dll_utils.c operation.c -o calc
```

Or use the provided `Makefile`:

```bash
make
```

---

## 🚀 Usage

```bash
./calc <operand1> <operator> <operand2>
```

### Examples:

```bash
./calc 12345 + 6789
./calc 987654321 x 123456789
./calc 1000 / 7
```

---

## 🧠 Example Output

```bash
$ ./calc 12345 + 6789
Result: 19134

$ ./calc 1000 / 7
Quotient: 142
Remainder: 6
```

---

## 📌 Notes

- Multiplication operator should be lowercase `x` (not `*`).
- Division prints both **quotient** and **remainder**.
- Input must contain **only digits** (no signs or decimal points).

---

## ✍️ Author

**VINODH KUMAR J**  
*Project: APC Calculator – Doubly Linked List*

---

## 📜 License

MIT License – Free to use, modify, and distribute.
