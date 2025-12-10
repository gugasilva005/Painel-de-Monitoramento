#ifndef I_HARDWARE_ADAPTER
#define I_HARDWARE_ADAPTER

#include <string>

class IHardwareAdapter {
    public:
        virtual ~IHardwareAdapter() = default;

        // Liga o equipamento (lança o processo externo)
        virtual void acionarEquipamento() = 0;

        // Desliga o equipamento
        virtual void desligarEquipamento() = 0;

        // Verifica se o equipamento está respondendo (se o processo/janela existe)
        virtual bool verificarStatusEquipamento() = 0;
};

#endif  // I_HARDWARE_ADAPTER