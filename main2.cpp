#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Elemento {
    float valor;
    float peso;
};

int main() {
    int n;
    float wmax;
    
    cout << "Ingresar el número de elementos en la mochila: ";
    cin >> n;
    vector<Elemento> elementos(n);
    
    cout << "\nIngresar los elementos en la mochila:\n";
    
    for (int i = 0; i < n; i++) {
        cout << "Valor " << i + 1 << ": ";
        cin >> elementos[i].valor;
        cout << "Peso " << i + 1 << ": ";
        cin >> elementos[i].peso;
    }
    
    cout << "Peso máximo de la mochila: ";
    cin >> wmax;
    int wmax_int = static_cast<int>(wmax);

    vector<vector<float>> dp(n + 1, vector<float>(wmax_int + 1, 0));
    
    // Programación dinámica para calcular el valor máximo que se puede obtener
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= wmax_int; w++) {
            if (elementos[i - 1].peso <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - static_cast<int>(elementos[i - 1].peso)] + elementos[i - 1].valor);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    float valmax = dp[n][wmax_int];
    
    cout << "\nEl valor máximo de la mochila es: " << valmax << endl;
    
    // Recuperar los pesos que se pueden agregar a la mochila
    vector<float> pesos;
    int w = wmax_int;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            pesos.push_back(elementos[i - 1].peso);
            w -= static_cast<int>(elementos[i - 1].peso);
        }
    }
    
    cout << "Los pesos que se pueden agregar a la mochila son: ";
    for (float peso : pesos) {
        cout << peso << " ";
    }
    
    return 0;
}
