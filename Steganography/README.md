# 🕵️ LSB Image Steganography (C)

This project implements **Least Significant Bit (LSB) image steganography** in **C**, enabling both **encoding (hiding)** and **decoding (extracting)** of secret textual data inside bitmap images (`.bmp`).  
The technique ensures that the hidden information is imperceptible to the human eye while allowing accurate recovery of the original message.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Encoding Process](#encoding-process)
- [Decoding Process](#decoding-process)
- [How It Works](#how-it-works)
- [Build & Compile](#build--compile)
- [Usage](#usage)
- [Example](#example)
- [Folder Structure](#folder-structure)
- [Limitations](#limitations)
- [Future Enhancements](#future-enhancements)

---

## 📙 Overview

Steganography is the practice of hiding secret information within a carrier medium.  
This project uses the **Least Significant Bit (LSB)** technique to embed a secret text file into a bitmap image without noticeably altering its visual appearance.

The application supports:
- **Encoding**: Hide a secret message inside an image
- **Decoding**: Extract the hidden message from the stego image

---

## ⭐ Features

✔ Encode secret text inside a BMP image  
✔ Decode and retrieve the hidden message  
✔ No noticeable visual distortion  
✔ Lossless message extraction  
✔ Command-line based implementation  
✔ Uses low-level file I/O and bitwise operations in C  

---

## 🔐 Encoding Process

1. Read the **source BMP image**
2. Read the **secret text file**
3. Convert secret data into binary form
4. Embed each bit of the secret data into the **LSB of image pixel bytes**
5. Store metadata (such as secret size or delimiter)
6. Generate the **stego image** as output

The original image quality remains visually unchanged after encoding.

---

## 🔓 Decoding Process

1. Read the **stego image**
2. Extract the **LSBs from pixel data**
3. Reconstruct the binary secret message
4. Detect message termination using stored metadata
5. Write the recovered message into an output text file

The decoding process accurately retrieves the original hidden data.

---

## 🧠 How It Works

In an 8-bit pixel value:
```

Original byte : 10110010
Modified byte : 10110011

````

Only the **least significant bit** is altered to store one bit of secret data.  
Because this change is extremely small, it is invisible to the human eye.

---

## 🛠 Build & Compile

Ensure `gcc` is installed.

```bash
gcc -Wall *.c -o stego
````

This generates the executable `stego`.

---

## 🚀 Usage

### Encode (Hide Data)

```bash
./stego encode <input_image.bmp> <secret_text.txt> <output_image.bmp>
```

### Decode (Extract Data)

```bash
./stego decode <stego_image.bmp> <output_text>
```

---

## 📄 Example

```bash
# Encode
./stego encode original.bmp secret.txt stego.bmp

# Decode
./stego decode stego.bmp extracted_secret.txt
```

After encoding, `stego.bmp` appears visually identical to `original.bmp` but contains hidden data.

---

## 🗂 Folder Structure

```
Steganography/
├── encode.c
├── decode.c
├── main.c
├── common.h
├── types.h
├── original.bmp
├── stego.bmp
├── secret.txt
├── README.md
```

---

## ⚠️ Limitations

* Works only with **BMP images**
* Supports only **text-based secrets**
* No encryption applied before embedding
* Image size limits maximum secret data size

---

## 🚀 Future Enhancements

* Add encryption (AES) before steganography
* Support PNG / JPEG formats
* Add password-based decoding
* Improve error handling and validation
* Add unit tests and logging

---

## 📌 Conclusion

This project demonstrates a practical implementation of LSB image steganography using C.
It highlights strong understanding of **bitwise manipulation**, **file handling**, and **low-level image processing**, making it well-suited for systems and embedded software roles.

