#include "MockOCRStrategy.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

MockOCRStrategy::MockOCRStrategy() { }

MockOCRStrategy::~MockOCRStrategy() { }

double MockOCRStrategy::extrairLeitura(const std::wstring& caminhoImagem) {
    // LOG: Mostra que o arquivo chegou nesta camada
    std::wcout << L"[OCR Strategy] Analisando Imagem: " << caminhoImagem << std::endl;

    // Simula um tempo de processamento de imagem 
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Gera um valor aleatório entre 100.0 e 500.0 para simular um SHA
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(100.0, 500.0);

    double valorSimulado = dis(gen);

    return valorSimulado;
}