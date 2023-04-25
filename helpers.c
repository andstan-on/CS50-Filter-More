#include "helpers.h"
#include  <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            average = round((image[i][j].rgbtBlue +  image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflected[width] ;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = width - 1, k = 0 ; j >= 0 ; j--, k ++)
        {
            reflected[k] = image[i][j] ;
        }
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = reflected[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    int sum_B ;
    int sum_G ;
    int sum_R ;
    float count ;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            sum_B = image[i][j].rgbtBlue;
            sum_G = image[i][j].rgbtGreen;
            sum_R = image[i][j].rgbtRed;
            count = 1;
            if ((i - 1 >= 0 && i - 1 < height) && (j - 1 >= 0 && j - 1 < width))
            {
                sum_B += image[i - 1][j - 1].rgbtBlue;
                sum_G += image[i - 1][j - 1].rgbtGreen;
                sum_R += image[i - 1][j - 1].rgbtRed;
                count += 1;
            }
            if ((i - 1 >= 0 && i - 1 < height) && (j >= 0 && j < width))
            {
                sum_B += image[i - 1][j].rgbtBlue;
                sum_G += image[i - 1][j].rgbtGreen;
                sum_R += image[i - 1][j].rgbtRed;
                count += 1;
            }
            if ((i - 1 >= 0 && i - 1 < height) && (j + 1 >= 0 && j + 1 < width))
            {
                sum_B += image[i - 1][j + 1].rgbtBlue;
                sum_G += image[i - 1][j + 1].rgbtGreen;
                sum_R += image[i - 1][j + 1].rgbtRed;
                count += 1;
            }
            if ((i >= 0 && i < height) && (j - 1 >= 0 && j - 1 < width))
            {
                sum_B += image[i][j - 1].rgbtBlue;
                sum_G += image[i][j - 1].rgbtGreen;
                sum_R += image[i][j - 1].rgbtRed;
                count += 1;
            }
            if ((i >= 0 && i < height) && (j + 1 >= 0 && j + 1 < width))
            {
                sum_B += image[i][j + 1].rgbtBlue;
                sum_G += image[i][j + 1].rgbtGreen;
                sum_R += image[i][j + 1].rgbtRed;
                count += 1;
            }
            if ((i + 1 >= 0 && i + 1 < height) && (j - 1 >= 0 && j - 1 < width))
            {
                sum_B += image[i + 1][j - 1].rgbtBlue;
                sum_G += image[i + 1][j - 1].rgbtGreen;
                sum_R += image[i + 1][j - 1].rgbtRed;
                count += 1;
            }
            if ((i + 1 >= 0 && i + 1 < height) && (j >= 0 && j < width))
            {
                sum_B += image[i + 1][j].rgbtBlue;
                sum_G += image[i + 1][j].rgbtGreen;
                sum_R += image[i + 1][j].rgbtRed;
                count += 1;
            }
            if ((i + 1 >= 0 && i + 1 < height) && (j + 1 >= 0 && j + 1 < width))
            {
                sum_B += image[i + 1][j + 1].rgbtBlue;
                sum_G += image[i + 1][j + 1].rgbtGreen;
                sum_R += image[i + 1][j + 1].rgbtRed;
                count += 1;
            }
            blurred[i][j].rgbtBlue = round((sum_B / count));
            blurred[i][j].rgbtGreen = round((sum_G / count));
            blurred[i][j].rgbtRed = round((sum_R / count));


        }
    }
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];
    int comp_B ;
    int comp_G ;
    int comp_R ;
    float GX_blue ;
    float GX_green;
    float GX_red ;
    float GY_blue ;
    float GY_green;
    float GY_red ;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            GX_blue = 0 ;
            GX_green = 0;
            GX_red = 0 ;
            GY_blue = 0 ;
            GY_green = 0;
            GY_red = 0 ;
            if ((i - 1 >= 0 && i - 1 < height) && (j - 1 >= 0 && j - 1 < width))
            {
                GX_blue += -1 * image[i - 1][j - 1].rgbtBlue ;
                GX_green += -1 * image[i - 1][j - 1].rgbtGreen;
                GX_red += -1 * image[i - 1][j - 1].rgbtRed ;
                GY_blue += -1 * image[i - 1][j - 1].rgbtBlue ;
                GY_green += -1 * image[i - 1][j - 1].rgbtGreen;
                GY_red += -1 * image[i - 1][j - 1].rgbtRed ;
            }



            if ((i - 1 >= 0 && i - 1 < height) && (j >= 0 && j < width))
            {

                GY_blue += -2 * image[i - 1][j].rgbtBlue ;
                GY_green += -2 * image[i - 1][j].rgbtGreen;
                GY_red += -2 * image[i - 1][j].rgbtRed ;
            }




            if ((i - 1 >= 0 && i - 1 < height) && (j + 1 >= 0 && j + 1 < width))
            {
                GX_blue +=  image[i - 1][j + 1].rgbtBlue ;
                GX_green +=  image[i - 1][j + 1].rgbtGreen;
                GX_red +=  image[i - 1][j + 1].rgbtRed ;
                GY_blue += -1 * image[i - 1][j + 1].rgbtBlue ;
                GY_green += -1 * image[i - 1][j + 1].rgbtGreen;
                GY_red += -1 * image[i - 1][j + 1].rgbtRed ;
            }




            if ((i >= 0 && i < height) && (j - 1 >= 0 && j - 1 < width))
            {
                GX_blue += -2 * image[i][j - 1].rgbtBlue ;
                GX_green += -2 * image[i][j - 1].rgbtGreen;
                GX_red += -2 * image[i][j - 1].rgbtRed ;

            }



            if ((i >= 0 && i < height) && (j + 1 >= 0 && j + 1 < width))
            {
                GX_blue += 2 * image[i][j + 1].rgbtBlue ;
                GX_green += 2 * image[i][j + 1].rgbtGreen;
                GX_red += 2 * image[i][j + 1].rgbtRed ;
            }




            if ((i + 1 >= 0 && i + 1 < height) && (j - 1 >= 0 && j - 1 < width))
            {
                GX_blue += -1 * image[i + 1][j - 1].rgbtBlue ;
                GX_green += -1 * image[i + 1][j - 1].rgbtGreen;
                GX_red += -1 * image[i + 1][j - 1].rgbtRed ;
                GY_blue += 1 * image[i + 1][j - 1].rgbtBlue ;
                GY_green += 1 * image[i + 1][j - 1].rgbtGreen;
                GY_red += 1 * image[i + 1][j - 1].rgbtRed ;
            }




            if ((i + 1 >= 0 && i + 1 < height) && (j >= 0 && j < width))
            {
                GY_blue += 2 * image[i + 1][j].rgbtBlue ;
                GY_green += 2 * image[i + 1][j].rgbtGreen;
                GY_red += 2 * image[i + 1][j].rgbtRed ;
            }




            if ((i + 1 >= 0 && i + 1 < height) && (j + 1 >= 0 && j + 1 < width))
            {
                GX_blue += 1 * image[i + 1][j + 1].rgbtBlue ;
                GX_green += 1 * image[i + 1][j + 1].rgbtGreen;
                GX_red += 1 * image[i + 1][j + 1].rgbtRed ;
                GY_blue += 1 * image[i + 1][j + 1].rgbtBlue ;
                GY_green += 1 * image[i + 1][j + 1].rgbtGreen;
                GY_red += 1 * image[i + 1][j + 1].rgbtRed ;
            }




            comp_B = round(sqrt(GX_blue * GX_blue + GY_blue * GY_blue)) ;
            if (comp_B > 255)
            {
                comp_B = 255;
            }

            comp_G = round(sqrt(GX_green * GX_green + GY_green * GY_green)) ;
            if (comp_G > 255)
            {
                comp_G = 255;
            }

            comp_R = round(sqrt(GX_red * GX_red + GY_red * GY_red)) ;
            if (comp_R > 255)
            {
                comp_R = 255;
            }

            edges[i][j].rgbtBlue = comp_B;
            edges[i][j].rgbtGreen = comp_G;
            edges[i][j].rgbtRed = comp_R;


        }
    }
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j].rgbtBlue = edges[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edges[i][j].rgbtGreen;
            image[i][j].rgbtRed = edges[i][j].rgbtRed;
        }
    }
    return;
}
