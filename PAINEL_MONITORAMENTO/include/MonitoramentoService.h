#ifndef MONITORAMENTO_SERVICE_H
#define MONITORAMENTO_SERVICE_H

#include <memory>
#include <string>
#include "IHardwareAdapter.h"
#include "IEstrategiaOCR.h"

class MonitoramentoService {
    private:
        std::shared_ptr<IHardwareAdapter> m_hardware;
        std::unique_ptr<IEstrategiaOCR> m_estrategiaOCR;
        std::wstring m_diretorioAlvo;

        // Varre o diretório e chama o OCR para cada imagem nova
        void processarImagensPendentes();
    
    public:
        // Injeção de dependência via construtor
        MonitoramentoService(std::shared_ptr<IHardwareAdapter> adapter, std::unique_ptr<IEstrategiaOCR> ocr);
        ~MonitoramentoService();

        void realizarVarredura();
};

#endif // MONITORAMENTO_SERVICE_H