#include "helpers.h"
#include <math.h>

int sum(int *a, BYTE *b);

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE qB, qG, qR;
    float fR, fG, fB;
    float sepiaRed, sepiaGreen, sepiaBlue;
    float sepiaR, sepiaG, sepiaB;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            qB = image[i][j].rgbtBlue;
            qG = image[i][j].rgbtGreen;
            qR = image[i][j].rgbtRed;

            // Formula de Sépia
            fR = qR * .393;
            fG = qG * .769;
            fB = qB * .189;
            sepiaR = fR + fG + fB;

            fR = qR * .349;
            fG = qG * .686;
            fB = qB * .168;
            sepiaG = fR + fG + fB;

            fR = qR * .272;
            fG = qG * .534;
            fB = qB * .131;
            sepiaB = fR + fG + fB;

            sepiaRed = round(sepiaR);
            sepiaGreen = round(sepiaG);
            sepiaBlue = round(sepiaB);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
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
