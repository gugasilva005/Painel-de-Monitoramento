#ifndef MOCK_OCR_STRATEGY_H
#define MOCK_OCR_STRATEGY_H

#include "IEstrategiaOCR.h"

class MockOCRStrategy : public IEstrategiaOCR {
    public:
        MockOCRStrategy();
        virtual ~MockOCRStrategy();

        double extrairLeitura(const std::wstring& caminhoImagem) override;
};

#endif // MOCK_OCR_STRATEGY_H