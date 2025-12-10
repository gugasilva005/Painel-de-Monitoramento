#include <iostream>
#include <thread>
#include <chrono>
#include <cstdio>
#include "PainelFacade.h"

#ifdef _WIN32
#include <windows.h>
#endif

// Função auxiliar para pausa
void pausar(const char* msg) {
    std::cout << ">>> " << msg << " (Pressione ENTER) <<<";
    std::cin.ignore();
    std::cout << std::endl;
}

int main() {
    // Configura o console no Windows para garantir saída visível
    #ifdef _WIN32
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    #endif

    std::cout << "==============================================\n";
    std::cout << "      PAINEL DE MONITORAMENTO (CLIENTE)       \n";
    std::cout << "==============================================\n\n";

    // Acesso via Singleton
    PainelMonitoramentoFacade& painel = PainelMonitoramentoFacade::getInstance();

    std::cout << "Cenario: O Painel esta rodando, mas o Hardware (SHA) esta desligado.\n";
    pausar("Passo 1: Tentar detectar hardware");
    
    // 1. Tenta detectar (Deve falhar)
    painel.verificarStatus();

    pausar("Passo 2: Enviar comando de acionamento remoto");

    // 2. Aciona o executável externo
    painel.acionarSimulador();

    std::cout << "Aguardando inicializacao do hardware externo (5s)...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    pausar("Passo 3: Iniciar Monitoramento Continuo (Pressione ENTER)");

    std::cout << "[Monitoramento] Iniciando loop de leitura por 10 segundos...\n";

    // LOOP DE MONITORAMENTO (10 ciclos)
    for (int i = 0; i < 10; i++) {
        std::cout << "\n>>> Ciclo " << (i + 1) << "/10 <<<\n";
        
        // O Painel verifica status e busca imagens
        painel.verificarStatus();
        
        // Espera 2 segundos antes da próxima leitura (para dar tempo do SHA gerar nova imagem)
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "\nTeste concluido. O Painel monitorou o SHA com sucesso.\n";
    pausar("Pressione ENTER para encerrar e desligar o SHA");

    painel.desligarSimulador();

    return 0;
}