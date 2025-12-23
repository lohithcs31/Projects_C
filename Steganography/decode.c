#include <stdio.h>
#include "decode.h"
#include "types.h"
#include <string.h>
#include "common.h"
#include <stdlib.h>

//Global variable to store the secret file size 
unsigned int file_size = 0;

//For the decode operation, only the encoded image needs to performed
Status open_file(DecodeInfo *decInfo)
{
    // Stego Image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    // Do Error handling
    if (decInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

//Evaluate the argument vector before performing actual decode operation
Status read_and_validate_decode_args(int argc, char *argv[], DecodeInfo* decInfo)
{
    //Only 3 arguments are mandatory --> ./a.out -d stego.bmp {the 4th argument is optional, if its mentioned only file name without the extension is mentioned}
    if(argc<3||argc>4)
    {
        printf("Number of command line arguments is improper!!\n");
        return e_failure;
    }
    else
    {
        if(strstr(argv[2],".bmp")!=NULL)
        {
            decInfo->stego_image_fname = malloc(strlen(argv[2])+1);
            strcpy(decInfo->stego_image_fname,argv[2]);
            printf("Encoded image file name : %s\n",decInfo->stego_image_fname);
            if(argc==4)
            {
                if(!(strchr(argv[3],'.')==NULL))
                {
                    printf("File name with extension provided! Decoding operation aborted!\n");
                    return e_failure;
                }
                else
                {
                    decInfo->secret_fname = malloc(strlen(argv[3])+1);
                    strcpy(decInfo->secret_fname,argv[3]);
                    printf("File name without extension : %s\n",decInfo->secret_fname);
                    return e_success;
                }
            }
            else
            {
                decInfo->secret_fname = malloc(strlen("decode_secret")+1);
                strcpy(decInfo->secret_fname,"decode_secret");
                printf("File name without extension : %s\n",decInfo->secret_fname);
                return e_success;
            }
        }
        else
        {
            return e_failure;
        }
    }
}

//All operations related to decoding are handled by this function alone
Status do_decoding(DecodeInfo *decInfo)
{
    if(open_file(decInfo)==e_success)
    {
        if(skip_bmp_header(decInfo->fptr_stego_image)==e_success)
        {
            if(decode_magic_string(MAGIC_STRING,decInfo)==e_success)
            {
                long int extn_size;
                if(decode_secret_extn_size(extn_size, decInfo)==e_success)
                {
                    char *file_extn;
                    if(decode_secret_file_extn(file_extn, decInfo)==e_success)
                    {
                        printf("Secret file name with extension : %s\n",decInfo->secret_fname);
                        if(decode_secret_file_size(file_size, decInfo)==e_success)
                        {
                            if(decode_secret_file_data(decInfo)==e_success)
                            {
                                return e_success;
                            }
                            else
                            {
                                printf("Secret file data decoding failed!\n");
                            }
                        }
                        else
                        {
                            printf("Secret file size decoding failed!\n");
                        }
                    }
                    else
                    {
                        printf("Secret file extension decoding failed!\n");
                    }
                }
                else
                {
                    printf("Secret file extension size decoding failed!\n");
                }
            }
            else
            {
                printf("Magic string decode operation failed\n");
            }
        }
        else
        {
            printf("Could not skip bmp header!\n");
            return e_failure;
        }
    }
    else
    {
        printf("Open file operation failed!!\n");
        return e_failure;
    }
}

//This function skips the first 54 bytes of the encoded image
Status skip_bmp_header(FILE *fptr_dest_image)
{
    fseek(fptr_dest_image,54,SEEK_SET);
    return e_success;
}

//Function to decode magic string(char)
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    //the encoded magic string is also passed to validate if it matches decoded magic string
    char buffer[2];
    if(decode_image_to_data(buffer, strlen(MAGIC_STRING),decInfo->fptr_stego_image)==e_success)
    {
        //Only if the decoded magic string matches the original, return e_success
        if(!(strcmp(magic_string,buffer)))
        {
            printf("Decoded magic string is same : %s\n",buffer);
            return e_success;
        }
        else
        {
            printf("Decode magic string is different!!\n");
            return e_failure;
        }
    }
}

//This function is used to read 8 bytes of encoded image data and pass it to decode lsb_to_byte for actual decoding
Status decode_image_to_data(char *data, int size, FILE *fptr_stego_image)
{
    char buffer[8];
    int count=0;//to keep track of the number of decoded bytes
    for(int i=0;i<size;i++)
    {
        fread(buffer,sizeof(char),8,fptr_stego_image);
        data[i] = decode_lsb_to_byte((char*)buffer);
        count++;
    }
    if(size==count)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//This function does the actual decoding of the char data(magic string, extn,secret data)
char decode_lsb_to_byte(char *image_buffer)
{
    char ch = 0;
    int mask;
    int i=0;
    for(int pos=7;pos>=0;pos--)
    {
        mask = image_buffer[i] & 1;
        ch = ch | (mask<<pos);
        i++;
    }
    return ch;
}

//Function to decode the extension size (int)
Status decode_secret_extn_size(long extn_size, DecodeInfo *decInfo)
{
    char buffer[32];
    fread(buffer,sizeof(char),32,decInfo->fptr_stego_image);
    extn_size = decode_size_to_lsb(buffer);
    decInfo->size_secret_file = extn_size;
    printf("Secret file extension size : %ld\n",extn_size);
    if(extn_size!=0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Function which performs actual size decoding (int-extn size, file size)
int decode_size_to_lsb(char *image_buffer)
{
    int dec_byte = 0;
    int mask;
    int i = 0;
    for(int pos=31;pos>=0;pos--)
    {
        mask = image_buffer[i] & 1;
        dec_byte = dec_byte | (mask<<pos);
        i++;
    }
    return dec_byte; 
}

//Function to decode the secret file extension(Ex. .txt)
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo)
{
    file_extn = (char*)malloc(5);
    char buffer[8];
    int count = 0;
    int i;
    for(i=0;i<(decInfo->size_secret_file);i++)
    {
        fread(buffer,sizeof(char),8,decInfo->fptr_stego_image);
        file_extn[i] = decode_lsb_to_byte(buffer);
        count++;
    }
    file_extn[i] = '\0';
    printf("Secret file extension : %s\n",file_extn);
    if(count==(decInfo->size_secret_file))
    {
        strcat(decInfo->secret_fname,file_extn);
        free(file_extn);
        return e_success;
    }
    else
    {
        free(file_extn);
        return e_failure;
    }
}

//Function to decode the secret file size (int)
Status decode_secret_file_size(long file_size, DecodeInfo *decInfo)
{
    char buffer[32];
    fread(buffer,sizeof(char),32,decInfo->fptr_stego_image);
    file_size = decode_size_to_lsb(buffer);
    decInfo->file_size = file_size;
    printf("Secret file size : %ld\n",file_size);
    if(file_size!=0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

//Function to decode the secret file data (char)
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    decInfo->fptr_secret = fopen(decInfo->secret_fname,"w");
    char buffer[8];
    char *secret_data = malloc((decInfo->file_size*8));
    int count = 0;
    for(int i=0;i<(decInfo->file_size);i++)
    {
        fread(buffer,sizeof(char),8,decInfo->fptr_stego_image);
        secret_data[i] = decode_lsb_to_byte(buffer);
        count++;
    }
    printf("Secret data : %s\n",secret_data);
    fwrite(secret_data,sizeof(char),strlen(secret_data),decInfo->fptr_secret);
    free(secret_data);
    fclose(decInfo->fptr_secret);
    if(count==decInfo->file_size)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}