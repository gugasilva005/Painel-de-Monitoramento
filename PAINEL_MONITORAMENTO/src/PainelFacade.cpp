#include "PainelFacade.h"
#include "SHALocalAdapter.h"
#include "MockOCRStrategy.h"

std::unique_ptr<PainelMonitoramentoFacade> PainelMonitoramentoFacade::instance = nullptr;
std::mutex PainelMonitoramentoFacade::instanceMutex;

PainelMonitoramentoFacade::PainelMonitoramentoFacade() {
    // Inicializa subsistemas
    m_shaAdapter = std::make_shared<SHALocalAdapter>();
    auto estrategiaOCR = std::make_unique<MockOCRStrategy>();
    m_monitoramentoService = std::make_unique<MonitoramentoService>(m_shaAdapter, std::move(estrategiaOCR));
}

PainelMonitoramentoFacade& PainelMonitoramentoFacade::getInstance() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance) {
        instance.reset(new PainelMonitoramentoFacade());
    }
    return *instance;
}

void PainelMonitoramentoFacade::acionarSimulador() {
    if (m_shaAdapter) {
        m_shaAdapter->acionarEquipamento();
    }
}

void PainelMonitoramentoFacade::verificarStatus() {
    if (m_monitoramentoService) {
        m_monitoramentoService->realizarVarredura();
    }
}

void PainelMonitoramentoFacade::desligarSimulador() {
    if (m_shaAdapter) {
        m_shaAdapter->desligarEquipamento();
    }
}