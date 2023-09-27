
#include "myutil.h"
#include "writeBMP.h"
#include "showBMP.h"
#include <stdlib.h>
#include <string.h>

#define  COL_SIZE m

void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName, char *sharpRsltImgName, char
*rowBlurRsltImgName, char *rowSharpRsltImgName, char *filteredBlurRsltImgName, char *filteredSharpRsltImgName, char
flag) {

    register int sumOfRgb;
    int matrix_loop_dim = COL_SIZE - 1;
    register int currRow, currCol;
    pixel current_pixel;
    register pixel loop_pixel;
    register int col1_red, col1_green, col1_blue;
    register int col2_red, col2_green, col2_blue;
    register int col3_red, col3_green, col3_blue;
    register int temp_coll_red = 0, temp_coll_green = 0, temp_coll_blue = 0;
    register int min_intensity_row, min_intensity_coll, max_intensity_row, max_intensity_coll;
    register int ii_inner;
    register int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is
    // 255*3=765
    register int max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
    register int rowsIndex;
    rowsIndex = COL_SIZE; // loop over rows
    int size = COL_SIZE * COL_SIZE * 3;
    // get pointer to image data
    register pixel *pixelsImg = malloc(size);
    // allocate memory for backup image
    register pixel *backupOrg = malloc(size);

    // copy original image to backup
    memcpy(pixelsImg, image->data, size);
    // copyPixels(pixelsImg, backupOrg);
    memcpy(backupOrg, pixelsImg, size);

    if (flag == '1') {
        /*
         * 1. Blur the image using a 3x3 kernel with 1/9 scale factor
         */
        currRow = 1;
        while (currRow < matrix_loop_dim) {
            for (currCol = 1; currCol < matrix_loop_dim; currCol++) {
                ii_inner = rowsIndex - COL_SIZE + currCol;
                if (currCol == 1) {
                    // sum all of the pixels in the first column of the kernel using pointer arithmetic
                    loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[0][0]
                    // calculate the weighted sum of the first column of the kernel
                    col1_blue = ((int) loop_pixel.blue);
                    col1_green = ((int) loop_pixel.green);
                    col1_red = ((int) loop_pixel.red);
                    // go to the second column of the kernel
                    loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                    // -kernel[0][1]
                    // calculate the weighted sum of the first pixel in the second column of the kernel
                    col2_blue = ((int) loop_pixel.blue);
                    col2_green = ((int) loop_pixel.green);
                    col2_red = ((int) loop_pixel.red);
                    // go to the third column of the kernel
                    loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel

                    col3_blue = ((int) loop_pixel.blue);
                    col3_green = ((int) loop_pixel.green);
                    col3_red = ((int) loop_pixel.red);
                    // move to the next row
                    ii_inner += COL_SIZE;
                    // sum all of the pixels in the first column of the kernel using pointer arithmetic
                    loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[1][0]
                    // calculate the weighted sum of the first column of the kernel
                    col1_blue += ((int) loop_pixel.blue);
                    col1_green += ((int) loop_pixel.green);
                    col1_red += ((int) loop_pixel.red);
                    // go to the second column of the kernel
                    loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                    // calculate the weighted sum of the first pixel in the second column of the kernel
                    col2_blue += ((int) loop_pixel.blue);
                    col2_green += ((int) loop_pixel.green);
                    col2_red += ((int) loop_pixel.red);
                    // go to the third column of the kernel
                    loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel

                    col3_blue += ((int) loop_pixel.blue);
                    col3_green += ((int) loop_pixel.green);
                    col3_red += ((int) loop_pixel.red);
                    // move to the next row
                    ii_inner += COL_SIZE;
                    // sum all of the pixels in the first column of the kernel using pointer arithmetic
                    loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[2][0]
                    // calculate the weighted sum of the first column of the kernel
                    col1_blue += ((int) loop_pixel.blue);
                    col1_green += ((int) loop_pixel.green);
                    col1_red += ((int) loop_pixel.red);
                    // go to the second column of the kernel
                    loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                    // calculate the weighted sum of the first pixel in the second column of the kernel
                    col2_blue += ((int) loop_pixel.blue);
                    col2_green += ((int) loop_pixel.green);
                    col2_red += ((int) loop_pixel.red);
                    // go to the third column of the kernel
                    loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel
                    // kernel[2][2]

                    col3_blue += ((int) loop_pixel.blue);
                    col3_green += ((int) loop_pixel.green);
                    col3_red += ((int) loop_pixel.red);
                }
                    // because we already calculated the weighted sum of the first column of the kernel and the matrix looks like this: {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}
                else {
                    // the second colomn of the new  kernel is the same as the first column of the old kernel
                    col1_blue = col2_blue;
                    col1_green = col2_green;
                    col1_red = col2_red;
                    // the third column of the new kernel is the same as the second column of the old kernel
                    col2_blue = col3_blue;
                    col2_green = col3_green;
                    col2_red = col3_red;

                    loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel
                    col3_blue = ((int) loop_pixel.blue);  // add the blue value of the pixel to the weighted sum of the third column of the kernel
                    col3_green = ((int) loop_pixel.green); // add the green value of the pixel to the weighted sum of the third column of the kernel
                    col3_red = ((int) loop_pixel.red);  // add the red value of the pixel to the weighted sum of the third column of the kernel

                    // move to the next row
                    ii_inner += COL_SIZE;

                    loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel
                    col3_blue += ((int) loop_pixel.blue);
                    col3_green += ((int) loop_pixel.green);
                    col3_red += ((int) loop_pixel.red);

                    // move to the next row
                    ii_inner += COL_SIZE;

                    loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel
                    col3_blue += ((int) loop_pixel.blue); // add the blue value of the pixel to the weighted sum of the third column of the kernel
                    col3_green += ((int) loop_pixel.green); // add the green value of the pixel to the weighted sum of the third column of the kernel
                    col3_red += ((int) loop_pixel.red); // add the red value of the pixel to the weighted sum of the
                    // third column of the kernel
                }
                temp_coll_blue = (col1_blue + col2_blue + col3_blue) / 9;
                temp_coll_green = (col1_green + col2_green + col3_green) / 9;
                temp_coll_red = (col1_red + col2_red + col3_red) / 9;
                //  use trenaary operator to check if the value is in the range of 0-255
                current_pixel.red = (temp_coll_red > 255) ? 255 : (temp_coll_red < 0) ? 0 : temp_coll_red;
                current_pixel.green = (temp_coll_green > 255) ? 255 : (temp_coll_green < 0) ? 0 : temp_coll_green;
                current_pixel.blue = (temp_coll_blue > 255) ? 255 : (temp_coll_blue < 0) ? 0 : temp_coll_blue;

                *(pixelsImg + rowsIndex + currCol) = current_pixel; // assign the pixel to the new image
            }
            // finished with the current row, move to the next row
            rowsIndex = rowsIndex + COL_SIZE;
            currRow++;
        }
        // finished with doing the convolution - copy the new image to the original image
        memcpy(image->data, pixelsImg, size);
        // write result image to file
        writeBMP(image, srcImgpName, blurRsltImgName);

        // move to the next convolution
        memcpy(pixelsImg, image->data, size); // copy image->data to pixelsImg
        memcpy(backupOrg, pixelsImg, size); // copy image->data to backupOrg'
        rowsIndex = COL_SIZE;
        /*
         * sharp the image using the following kernel: {{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}}
         */
        currRow = 1;
        while (currRow < matrix_loop_dim) {
           for(currCol = 1; currCol < matrix_loop_dim; currCol++) {
                ii_inner = rowsIndex - COL_SIZE + currCol;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[0][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue = -((int) loop_pixel.blue);
                col1_green = -((int) loop_pixel.green);
                col1_red = -((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                // -kernel[0][1]
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue = -((int) loop_pixel.blue);
                col2_green = -((int) loop_pixel.green);
                col2_red = -((int) loop_pixel.red);
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // kernel[0][2]

                col3_blue = -((int) loop_pixel.blue);
                col3_green = -((int) loop_pixel.green);
                col3_red = -((int) loop_pixel.red);
                // move to the next row
                ii_inner += COL_SIZE;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[1][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue -= ((int) loop_pixel.blue);
                col1_green -= ((int) loop_pixel.green);
                col1_red -= ((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // kernel[1][1]
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue += (9 * ((int) loop_pixel.blue));
                col2_green += (9 * ((int) loop_pixel.green));
                col2_red += (9 * ((int) loop_pixel.red));
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // kernel[1][2]

                col3_blue -= ((int) loop_pixel.blue);
                col3_green -= ((int) loop_pixel.green);
                col3_red -= ((int) loop_pixel.red);
                // move to the next row
                ii_inner += COL_SIZE;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[2][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue -= ((int) loop_pixel.blue);
                col1_green -= ((int) loop_pixel.green);
                col1_red -= ((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue -= ((int) loop_pixel.blue);
                col2_green -= ((int) loop_pixel.green);
                col2_red -= ((int) loop_pixel.red);
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel
                // kernel[2][2]

                col3_blue -= ((int) loop_pixel.blue);
                col3_green -= ((int) loop_pixel.green);
                col3_red -= ((int) loop_pixel.red);

                temp_coll_blue = (col1_blue + col2_blue + col3_blue);
                temp_coll_green = (col1_green + col2_green + col3_green);
                temp_coll_red = (col1_red + col2_red + col3_red);

                // if the color value is less then zero or greater than 255, set it to 0 or 255 respectively with inline if-else statement
                current_pixel.red = (temp_coll_red > 255) ? 255 : (temp_coll_red < 0) ? 0 : temp_coll_red;
                current_pixel.green = (temp_coll_green > 255) ? 255 : (temp_coll_green < 0) ? 0 : temp_coll_green;
                current_pixel.blue = (temp_coll_blue > 255) ? 255 : (temp_coll_blue < 0) ? 0 : temp_coll_blue;
                *(pixelsImg + rowsIndex + currCol) = current_pixel; // assign the pixel to the new image
            }
            // finished with the current row, move to the next row
            rowsIndex = rowsIndex + COL_SIZE;
            currRow++;
        }
        memcpy(image->data, pixelsImg, size);
        // write result image to file
        writeBMP(image, srcImgpName, sharpRsltImgName);
        free(pixelsImg);
        free(backupOrg);
    } else if (flag == '2') {
        currRow = 1;
        while (currRow < matrix_loop_dim) {
            for(currCol =1; currCol < matrix_loop_dim; currCol++) {
                ii_inner = rowsIndex - COL_SIZE + currCol;
                ii_inner += COL_SIZE;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[1][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue = ((int) loop_pixel.blue);
                col1_green = ((int) loop_pixel.green);
                col1_red = ((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // kernel[1][1]
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue = ((int) loop_pixel.blue) + ((int) loop_pixel.blue);
                col2_green = ((int) loop_pixel.green) + ((int) loop_pixel.green);
                col2_red = ((int) loop_pixel.red) + ((int) loop_pixel.red);
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // kernel[1][2]

                col3_blue = ((int) loop_pixel.blue);
                col3_green = ((int) loop_pixel.green);
                col3_red = ((int) loop_pixel.red);

                temp_coll_blue = (col1_blue + col2_blue + col3_blue) >> 2;
                temp_coll_green = (col1_green + col2_green + col3_green) >> 2;
                temp_coll_red = (col1_red + col2_red + col3_red) >> 2;
                // if the color value is less then zero or greater than 255, set it to 0 or 255 respectively with inline if-else statement
                current_pixel.red = (temp_coll_red > 255) ? 255 : (temp_coll_red < 0) ? 0 : temp_coll_red;
                current_pixel.green = (temp_coll_green > 255) ? 255 : (temp_coll_green < 0) ? 0 : temp_coll_green;
                current_pixel.blue = (temp_coll_blue > 255) ? 255 : (temp_coll_blue < 0) ? 0 : temp_coll_blue;
                *(pixelsImg + rowsIndex + currCol) = current_pixel; // assign the pixel to the new image
            }
            // finished with the current row, move to the next row
            currRow++;
            rowsIndex = rowsIndex + COL_SIZE;
        }
        memcpy(image->data, pixelsImg, size);
        // write result image to file

        writeBMP(image, srcImgpName, rowBlurRsltImgName);

        memcpy(pixelsImg, image->data, size); // copy image->data to pixelsImg
        memcpy(backupOrg, pixelsImg, size); // copy image->data to backup
        rowsIndex = n;
        currRow = 1;
        while (currRow < matrix_loop_dim) {
            for (currCol = 1; currCol < matrix_loop_dim; currCol++) {
                ii_inner = rowsIndex - COL_SIZE + currCol;
                ii_inner += COL_SIZE;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[1][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue = -((int) loop_pixel.blue) - ((int) loop_pixel.blue);
                col1_green = -((int) loop_pixel.green) - ((int) loop_pixel.green);
                col1_red = -((int) loop_pixel.red) - ((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // kernel[1][1]
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue = ((int) loop_pixel.blue) + ((int) loop_pixel.blue) + ((int) loop_pixel.blue) + ((int)
                        loop_pixel.blue) + ((int) loop_pixel.blue) + ((int) loop_pixel.blue);
                col2_green = ((int) loop_pixel.green) + ((int) loop_pixel.green) + ((int) loop_pixel.green) + ((int)
                        loop_pixel.green) + ((int) loop_pixel.green) + ((int) loop_pixel.green);
                col2_red = ((int) loop_pixel.red) + ((int) loop_pixel.red) + ((int) loop_pixel.red) + ((int)
                        loop_pixel.red) + ((int) loop_pixel.red) + ((int) loop_pixel.red);
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // kernel[1][2]

                col3_blue = -((int) loop_pixel.blue) - (int) (loop_pixel.blue);
                col3_green = -((int) loop_pixel.green) - ((int) loop_pixel.green);
                col3_red = -((int) loop_pixel.red) - ((int) loop_pixel.red);

                temp_coll_blue = (col1_blue + col2_blue + col3_blue) >> 1;
                temp_coll_green = (col1_green + col2_green + col3_green) >> 1;
                temp_coll_red = (col1_red + col2_red + col3_red) >> 1;
                // if the color value is less then zero or greater than 255, set it to 0 or 255 respectively with inline if-else statement
                current_pixel.red = (temp_coll_red > 255) ? 255 : (temp_coll_red < 0) ? 0 : temp_coll_red;
                current_pixel.green = (temp_coll_green > 255) ? 255 : (temp_coll_green < 0) ? 0 : temp_coll_green;
                current_pixel.blue = (temp_coll_blue > 255) ? 255 : (temp_coll_blue < 0) ? 0 : temp_coll_blue;
                *(pixelsImg + rowsIndex + currCol) = current_pixel; // assign the pixel to the new image
            }
            // finished with the current row, move to the next row
            rowsIndex = rowsIndex + COL_SIZE;
            currRow++;
        }
        memcpy(image->data, pixelsImg, size);
        free(pixelsImg);
        free(backupOrg);
        // write result image to file
        writeBMP(image, srcImgpName, rowSharpRsltImgName);
    } else {

        rowsIndex = COL_SIZE; // start from the second row
        currRow = 1;
        while (currRow < matrix_loop_dim) {
            for (currCol = 1; currCol < matrix_loop_dim; currCol++) {
                pixel max_intensity_pixel;
                pixel min_intensity_pixel;
                ii_inner = rowsIndex - COL_SIZE + currCol;
                // get the kernel[0][0] pixel value
                loop_pixel = backupOrg[ii_inner - 1];
                // calculate the weighted sum of the first pixel in the first column of the kernel
                temp_coll_red = ((int) loop_pixel.red);
                temp_coll_green = ((int) loop_pixel.green);
                temp_coll_blue = ((int) loop_pixel.blue);
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                /*
                 * if the sum of the RGB values is less than the minimum intensity,
                 * set the minimum intensity to the sum of the RGB values
                 */
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow - 1;
                    min_intensity_coll = currCol - 1;
                }
                /*
                 * if the sum of the RGB values is greater than the maximum intensity,
                 * set the maximum intensity to the sum of the RGB values
                 */
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow - 1;
                    max_intensity_coll = currCol - 1;
                }
                // get the kernel[0][1] pixel value
                loop_pixel = backupOrg[ii_inner];
                // calculate the weighted sum of the second pixel in the first column of the kernel
                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                /*
                 * if the sum of the RGB values is less than the minimum intensity,
                 * set the minimum intensity to the sum of the RGB values
                 */
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow - 1;
                    min_intensity_coll = currCol;
                }
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow - 1;
                    max_intensity_coll = currCol;
                }
                // get the kernel[0][2] pixel value
                loop_pixel = backupOrg[ii_inner + 1];
                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow - 1;
                    min_intensity_coll = currCol + 1;
                }
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow - 1;
                    max_intensity_coll = currCol + 1;
                }
                ii_inner += COL_SIZE;
                // get the kernel[1][0] pixel value
                loop_pixel = backupOrg[ii_inner - 1];

                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                // sum of the RGB values of the pixel
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow;
                    max_intensity_coll = currCol - 1;
                }
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow;
                    min_intensity_coll = currCol - 1;

                }
                // get the kernel[1][1] pixel value
                loop_pixel = backupOrg[ii_inner];
                // calculate the weighted sum of the second pixel in the second column of the kernel
                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                // sum of the RGB values of the pixel
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow;
                    min_intensity_coll = currCol;
                }
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow;
                    max_intensity_coll = currCol;

                }
                // get the kernel[1][2] pixel value
                loop_pixel = backupOrg[ii_inner + 1];
                // weight = *(*(kernel + 1) + 2);
                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);


                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow;
                    max_intensity_coll = currCol + 1;
                }
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow;
                    min_intensity_coll = currCol + 1;
                }

                ii_inner += COL_SIZE;
                // get the kernel[2][0] pixel value
                loop_pixel = backupOrg[ii_inner - 1];
                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                // sum of the RGB values of the pixel
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow + 1;
                    max_intensity_coll = currCol - 1;
                }
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow + 1;
                    min_intensity_coll = currCol - 1;

                }
                // get the kernel[2][1] pixel value
                loop_pixel = backupOrg[ii_inner];

                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                // use trinary operator to determine the maximum intensity
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow + 1;
                    max_intensity_coll = currCol;

                }
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow + 1;
                    min_intensity_coll = currCol;

                }
                loop_pixel = backupOrg[ii_inner + 1];
                temp_coll_red += ((int) loop_pixel.red);
                temp_coll_green += ((int) loop_pixel.green);
                temp_coll_blue += ((int) loop_pixel.blue);
                sumOfRgb = ((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue));
                if (sumOfRgb > max_intensity) {
                    max_intensity = sumOfRgb;
                    max_intensity_row = currRow + 1;
                    max_intensity_coll = currCol + 1;

                }
                if (sumOfRgb <= min_intensity) {
                    min_intensity = sumOfRgb;
                    min_intensity_row = currRow + 1;
                    min_intensity_coll = currCol + 1;
                }

                min_intensity_pixel = backupOrg[min_intensity_row * COL_SIZE + min_intensity_coll];
                max_intensity_pixel = backupOrg[max_intensity_row * COL_SIZE + max_intensity_coll];
                temp_coll_red -= (max_intensity_pixel.red + min_intensity_pixel.red);
                temp_coll_green -= (max_intensity_pixel.green + min_intensity_pixel.green);
                temp_coll_blue -= (max_intensity_pixel.blue + min_intensity_pixel.blue);
                // divide by 7 using bit shift
                temp_coll_red = temp_coll_red / 7;
                temp_coll_green = temp_coll_green / 7;
                temp_coll_blue = temp_coll_blue / 7;

                // use trenary operator to check if the value is in the range
                current_pixel.red = (temp_coll_red > 255) ? 255 : (temp_coll_red < 0) ? 0 : temp_coll_red;
                current_pixel.green = (temp_coll_green > 255) ? 255 : (temp_coll_green < 0) ? 0 : temp_coll_green;
                current_pixel.blue = (temp_coll_blue > 255) ? 255 : (temp_coll_blue < 0) ? 0 : temp_coll_blue;

                *(pixelsImg + rowsIndex + currCol) = current_pixel;
                // reset max and min intensity
                min_intensity = 766;
                max_intensity = -1;
            }
            rowsIndex = rowsIndex + COL_SIZE;
            currRow++;
        }
        memcpy(image->data, pixelsImg, size);

        // write result image to file
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);
        rowsIndex = COL_SIZE;
        memcpy(pixelsImg, image->data, size);
        memcpy(backupOrg, pixelsImg, size);
        // sharpen the resulting image

        currRow = 1;
        while (currRow < matrix_loop_dim) {
            for (currCol = 1; currCol < matrix_loop_dim; currCol++) {
                ii_inner = rowsIndex - COL_SIZE + currCol;

                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[0][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue = -((int) loop_pixel.blue);
                col1_green = -((int) loop_pixel.green);
                col1_red = -((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                // -kernel[0][1]
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue = -((int) loop_pixel.blue);
                col2_green = -((int) loop_pixel.green);
                col2_red = -((int) loop_pixel.red);
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // kernel[0][2]

                col3_blue = -((int) loop_pixel.blue);
                col3_green = -((int) loop_pixel.green);
                col3_red = -((int) loop_pixel.red);
                // move to the next row
                ii_inner += COL_SIZE;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[1][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue -= ((int) loop_pixel.blue);
                col1_green -= ((int) loop_pixel.green);
                col1_red -= ((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // kernel[1][1]
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue += (((int) loop_pixel.blue) << 3) + ((int) loop_pixel.blue);
                col2_green += (((int) loop_pixel.green) << 3) + (int) loop_pixel.green;
                col2_red += (((int) loop_pixel.red) << 3) + (((int) loop_pixel.red));
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // kernel[1][2]

                col3_blue -= ((int) loop_pixel.blue);
                col3_green -= ((int) loop_pixel.green);
                col3_red -= ((int) loop_pixel.red);
                // move to the next row
                ii_inner += COL_SIZE;
                // sum all of the pixels in the first column of the kernel using pointer arithmetic
                loop_pixel = backupOrg[ii_inner - 1]; // get kernel - kernel[2][0]
                // calculate the weighted sum of the first column of the kernel
                col1_blue -= ((int) loop_pixel.blue);
                col1_green -= ((int) loop_pixel.green);
                col1_red -= ((int) loop_pixel.red);
                // go to the second column of the kernel
                loop_pixel = backupOrg[ii_inner]; // get value pixel at the second column of the kernel
                // calculate the weighted sum of the first pixel in the second column of the kernel
                col2_blue -= ((int) loop_pixel.blue);
                col2_green -= ((int) loop_pixel.green);
                col2_red -= ((int) loop_pixel.red);
                // go to the third column of the kernel
                loop_pixel = backupOrg[ii_inner + 1]; // get value pixel at the third column of the kernel
                // kernel[2][2]

                col3_blue -= ((int) loop_pixel.blue);
                col3_green -= ((int) loop_pixel.green);
                col3_red -= ((int) loop_pixel.red);

                temp_coll_blue = (col1_blue + col2_blue + col3_blue);
                temp_coll_green = (col1_green + col2_green + col3_green);
                temp_coll_red = (col1_red + col2_red + col3_red);

                // if the color value is less then zero or greater than 255, set it to 0 or 255 respectively with
                // inline if-else statement
                current_pixel.red = (temp_coll_red > 255) ? 255 : (temp_coll_red < 0) ? 0 : temp_coll_red;
                current_pixel.green = (temp_coll_green > 255) ? 255 : (temp_coll_green < 0) ? 0 : temp_coll_green;
                current_pixel.blue = (temp_coll_blue > 255) ? 255 : (temp_coll_blue < 0) ? 0 : temp_coll_blue;
                *(pixelsImg + rowsIndex + currCol) = current_pixel; // assign the pixel to the new imag
            }
            // finished with the current row, move to the next row
            currRow++;
            rowsIndex = rowsIndex + COL_SIZE;
        }
        memcpy(image->data, pixelsImg, size);
        free(pixelsImg);
        free(backupOrg);
        // write result image to file
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
}
