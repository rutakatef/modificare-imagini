#define STB_IMAGE_IMPLEMENTATION
#define MARIME_POINTER 500
#define MARIME_CONDITIE 30
#define num_pixel 3
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

struct IMG {
    int inaltime, latime;
    unsigned char *IMG_data;
};

void extindere_pixeli(unsigned char *imagine_noua, unsigned char *imagine_veche, int inaltime, int latime, int scala) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            int index = (i * latime + j) * num_pixel;
            int new_index_x = i * scala;
            int new_index_y = j * scala;
            int new_index = (new_index_x * latime * scala + new_index_y) * num_pixel;
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
            int index_actual = (i * latime + j) * num_pixel;
            if (j % scala != 0) {
                int stanga = j - 1;
                int dreapta = j + 1;
                if (stanga >= 0 && dreapta < latime) {
                    int index_stanga = (i * latime + stanga) * num_pixel;
                    int index_dreapta = (i * latime + dreapta) * num_pixel;
                    imagine[index_actual] = (imagine[index_stanga] + imagine[index_dreapta]) / 2;
                    imagine[index_actual + 1] = (imagine[index_stanga + 1] + imagine[index_dreapta + 1]) / 2;
                    imagine[index_actual + 2] = (imagine[index_stanga + 2] + imagine[index_dreapta + 2]) / 2;
                }
            }
            if (i % scala != 0) {
                int sus = i - 1;
                int jos = i + 1;
                if (sus >= 0 && jos < inaltime) {
                    int index_sus = (sus * latime + j) * num_pixel;
                    int index_jos = (jos * latime + j) * num_pixel;
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
            int index_actual = (i * latime + j) * num_pixel;
            if (j % scala != 0) {
                int stanga = j - 1;
                int dreapta = j + 1;
                if (stanga >= 0 && dreapta < latime) {
                    int index_stanga = (i * latime + stanga) * num_pixel;
                    int index_dreapta = (i * latime + dreapta) * num_pixel;
                    imagine[index_actual] = (imagine[index_stanga] + imagine[index_dreapta]) / 2;
                    imagine[index_actual + 1] = (imagine[index_stanga + 1] + imagine[index_dreapta + 1]) / 2;
                    imagine[index_actual + 2] = (imagine[index_stanga + 2] + imagine[index_dreapta + 2]) / 2;
                }
            }

      if (i % scala != 0) {
                int sus = i - 1;
                int jos = i + 1;
                if (sus >= 0 && jos < inaltime) {
                    int index_sus = (sus * latime + j) * num_pixel;
                    int index_jos = (jos * latime + j) * num_pixel;
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
            int new_index = (i * latime_noua + j) * num_pixel;
            int old_index = (i * scala *latime_veche + j * scala) * num_pixel;
            imagine_noua[new_index] = imagine_veche[old_index];
            imagine_noua[new_index + 1] = imagine_veche[old_index + 1];
            imagine_noua[new_index + 2] = imagine_veche[old_index + 2];
        }
    }

}

void convertire(unsigned char *imagine, int inaltime, int latime) {
    for (int i = 0; i < inaltime; i++) {
        for (int j = 0; j < latime; j++) {
            int index = (i * latime + j) * num_pixel;
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
                        int index = (x * latime + y) * num_pixel;

                        suma_r += imagine[index];
                        suma_g += imagine[index + 1];
                        suma_b += imagine[index + 2];
                        num_pixeli++;
                    }
                }
            }

            int index_curent = (i * latime + j) * num_pixel;
            imagine_noua[index_curent] = suma_r / num_pixeli;
            imagine_noua[index_curent + 1] = suma_g / num_pixeli;
            imagine_noua[index_curent + 2] = suma_b / num_pixeli;
        }
    }
}




int main() {
    struct IMG imagine[2];
    int  culori;
    char adresa[MARIME_POINTER], salvare[MARIME_POINTER];
    printf("Introduceti adresa imaginii: ");
    fgets(adresa, MARIME_POINTER, stdin);
    printf("Introduceti adresa in care doriti sa salvati imaginea modificata:");
    fgets(salvare, MARIME_POINTER, stdin);
    salvare[strcspn(salvare, "\n")] = '\0';
    if (strlen(salvare) > 0 && salvare[strlen(salvare) - 1] == '\n') {
        salvare[strlen(salvare) - 1] = '\0';
    }
    adresa[strcspn(adresa, "\n")] = '\0';
    if (strlen(adresa) > 0 && adresa[strlen(adresa) - 1] == '\n') {
        adresa[strlen(adresa) - 1] = '\0';
    }
    imagine[0].IMG_data = stbi_load(adresa, &imagine[0].latime, &imagine[0].inaltime, &culori, 0);
    if (imagine[0].IMG_data == NULL) {
        printf("Eroare la incarcarea imaginii.\n");
        return 1;
    }
    char conditie[MARIME_CONDITIE];
    printf("Doriti micsorare, marire sau niciuna?");
    scanf("%s", conditie);
    if (strcmp(conditie, "marire") == 0) {
        int scala;
        printf("De cate ori doriti sa mariti?");
        scanf("%d", &scala);
        imagine[1].latime = imagine[0].latime * scala;
        imagine[1].inaltime = imagine[0].inaltime * scala;
        imagine[1].IMG_data = (unsigned char *)malloc(imagine[1].latime * imagine[1].inaltime * num_pixel);
        if (imagine[1].IMG_data == NULL) {
            printf("Eroare la alocarea memoriei pentru imaginea noua.\n");
            free(imagine[0].IMG_data);
            return 1;
        }

        //copiez in imaginea noua fiecare pixel din imaginea veche la o distanta egala cu scala atat pe verticala ct si pe orizontala

        extindere_pixeli(imagine[1].IMG_data, imagine[0].IMG_data, imagine[0].inaltime, imagine[0].latime, scala);
        for (int i = 0 ; i < scala; i++) {

            //umplu pixelii de pe aceeasi linie si coloana folosind pixelii deja initializati
            //voi efectua media aritemtica la pixelii dintre cei initializati in functia extindere_pixeli de scala ori
            //pentru o claritate mai buna

            umplere_pixeli(imagine[1].IMG_data, imagine[1].inaltime, imagine[1].latime, scala);
        }
        for (int i = 0 ; i < scala; i++) {

            //voi umple restul pixelilor folosind acelasi principiu ca la umplere_pixeli numai ca pentru liniile si coloanele intermediare
            //care nu au niciun pixel initializat din imaginea principala
            //efectuez de scala ori pentru o claritate mai buna

            restul(imagine[1].IMG_data, imagine[1].inaltime, imagine[1].latime, scala);
        }
        if (!stbi_write_png(salvare, imagine[1].latime, imagine[1].inaltime, num_pixel, imagine[1].IMG_data, imagine[1].latime * num_pixel)) {
            printf("Eroare la salvarea imaginii.\n");
            free(imagine[0].IMG_data);
            free(imagine[1].IMG_data);
            return 1;
        }
        free(imagine[0].IMG_data);
        free(imagine[1].IMG_data);

        printf("Imaginea a fost creata si salvata cu succes!\n");
    }
    else if (strcmp(conditie, "micsorare") == 0) {
        int scala;
        printf("De cate ori doriti sa micsorati?");
        scanf("%d", &scala);
        imagine[1].inaltime = imagine[0].inaltime / scala;
        imagine[1].latime = imagine[0].latime / scala;
        imagine[1].IMG_data = (unsigned char *)malloc(imagine[1].latime * imagine[1].inaltime * 3);
        if (imagine[1].IMG_data == NULL) {
            printf("Eroare la alocarea memoriei pentru imaginea nou.\n");
            free(imagine[0].IMG_data);
            return 1;
        }
        for (int i = 0; i < scala; i++) {

            //copiez din imaginea veche in imaginea noua un pixel o data la scala pixeli

            reducere_pixeli(imagine[0].IMG_data, imagine[1].IMG_data, imagine[0].inaltime, imagine[0].latime, scala);
        }
        if (!stbi_write_png(salvare, imagine[1].latime, imagine[1].inaltime, num_pixel, imagine[1].IMG_data, imagine[1].latime * num_pixel)) {
            printf("Eroare la salvarea imaginii.\n");
            free(imagine[0].IMG_data);
            free(imagine[1].IMG_data);
            return 1;
        }
        free(imagine[0].IMG_data);
        free(imagine[1].IMG_data);

        printf("Imaginea a fost creata si salvata cu succes!\n");
    }
    else if (strcmp(conditie, "niciuna") == 0) {
        char conditie2[MARIME_CONDITIE];
        printf("Doriti blur sau convertire in alb negru?");
        scanf("%s", conditie2);
        if (strcmp(conditie2, "convertire") == 0) {

            //convertesc fiecare pixel din imaginea originala in gri

            convertire(imagine[0].IMG_data, imagine[0].inaltime, imagine[0].latime);
            if (!stbi_write_png(salvare, imagine[0].latime, imagine[0].inaltime, num_pixel, imagine[0].IMG_data, imagine[0].latime * num_pixel)) {
                printf("Eroare la salvarea imaginii.\n");
                free(imagine[0].IMG_data);
                return 1;
            }
            free(imagine[0].IMG_data);
            printf("Imaginea a fost creata si salvata cu succes!\n");
        }
        else if (strcmp(conditie2, "blur") == 0) {
            int scala;
            printf("Cat de puternic doriti blurul?");
            scanf("%d", &scala);
            unsigned char *imagine_noua = (unsigned char *)malloc(imagine[0].latime * imagine[0].inaltime * num_pixel);

            //creeaza o masca prin care face media aritmetica a culorilor pixelilor din jurul pixelului din poza initiala
            //si ii da valoarea acelei masti pixelului

            blur(imagine[0].IMG_data, imagine_noua, imagine[0].inaltime, imagine[0].latime, scala);
            if (!stbi_write_png(salvare, imagine[0].latime, imagine[0].inaltime, num_pixel, imagine_noua, imagine[0].latime * num_pixel)) {
                printf("Eroare la salvarea imaginii.\n");
                free(imagine[0].IMG_data);
                free(imagine_noua);
                return 1;
            }
            free(imagine[0].IMG_data);
            free(imagine_noua);
            printf("Imaginea a fost creata si salvata cu succes!\n");
        }
        else {
            printf("conditie invalida!");
            free(imagine[0].IMG_data);
        }
    }
    return 0;
}
