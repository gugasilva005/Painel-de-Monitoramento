#ifndef PAINEL_FACADE_H
#define PAINEL_FACADE_H

#include <memory>
#include <mutex>
#include "MonitoramentoService.h"

class SHALocalAdapter;

class PainelMonitoramentoFacade {
    private:
        static std::unique_ptr<PainelMonitoramentoFacade> instance;
        static std::mutex instanceMutex;

        // Subsistemas
        std::unique_ptr<MonitoramentoService> m_monitoramentoService;
        std::shared_ptr<SHALocalAdapter> m_shaAdapter;

        // Construtor Privado
        PainelMonitoramentoFacade();

    public:
        PainelMonitoramentoFacade(const PainelMonitoramentoFacade&) = delete;
        PainelMonitoramentoFacade& operator=(const PainelMonitoramentoFacade&) = delete;

        static PainelMonitoramentoFacade& getInstance();

        void acionarSimulador();
        void verificarStatus();
        void desligarSimulador();
};

#endif // PAINEL_FACADE_H