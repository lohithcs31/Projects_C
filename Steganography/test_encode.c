#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    //Create structure variables for encode and decode operations
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    //Store the enum returned by check_operation_type() and take action based on the return 
    OperationType res = check_operation_type(argv);
    if(res == e_encode)
    {
        //Evaluate the argument vector for the encode operation
        if(read_and_validate_encode_args(argc, argv, &encInfo)==e_success)
        {
            printf("Read and validate encode arguments operation completed successfully!!\n");
            //Call do_encoding function to continue the encoding operation
            if(do_encoding(&encInfo)==e_success)
            {
                printf("Encoding operation completed successfully!\n");
                //deallocating memory after encode operation
                free(encInfo.src_image_fname);
                free(encInfo.secret_fname);
            }
            else
            {
                printf("Encoding operation failed!!\n");
            }
        }
        else
        {
            printf("Read and validate arguments operation failed!!\n");
            return 0;
        }
    }
    else if(res==e_decode)
    {
        //Evaluate the argument vector for the decode operation
        if(read_and_validate_decode_args(argc, argv, &decInfo)==e_success)
        {
            printf("Read and validate decode arguments operation completed successfully!!\n");
            //Call do_decoding function to continue the decoding operation
            if(do_decoding(&decInfo)==e_success)
            {
                printf("Decoding operation completed successfully!\n");
                
            }
            else
            {
                printf("Decoding operation failed!!\n");
            }
        }
        else
        {
            printf("Read and validate arguments operation failed!\n");
            return 0;
        }
    }
    else
    {
        printf("Unsupported operation!\n");
        return 0;
    }
}

//Used to check what operation needs to be performed (either encoding or decoding)
//Function is common for both encoding and decoding
OperationType check_operation_type(char *argv[])
{
    if(!(strcmp(argv[1],"-e")))
    {
        return e_encode;
    }
    else if(!(strcmp(argv[1],"-d")))
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
}


