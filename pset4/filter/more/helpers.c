#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE qB, qG, qR; // q = Quantidade
    float averagefloat;
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            qB = image[i][j].rgbtBlue;
            qG = image[i][j].rgbtGreen;
            qR = image[i][j].rgbtRed;

            // Formula de Preto e Branco
            averagefloat = ((float) qB + (float) qG + (float) qR) / 3;
            average = round(averagefloat);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int qB, qG, qR; // quantidade da esquerda
    int qBr, qGr, qRr; // quantidade da direita
    int last = width - 1;

    for (int i = 0; i < height; i++)
    {
        // Width / 2, se nao reflete e depois reflete novamente e fica normal
        for (int j = 0; j < width / 2; j++)
        {
            qB = image[i][j].rgbtBlue;
            qG = image[i][j].rgbtGreen;
            qR = image[i][j].rgbtRed;

            qBr = image[i][last - j].rgbtBlue;
            qGr = image[i][last - j].rgbtGreen;
            qRr = image[i][last - j].rgbtRed;

            image[i][j].rgbtBlue = qBr;
            image[i][j].rgbtGreen = qGr;
            image[i][j].rgbtRed = qRr;

            image[i][last - j].rgbtBlue = qB;
            image[i][last - j].rgbtGreen = qG;
            image[i][last - j].rgbtRed = qR;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float averageB, averageG, averageR;

    // copy
    RGBTRIPLE temp[height][width];

    for (int ti = 0; ti < height; ti++)
    {
        for (int tj = 0; tj < width; tj++)
        {
            temp[ti][tj].rgbtBlue = image[ti][tj].rgbtBlue;
            temp[ti][tj].rgbtGreen = image[ti][tj].rgbtGreen;
            temp[ti][tj].rgbtRed = image[ti][tj].rgbtRed;

        }
    }

    // Pixel original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumB = 0, sumG = 0, sumR = 0;
            int count = 0;

            // Pixel em volta
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if ((x < 0 || y < 0) || (x >= height || y >= width))
                    {
                        continue;
                    }
                    sumB = sumB + temp[x][y].rgbtBlue;
                    sumG = sumG + temp[x][y].rgbtGreen;
                    sumR = sumR + temp[x][y].rgbtRed;
                    count++;
                }
            }
            // Pegando média
            averageB = sumB / count;
            averageG = sumG / count;
            averageR = sumR / count;

            // Efeito de fato
            image[i][j].rgbtBlue = round(averageB);
            image[i][j].rgbtGreen = round(averageG);
            image[i][j].rgbtRed = round(averageR);

        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Variáveis
    RGBTRIPLE temp[height][width];
    int GR[3][3];
    int GG[3][3];
    int GB[3][3];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float resultR, resultG, resultB;

    // I'm basically making a copy of my image (because the original will be changed.)
    for (int tempi = 0; tempi < height; tempi++)
    {
        for (int tempj = 0; tempj < width; tempj++)
        {
            temp[tempi][tempj].rgbtRed = image[tempi][tempj].rgbtRed;
            temp[tempi][tempj].rgbtGreen = image[tempi][tempj].rgbtGreen;
            temp[tempi][tempj].rgbtBlue = image[tempi][tempj].rgbtBlue;
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int countx = 0;

            // Then I take the 3x3 values to put in the formula
            for (int x = i - 1; x < i + 2; x++)
            {
                int county = 0;
                for (int y = j - 1; y < j + 2; y++)
                {
                    if ((x < 0 || y < 0) || (x >= height || y >= width))
                    {
                        GR[countx][county] = 0;
                        GG[countx][county] = 0;
                        GB[countx][county] = 0;
                    }
                    else
                    {
                        GR[countx][county] = temp[x][y].rgbtRed;
                        GG[countx][county] = temp[x][y].rgbtGreen;
                        GB[countx][county] = temp[x][y].rgbtBlue;
                    }

                    county++;

                }
                countx++;
            }

            // So we add and multiply
            float sumxR = 0, sumyR = 0, sumxG = 0, sumyG = 0, sumxB = 0, sumyB = 0;
            for (int ix = 0; ix <= 2; ix++)
            {
                for (int iy = 0; iy <= 2; iy++)
                {
                    sumxR = sumxR + (GR[ix][iy] * Gx[ix][iy]);
                    sumxG = sumxG + (GG[ix][iy] * Gx[ix][iy]);
                    sumxB = sumxB + (GB[ix][iy] * Gx[ix][iy]);

                    sumyR = sumyR + (GR[ix][iy] * Gy[ix][iy]);
                    sumyG = sumyG + (GG[ix][iy] * Gy[ix][iy]);
                    sumyB = sumyB + (GB[ix][iy] * Gy[ix][iy]);
                }
            }

            // Finally I take the result and put it in the formula: square root (Gx ^ 2 + Gy ^ 2)
            resultR = sqrt((sumxR * sumxR) + (sumyR * sumyR));
            resultG = sqrt((sumxG * sumxG) + (sumyG * sumyG));
            resultB = sqrt((sumxB * sumxB) + (sumyB * sumyB));

            // If it exceeds 255 it must be 255, because RGB goes up to 255 which is white
            if (resultR > 255)
            {
                resultR = 255;
            }
            if (resultG > 255)
            {
                resultG = 255;
            }
            if (resultB > 255)
            {
                resultB = 255;
            }

            // And if there is a broken number, round to the nearest
            image[i][j].rgbtRed = round(resultR);
            image[i][j].rgbtGreen = round(resultG);
            image[i][j].rgbtBlue = round(resultB);
        }
    }
}