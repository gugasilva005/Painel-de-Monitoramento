#include "MonitoramentoService.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

MonitoramentoService::MonitoramentoService(std::shared_ptr<IHardwareAdapter> adapter, std::unique_ptr<IEstrategiaOCR> ocr)
    : m_hardware(adapter), m_estrategiaOCR(std::move(ocr)) {
    
    // Define o diretório atual como alvo da busca de imagens
    m_diretorioAlvo = fs::current_path().wstring();
}

MonitoramentoService::~MonitoramentoService() { }

void MonitoramentoService::realizarVarredura() {
    std::cout << "\n[Monitoramento] --- Iniciando Ciclo de Varredura ---" << std::endl;
    
    // 1. Verifica conexão com o Hardware (Adapter)
    if (m_hardware->verificarStatusEquipamento()) {
        std::cout << "[Monitoramento] STATUS: ONLINE. Hardware conectado." << std::endl;
        
        // 2. Se online, processa os dados (Strategy OCR)
        processarImagensPendentes();
        
    } else {
        std::cout << "[Monitoramento] STATUS: OFFLINE. Equipamento nao responde." << std::endl;
    }
    std::cout << "[Monitoramento] --- Fim da Varredura ---\n" << std::endl;
}

void MonitoramentoService::processarImagensPendentes() {
    std::cout << "[Monitoramento] Buscando novas imagens..." << std::endl;
    bool encontrouImagem = false;

    try {
        // Itera sobre os arquivos do diretório
        for (const auto& entry : fs::directory_iterator(m_diretorioAlvo)) {
            
            // Filtra apenas arquivos .bmp
            if (entry.is_regular_file() && entry.path().extension() == ".bmp") {
                encontrouImagem = true;
                
                // Caminho completo para o OCR
                std::wstring caminhoArquivo = entry.path().wstring();
                
                // DELEGA PARA A ESTRATÉGIA
                double valorLido = m_estrategiaOCR->extrairLeitura(caminhoArquivo);
                
                std::cout << "   -> Leitura Confirmada: " << valorLido << " m3" << std::endl;
                
                // IMPORTANTE: Deletar a imagem após leitura para não ler a mesma 2 vezes
                fs::remove(entry.path());
                std::cout << "   -> Arquivo processado e removido." << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[Monitoramento] Erro ao acessar sistema de arquivos: " << e.what() << std::endl;
    }

    if (!encontrouImagem) {
        std::cout << "[Monitoramento] Nenhuma nova imagem encontrada neste ciclo." << std::endl;
    }
}