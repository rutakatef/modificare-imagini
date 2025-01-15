#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

void extindere_pixeli(unsigned char *imagine_noua, unsigned char *imagine_veche, int inaltime, int latime, int scala) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            int index = (i * latime + j) * 3;
            int new_index_x = i * scala;
            int new_index_y = j * scala;
            int new_index = (new_index_x * latime * scala + new_index_y) * 3;
            imagine_noua[new_index] = imagine_veche[index];
            imagine_noua[new_index + 1] = imagine_veche[index + 1];
            imagine_noua[new_index + 2] = imagine_veche[index + 2];
        }
    }
}

void umplere_pixeli(unsigned char *imagine, int inaltime, int latime, int scala) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            if (i % scala == 0 && j % scala == 0) {
                continue;
            }
            int index_actual = (i * latime + j) * 3;
            if (j % scala != 0) {
                int stanga = j - 1;
                int dreapta = j + 1;
                if (stanga >= 0 && dreapta < latime) {
                    int index_stanga = (i * latime + stanga) * 3;
                    int index_dreapta = (i * latime + dreapta) * 3;
                    imagine[index_actual] = (imagine[index_stanga] + imagine[index_dreapta]) / 2;
                    imagine[index_actual + 1] = (imagine[index_stanga + 1] + imagine[index_dreapta + 1]) / 2;
                    imagine[index_actual + 2] = (imagine[index_stanga + 2] + imagine[index_dreapta + 2]) / 2;
                }
            }
            if (i % scala != 0) {
                int sus = i - 1;
                int jos = i + 1;
                if (sus >= 0 && jos < inaltime) {
                    int index_sus = (sus * latime + j) * 3;
                    int index_jos = (jos * latime + j) * 3;
                    imagine[index_actual] = (imagine[index_sus] + imagine[index_jos]) / 2;
                    imagine[index_actual + 1] = (imagine[index_sus + 1] + imagine[index_jos + 1]) / 2;
                    imagine[index_actual + 2] = (imagine[index_sus + 2] + imagine[index_jos + 2]) / 2;
                }
            }
        }
    }
}

void restul(unsigned char *imagine, int inaltime, int latime, int scala) {
    for (int x = 1; x < scala; x++) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            if ((i - x) % scala == 0 && (j - x) % scala == 0) {
                continue;
            }
            int index_actual = (i * latime + j) * 3;
            if (j % scala != 0) {
                int stanga = j - 1;
                int dreapta = j + 1;
                if (stanga >= 0 && dreapta < latime) {
                    int index_stanga = (i * latime + stanga) * 3;
                    int index_dreapta = (i * latime + dreapta) * 3;
                    imagine[index_actual] = (imagine[index_stanga] + imagine[index_dreapta]) / 2;
                    imagine[index_actual + 1] = (imagine[index_stanga + 1] + imagine[index_dreapta + 1]) / 2;
                    imagine[index_actual + 2] = (imagine[index_stanga + 2] + imagine[index_dreapta + 2]) / 2;
                }
            }

      if (i % scala != 0) {
                int sus = i - 1;
                int jos = i + 1;
                if (sus >= 0 && jos < inaltime) {
                    int index_sus = (sus * latime + j) * 3;
                    int index_jos = (jos * latime + j) * 3;
                    imagine[index_actual] = (imagine[index_sus] + imagine[index_jos]) / 2;
                    imagine[index_actual + 1] = (imagine[index_sus + 1] + imagine[index_jos + 1]) / 2;
                    imagine[index_actual + 2] = (imagine[index_sus + 2] + imagine[index_jos + 2]) / 2;
                }
            }
        }
    }
}
}

void reducere_pixeli(unsigned char *imagine_veche, unsigned char *imagine_noua, int inaltime_veche, int latime_veche, int scala) {
    int inaltime_noua = inaltime_veche / scala;
    int latime_noua = latime_veche / scala;
    for (int i = 0; i < inaltime_noua; i++) {
        for (int j = 0; j < latime_noua; j++) {
            int new_index = (i * latime_noua + j) * 3;
            int old_index = (i * scala *latime_veche + j * scala) * 3;
            imagine_noua[new_index] = imagine_veche[old_index];
            imagine_noua[new_index + 1] = imagine_veche[old_index + 1];
            imagine_noua[new_index + 2] = imagine_veche[old_index + 2];
        }
    }

}

void convertire(unsigned char *imagine, int inaltime, int latime) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            int index = (i * latime + j) * 3;
            unsigned char gray = (unsigned char)(imagine[index] * 0.299 + imagine[index + 1] * 0.587 + imagine[index + 2] * 0.114);
            imagine[index] = gray;
            imagine[index + 1] = gray;
            imagine[index + 2] = gray;
        }
    }
}

void blur(unsigned char *imagine, unsigned char *imagine_noua, int inaltime, int latime, int scala) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            int suma_r = 0, suma_g = 0, suma_b = 0;
            int num_pixeli = 0;
            for (int k = -scala; k <= scala; k++) {
                for (int l = -scala; l <= scala; l++) {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && x < inaltime && y >= 0 && y < latime) {
                        int index = (x * latime + y) * 3;

                        suma_r += imagine[index];
                        suma_g += imagine[index + 1];
                        suma_b += imagine[index + 2];
                        num_pixeli++;
                    }
                }
            }

            int index_curent = (i * latime + j) * 3;
            imagine_noua[index_curent] = suma_r / num_pixeli;
            imagine_noua[index_curent + 1] = suma_g / num_pixeli;
            imagine_noua[index_curent + 2] = suma_b / num_pixeli;
        }
    }
}




int main() {
    int inaltime, latime, culori;
    char adresa[500], salvare[500];
    printf("Introduceti adresa imaginii: ");
    fgets(adresa, 500, stdin);
    printf("Introduceti adresa in care doriti sa salvati imaginea modificata:");
    fgets(salvare, 500, stdin);
    salvare[strcspn(salvare, "\n")] = '\0';
    if (strlen(salvare) > 0 && salvare[strlen(salvare) - 1] == '\n') {
        salvare[strlen(salvare) - 1] = '\0';
    }
    adresa[strcspn(adresa, "\n")] = '\0';
    if (strlen(adresa) > 0 && adresa[strlen(adresa) - 1] == '\n') {
        adresa[strlen(adresa) - 1] = '\0';
    }
    unsigned char *img_data = stbi_load(adresa, &latime, &inaltime, &culori, 0);
    if (img_data == NULL) {
        printf("Eroare la incarcarea imaginii.\n");
        return 1;
    }
    char conditie[20];
    printf("Doriti micsorare, marire sau niciuna?");
    scanf("%s", conditie);
    if (strcmp(conditie, "marire") == 0) {
        int inaltime_noua, latime_noua;
        int scala;
        printf("De cate ori doriti sa mariti?");
        scanf("%d", &scala);
        latime_noua = latime * scala;
        inaltime_noua = inaltime * scala;
        unsigned char *image_data = (unsigned char *)malloc(latime_noua * inaltime_noua * 3);
        if (image_data == NULL) {
            printf("Eroare la alocarea memoriei pentru imaginea noua.\n");
            free(img_data);
            return 1;
        }
        extindere_pixeli(image_data, img_data, inaltime, latime, scala);
        for (int i = 0 ; i < scala; i++) {
            umplere_pixeli(image_data, inaltime_noua, latime_noua, scala);
        }
        for (int i = 0 ; i < scala; i++) {
            restul(image_data, inaltime_noua, latime_noua, scala);
        }
        if (!stbi_write_png(salvare, latime_noua, inaltime_noua, 3, image_data, latime_noua * 3)) {
            printf("Eroare la salvarea imaginii.\n");
            free(img_data);
            free(image_data);
            return 1;
        }
        free(img_data);
        free(image_data);

        printf("Imaginea a fost creata si salvata cu succes!\n");
    }
    else if (strcmp(conditie, "micsorare") == 0) {
        int scala, inaltime_noua, latime_noua;
        printf("De cate ori doriti sa micsorati?");
        scanf("%d", &scala);
        inaltime_noua = inaltime / scala;
        latime_noua = latime / scala;
        unsigned char *imagine_noua = (unsigned char *)malloc(latime_noua * inaltime_noua * 3);
        if (imagine_noua == NULL) {
            printf("Eroare la alocarea memoriei pentru imaginea nou.\n");
            free(img_data);
            return 1;
        }
        for (int i = 0; i < scala; i++) {
            reducere_pixeli(img_data, imagine_noua, inaltime, latime, scala);
        }
        if (!stbi_write_png(salvare, latime_noua, inaltime_noua, 3, imagine_noua, latime_noua * 3)) {
            printf("Eroare la salvarea imaginii.\n");
            free(img_data);
            free(imagine_noua);
            return 1;
        }
        free(img_data);
        free(imagine_noua);

        printf("Imaginea a fost creata si salvata cu succes!\n");
    }
    else if (strcmp(conditie, "niciuna") == 0) {
        char conditie2[30];
        printf("Doriti blur sau convertire in alb negru?");
        scanf("%s", conditie2);
        if (strcmp(conditie2, "convertire") == 0) {
            convertire(img_data, inaltime, latime);
            if (!stbi_write_png(salvare, latime, inaltime, 3, img_data, latime * 3)) {
                printf("Eroare la salvarea imaginii.\n");
                free(img_data);
                return 1;
            }
            free(img_data);
            printf("Imaginea a fost creata si salvata cu succes!\n");
        }
        else if (strcmp(conditie2, "blur") == 0) {
            int scala;
            printf("Cat de puternic doriti blurul?");
            scanf("%d", &scala);
            unsigned char *imagine_noua = (unsigned char *)malloc(latime * inaltime * 3);
            blur(img_data, imagine_noua, inaltime, latime, scala);
            if (!stbi_write_png(salvare, latime, inaltime, 3, imagine_noua, latime * 3)) {
                printf("Eroare la salvarea imaginii.\n");
                free(img_data);
                free(imagine_noua);
                return 1;
            }
            free(img_data);
            free(imagine_noua);

            printf("Imaginea a fost creata si salvata cu succes!\n");
        }
        else {
            printf("conditie invalida!");
            free(img_data);
        }
    }
    return 0;
}
