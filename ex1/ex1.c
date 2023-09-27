//Ariel Elbaz 213073497
#include <stdbool.h>
//
// Created by arie1 on 11/13/2022.
// ID - 213073497.
//

int is_big_endian() {

    long word = 0x1;
    char *ch = (char *) &word;
    if (*ch)
        // little endian - if the least significant byte is the first byte in memory.
        return 0;
        // big endian
    else
        return 1;
}

/**
 * @brief get the sign magnitude of a bit array
 * @param bitArray
 * @return sum - the sign magnitude of the bit array
 */
int get_sign_magnitude(bool bitArray[8]) {
    int decimalNum = 0;
    int sign = 1 - 2 * bitArray[7];
    int j = 0;
    for (j = 6; j >= 0; j--) {
        //if (bitArray[j] == 1)  it will shift by j meaning it will multiply  1 by 2^j and add it to sum.
        decimalNum += bitArray[j] << j;
    }
    // if the sign is negative, multiply the decimal number by -1.
    decimalNum *= sign;
    return decimalNum;
}

/*
 * @brief get the two's complement of a bit array
 * @param bitArray
 * @return sum - the two's complement of the bit array
 */
int get_two_comp(bool bitArray[8]) {
    int decimalNum = 0;
    // -Xw-1 * 2^w-1 -- w-1 is the first bit of the number and Xw-1  is the sign of the w-1 bit.
    int complement = -bitArray[7] << 7;
    /*
     * running over the array from the end to the beginning and if the bit is 1 we will add 2^j to decimalNum.
     */
    int j = 0;
    for (j = 6; j >= 0; j--) {
        //if (bitArray[j] == 1)  it will shift by j meaning it will multiply  1 by 2^j and add it to decimalNum.
        decimalNum += bitArray[j] << j;
    }
    //
    decimalNum += complement;
    return decimalNum;
}