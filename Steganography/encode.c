#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
#include "common.h"
#include <stdlib.h>

/* Function Definitions */
unsigned int secret_file_extension_size = 0;
/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

//Function to copy 54 byte header from source image to destination
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    unsigned char temp[54];
    fseek(fptr_src_image,0,SEEK_SET);//check return value
    size_t read_header = fread(temp,sizeof(char),54,fptr_src_image);
    if(read_header!=54)
    {
        printf("Error!Could not fetch source image header\n");
        return e_failure;
    }
    size_t write_header = fwrite(temp,sizeof(char),54,fptr_dest_image);
    if(write_header!=54)
    {
        printf("Error!Could not write header into destination image\n");
        return e_failure;
    }
    return e_success;
}

//Function to encode magic string(char data -->2 bytes (hardcoded as "#*"))
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    if(encode_data_to_image((char*)magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Pass the arguments from the command line and check the argument count (if argc<4 || argc>5 --> invalid), copy relevant file names
//The structure address is also passed as an argument in order to store the file names passed by the user as command line argument
Status read_and_validate_encode_args(int argc, char *argv[], EncodeInfo *encInfo)
{
    if(argc<4||argc>5)
    {
        printf("Number of command line arguments is improper!!\n");
        return e_failure;
    }
    else
    {
        if((strstr(argv[2],".bmp"))!=NULL)
        {
            encInfo->src_image_fname = malloc(strlen(argv[2])+1);
            strcpy(encInfo->src_image_fname,argv[2]);
            printf("Source image file name : %s\n",encInfo->src_image_fname);
            if((strchr(argv[3],'.'))!=NULL)
            {
                int k=0;
                encInfo->secret_fname = malloc(strlen(argv[3])+1);
                strcpy(encInfo->secret_fname,argv[3]);
                printf("Secret file name : %s\n",encInfo->secret_fname);
                for(int i=0;encInfo->secret_fname[i]!='\0';i++)
                {
                    if(encInfo->secret_fname[i]=='.')
                    {
                        for(int j=i;encInfo->secret_fname[j]!='\0';j++)
                        {
                            encInfo->extn_secret_file[k++] = encInfo->secret_fname[j];
                        }
                        secret_file_extension_size = strlen(encInfo->extn_secret_file);//secret_file_extension_size = k;
                    }
                }
                printf("Secret file extension size is %d\n",secret_file_extension_size);
                printf("Secret file extension is %s\n",encInfo->extn_secret_file);
                if(argc==4)
                {
                    encInfo->stego_image_fname = malloc(strlen("stego.bmp")+1);
                    strcpy(encInfo->stego_image_fname,"stego.bmp");
                    printf("Output image file name : %s\n",encInfo->stego_image_fname);
                    return e_success;
                }
                else
                {
                    if((strstr(argv[2],".bmp"))!=NULL)
                    {
                        encInfo->stego_image_fname = malloc(strlen(argv[4])+1);
                        strcpy(encInfo->stego_image_fname,argv[4]);
                        printf("Output image file name : %s\n",encInfo->stego_image_fname);
                        return e_success;
                    }
                    else
                    {
                        return e_failure;
                    }
                }
            }
            else
            {
                return e_failure;
            }
        }
        else
        {
            return e_failure;
        }   
    }
}

//All operations related to encoding are handled by this function alone
Status do_encoding(EncodeInfo *encInfo)
{
    if(open_files(encInfo)==e_success)
    {
        printf("Open file operation completed successfully!\n");
        if(check_capacity(encInfo)==e_success)
        {
            printf("Source image capacity is proper!\n");
            if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
            {
                printf("Source image header copied successfully!\n");
                if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)//Encode magic string
                {
                    printf("Magic string encoded successfully!\n");
                    if(encode_secret_extn_size(secret_file_extension_size, encInfo)==e_success)//Encode secret file extension size (integer)
                    {
                        if(encode_secret_file_extn(encInfo->extn_secret_file, encInfo)==e_success)//Encode  secret file extension
                        {
                            if(encode_secret_file_size(encInfo->size_secret_file, encInfo)==e_success)//Encode secret file size
                            {
                                if(encode_secret_file_data(encInfo)==e_success)//Encode secret file data
                                {
                                    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image)== e_success)//Copy remaining data
                                    {
                                        return e_success;
                                    }
                                    else
                                    {
                                        printf("Could not copy remaining source image data!\n");
                                        return e_failure;
                                    }
                                }
                                else
                                {
                                    printf("Secret file data encoding failed!\n");
                                    return e_failure;
                                }
                            }
                            else
                            {
                                printf("Secret file size encoding failed!\n");
                                return e_failure;
                            }
                        }
                        else
                        {
                            printf("Secret file extension encoding failed!\n");
                            return e_failure;
                        }
                    }
                    else
                    {
                        printf("Secret file extension size encoding failed!\n");
                        return e_failure;
                    }
                }
                else
                {
                    printf("Magic string encoding failed!!\n");
                    return e_failure;
                }
            }
            else
            {
                printf("Could not copy image header!\n");
                return e_failure;
            }
        }
        else
        {
            printf("Source image capacity is improper!\n");
            return e_failure;
        }
    }
    else
    {
        printf("Open file operation failed!!\n");
        return e_failure;
    }
}


//This function checks whether the output image can hold both input image and the secret size in bytes
Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image); //returns image capacity -->store it in the structure member
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret); //this function returns the size of the secret file
    if(encInfo->image_capacity>(54/*header*/+16/*magic string*/+32/*file size - int*/+(secret_file_extension_size*8)+(encInfo->size_secret_file * 8)))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//This function returns the file size of the secret file
uint get_file_size(FILE *fptr)
{
    long int size;
    fseek(fptr,0,SEEK_END);
    size = ftell(fptr);
    return (uint)size;
}

//This file encodes 1 bit of char data(magic string, secret file extn, secret file data) to the LSB of the byte(image buffer)
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    //get MSB of the data parameter
    //Clear LSB of image_buffer[i]
    //replace the bit in the LSB (set operation)
    int k=0;
    int count=0;//count variable to keep track of encode count
    for(int pos=7;pos>=0;pos--)
    {
        int res = (data & (1<<pos))>>pos;
        image_buffer[k] = image_buffer[k] & (~1);
        image_buffer[k] = image_buffer[k] | res;
        k++;
        count++;
    }
    if(count==8)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//This function encodes 1 bit of the integer data(secret file extn size, secret file size) to the LSB of the byte(image buffer)
Status encode_size_to_lsb(int data, char *image_buffer)
{
    //get MSB of the data parameter
    //Clear LSB of image_buffer[i]
    //replace the bit in the LSB (set operation)
    int k=0;
    int count=0;//count variable to keep track of encode count
    for(int pos=31;pos>=0;pos--)
    {
        int res = (data & (1<<pos))>>pos;
        image_buffer[k] = image_buffer[k] & (~1);
        image_buffer[k] = image_buffer[k] | res;
        k++;
        count++;
    }
    if(count==32)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Generic function to encode magic string, extension, and file data(secret characters in the file)
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[8];
    int count=0;
    for(int i=0;i<size;i++)
    {
        fread(buffer,sizeof(char),8,fptr_src_image);
        encode_byte_to_lsb(data[i], buffer);
        fwrite(buffer,sizeof(char),8,fptr_stego_image);
        count++;
    }
    if(count==size)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Function to encode the secret file extension size(integer)
Status encode_secret_extn_size(long extn_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,sizeof(char),32,encInfo->fptr_src_image);
    encode_size_to_lsb(extn_size,buffer);
    fwrite(buffer,sizeof(char),32,encInfo->fptr_stego_image);
    return e_success;
}

//Function to encode the secret file extension (char)
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    if(encode_data_to_image((char*)file_extn, strlen(file_extn), encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Function to encode the secret file size(integer)
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,sizeof(char),32,encInfo->fptr_src_image);
    encode_size_to_lsb(file_size,buffer);
    fwrite(buffer,sizeof(char),32,encInfo->fptr_stego_image);
    return e_success;
}

//Function to encode the secret file data(char)
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char buffer[encInfo->size_secret_file];
    fseek(encInfo->fptr_secret,0,SEEK_SET);
    fread(buffer,sizeof(char),encInfo->size_secret_file,encInfo->fptr_secret);
    if(encode_data_to_image(buffer, strlen(buffer), encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Function to copy remaining image data (from source image to dest)
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char data[8];
    size_t bytes_read;
    while((bytes_read = fread(data,sizeof(char),8,fptr_src))>0)
    {
        fwrite(data,sizeof(char),8,fptr_dest);
    }
    return e_success;
}