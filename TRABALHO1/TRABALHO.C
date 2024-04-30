#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    float y;
} Ponto;

void calcular_regressao_linear(Ponto *pontos, int tamanho) {
    int soma_x = 0;
    float soma_y = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma_x += pontos[i].x;
        soma_y += pontos[i].y;
    }

    float media_x = soma_x / (float)tamanho;
    float media_y = soma_y / (float)tamanho;

    float soma_xy = 0.0, soma_x_quadrado = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma_xy += (pontos[i].x - media_x) * (pontos[i].y - media_y);
        soma_x_quadrado += (pontos[i].x - media_x) * (pontos[i].x - media_x);
    }

    float coef_angular = soma_xy / soma_x_quadrado;
    float coef_linear = media_y - coef_angular * media_x;

    printf("Equação da regressão linear: y = %.2fx + %.2f\n", coef_angular, coef_linear);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_csv>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    int tamanho = 0;
    while (fgetc(arquivo) != EOF) {
        tamanho++;
    }
    fseek(arquivo, 0, SEEK_SET); // Voltar ao início do arquivo

    Ponto *pontos = malloc(tamanho * sizeof(Ponto));
    if (pontos == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arquivo);
        return 1;
    }

    for (int i = 0; i < tamanho; i++) {
        fscanf(arquivo, "%d,%f\n", &pontos[i].x, &pontos[i].y);
    }

    fclose(arquivo);

    calcular_regressao_linear(pontos, tamanho);

    free(pontos);

    return 0;
}