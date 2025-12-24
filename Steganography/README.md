# 🕵️‍♂️ LSB Image Steganography (C)

This project implements **Least Significant Bit (LSB) image steganography** in **C**, allowing you to **hide and retrieve secret messages** inside bitmap images. LSB steganography works by modifying the least significant bit of image pixels to store hidden data, which keeps the visual changes imperceptible to the human eye. :contentReference[oaicite:0]{index=0}

---

## 📌 Table of Contents

- [Project Overview](#project-overview)  
- [Features](#features)  
- [How It Works](#how-it-works)  
- [Usage](#usage)  
- [Build & Compile](#build--compile)  
- [Example](#example)  
- [Folder Structure](#folder-structure)  
- [Contributing](#contributing)  
- [License](#license)

---

## 📙 Project Overview

This repository contains a C implementation of an image steganography tool using the **Least Significant Bit (LSB)** technique:

- **Encode** – Embed a secret message into a BMP image.  
- **Decode** – Extract a previously hidden message from the stego image.

The program demonstrates fundamental **bitwise operations**, **file handling**, and **image data manipulation** in C.

---

## ⭐ Features

✔ Hide secret text inside a bitmap image  
✔ Extract hidden message from a stego image  
✔ Minimal visual distortion of the original image  
✔ Simple command-line based interface

---

## 🧠 How It Works

Steganography is the practice of hiding data within another file, in this case, an image. The **LSB algorithm** replaces the least significant bit of each pixel’s binary value with bits from the message — this change is so small that it’s nearly impossible to detect visually. :contentReference[oaicite:1]{index=1}

**Steps:**
1. Read the input image (`.bmp`) pixel data  
2. Convert the secret text into a binary bit stream  
3. Embed bits of the message into the least significant bits of pixel bytes  
4. Save the modified image as the **stego image**  
5. For decoding, read LSBs and reconstruct the hidden text

---

## 🚀 Usage

**Encode (Hide):**

```bash
./stego encode <cover_image.bmp> <secret_message.txt> <output_image.bmp>
