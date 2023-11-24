// Programa em C++ para implementar o algoritmo de Cohen-Sutherland
// para recorte de linhas.
#include <iostream>
using namespace std;

// Definindo códigos de região
const int DENTRO = 0; // 0000
const int ESQUERDA = 1; // 0001
const int DIREITA = 2; // 0010
const int INFERIOR = 4; // 0100
const int SUPERIOR = 8; // 1000

// Definindo x_max, y_max e x_min, y_min para
// retângulo de recorte. Como pontos diagonais são
// suficientes para definir um retângulo
const int x_max = 100;
const int y_max = 100;
const int x_min = -100;
const int y_min = -100;

// Função para calcular o código de região para um ponto (x, y)
int calcularCodigo(double x, double y)
{
    // inicializado como estando dentro
    int codigo = DENTRO;

    if (x < x_min) // à esquerda do retângulo
        codigo |= ESQUERDA;
    else if (x > x_max) // à direita do retângulo
        codigo |= DIREITA;
    if (y < y_min) // abaixo do retângulo
        codigo |= INFERIOR;
    else if (y > y_max) // acima do retângulo
        codigo |= SUPERIOR;

    return codigo;
}

// Implementando o algoritmo de Cohen-Sutherland
// Recortando uma linha de P1 = (x1, y1) para P2 = (x2, y2)
void cohenSutherlandClip(double x1, double y1,
                          double x2, double y2)
{
    // Calcular códigos de região para P1, P2
    int codigo1 = calcularCodigo(x1, y1);
    int codigo2 = calcularCodigo(x2, y2);

    // Inicializar a linha como fora da janela retangular
    bool aceito = false;

    while (true)
    {
        if ((codigo1 == 0) && (codigo2 == 0))
        {
            // Se ambos os pontos finais estiverem dentro do retângulo
            aceito = true;
            break;
        }
        else if (codigo1 & codigo2)
        {
            // Se ambos os pontos finais estão fora do retângulo,
            // na mesma região
            break;
        }
        else
        {
            // Algum segmento da linha está dentro do
            // retângulo
            int codigo_fora;
            double x, y;

            // Pelo menos um ponto final está fora do
            // retângulo, escolha-o.
            if (codigo1 != 0)
                codigo_fora = codigo1;
            else
                codigo_fora = codigo2;

            // Encontrar ponto de interseção;
            // usando fórmulas y = y1 + inclinação * (x - x1),
            // x = x1 + (1 / inclinação) * (y - y1)
            if (codigo_fora & SUPERIOR)
            {
                // ponto está acima do retângulo de recorte
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (codigo_fora & INFERIOR)
            {
                // ponto está abaixo do retângulo
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (codigo_fora & DIREITA)
            {
                // ponto está à direita do retângulo
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (codigo_fora & ESQUERDA)
            {
                // ponto está à esquerda do retângulo
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Agora, o ponto de interseção x, y é encontrado
            // Substituímos o ponto fora do retângulo
            // pelo ponto de interseção
            if (codigo_fora == codigo1)
            {
                x1 = x;
                y1 = y;
                codigo1 = calcularCodigo(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                codigo2 = calcularCodigo(x2, y2);
            }
        }
    }
    if (aceito)
    {
        cout << "Linha aceita de " << x1 << ", "
             << y1 << " para " << x2 << ", " << y2 << endl;
        // Aqui o usuário pode adicionar código para exibir o retângulo
        // junto com as linhas aceitas (parte)
    }
    else
        cout << "Linha rejeitada" << endl;
}

// Código principal
int main()
{
    // Primeiro segmento de linha
    // P11 = (5, 5), P12 = (7, 7)
    cohenSutherlandClip(-180, 40, 50, 10);

    // Segundo segmento de linha
    // P21 = (7, 9), P22 = (11, 4)
    cohenSutherlandClip(120, 30, 150, 40);

    // Terceiro segmento de linha
    // P31 = (1, 5), P32 = (4, 1)
    cohenSutherlandClip(-120, 30, 30, 255);

    return 0;
}
