#ifndef I_ESTRATEGIA_OCR_H
#define I_ESTRATEGIA_OCR_H

#include <string>

class IEstrategiaOCR {
    public:
        virtual ~IEstrategiaOCR() = default;

        // Recebe o caminho do arquivo e retorna o valor lido (simulado ou real)
        virtual double extrairLeitura(const std::wstring& caminhoImagem) = 0;
};

#endif // I_ESTRATEGIA_OCR_H