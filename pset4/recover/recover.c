#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Conferir se o ARGC == 2
    if (argc != 2)
    {
        printf("Usage: ./recover name.raw\n");
        return 1;
    }
    // Pegar o arquivo
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File NULL\n");
        return 1;
    }


    unsigned char buffer[512];
    char name[8];
    FILE *img;


    int i = 0;
    int j = 0;

    while (1)
    {
        // Ler o arquivo
        int read = fread(buffer, 512, 1, file);
        // Checar se chegou no fim
        if (read < 1)
        {
            break;
        }
        // JPEG pattern
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // New image
            if (j == 1)
            {
                fclose(img);
                j = 0;
            }
            // First and more images
            sprintf(name, "%03i.jpg", i);
            img = fopen(name, "wb");
            i++;
            j++;
        }
        // Check if not is new image
        if (j == 1)
        {
            fwrite(buffer, 512, 1, img);
        }


    }

    // Fechar programa
    fclose(img);
    fclose(file);

}
