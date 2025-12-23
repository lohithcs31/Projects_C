Name : Lohith C S
Date : 22/12/2025
Title: LSB Image Steganography

Description:

Developed an image steganography application using the Least Significant Bit (LSB) technique to securely hide textual
data inside digital images. The project embeds secret messages into pixel data without causing perceptible changes to the original image.
Implemented encoding and decoding mechanisms to ensure accurate data retrieval while preserving image quality. 
Focused on data security, lossless embedding, and efficient memory handling.

Key Highlights:

Implemented LSB-based data hiding in RGB images

Ensured minimal visual distortion and lossless message recovery

Designed separate encoding and decoding modules

Verified robustness using multiple image formats and message sizes

gcc *.c       
lohith_cs@DESKTOP-HF5HL9B:/mnt/d/Lohith/Embedded_Systems_Fundamentals/Emertxe/Advanced_C/C_Fundamentals/C-Project-1/C-Project-1/Steganography$ ./a.out -e beautiful.bmp secret.txt stego.bmp 
Source image file name : beautiful.bmp
Secret file name : secret.txt
Secret file extension size is 4
Secret file extension is .txt
Output image file name : stego.bmp
Read and validate encode arguments operation completed successfully!!
Open file operation completed successfully!
width = 1024
height = 768
Source image capacity is proper!
Source image header copied successfully!
Magic string encoded successfully!
Encoding operation completed successfully!
lohith_cs@DESKTOP-HF5HL9B:/mnt/d/Lohith/Embedded_Systems_Fundamentals/Emertxe/Advanced_C/C_Fundamentals/C-Project-1/C-Project-1/Steganography$ ./a.out -d stego.bmp decode
go.bmp decode
Encoded image file name : stego.bmp
File name without extension : decode
Read and validate decode arguments operation completed successfully!!
Decoded magic string is same : #*
Secret file extension size : 4
Secret file extension : .txt
Secret file name with extension : decode.txt
Secret file size : 25
Secret data : My password is SECRET ;)

Decoding operation completed successfully!
