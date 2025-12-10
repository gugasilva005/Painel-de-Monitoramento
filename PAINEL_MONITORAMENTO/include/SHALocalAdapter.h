#ifndef SHA_LOCAL_ADAPTER
#define SHA_LOCAL_ADAPTER

#include "IHardwareAdapter.h"

class SHALocalAdapter : public IHardwareAdapter {
    private:
        static const wchar_t* NOME_JANELA_SHA;
        static const wchar_t* EXECUTAVEL_SHA;

    public:
        SHALocalAdapter();
        virtual ~SHALocalAdapter();

        void acionarEquipamento() override;
        void desligarEquipamento() override;
        bool verificarStatusEquipamento() override;
};

#endif // SHA_LOCAL_ADAPTER