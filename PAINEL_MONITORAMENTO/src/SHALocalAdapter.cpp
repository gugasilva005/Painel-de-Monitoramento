#include "SHALocalAdapter.h"
#include <windows.h>
#include <shellapi.h>
#include <iostream>

// Sistema Hidrométrico - Hidrômetro Real
// Simulador de Hidrômetro
const wchar_t* SHALocalAdapter::NOME_JANELA_SHA = L"Sistema Hidrométrico - Hidrômetro Real";
const wchar_t* SHALocalAdapter::EXECUTAVEL_SHA = L"SimuladorSHA.exe";

SHALocalAdapter::SHALocalAdapter() { }

SHALocalAdapter::~SHALocalAdapter() { }

void SHALocalAdapter::acionarEquipamento() {
    std::cout << "[Adapter SHA] Tentando lancar processo externo: SimuladorSHA.exe..." << std::endl;

    // SW_SHOW abre a janela visível
    HINSTANCE result = ShellExecuteW(NULL, L"open", EXECUTAVEL_SHA, L"--auto", NULL, SW_SHOW);

    if ((intptr_t)result > 32) {
        std::cout << "[Adapter SHA] Processo iniciado com sucesso" << std::endl;
    } else {
        std::cerr << "[Adapter SHA] ERRO: Nao foi possivel encontrar 'SimuladorSHA.exe'." << std::endl;
    }
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    wchar_t class_name[80];
    wchar_t title[80];
    GetClassNameW(hwnd, class_name, sizeof(class_name));
    GetWindowTextW(hwnd, title, sizeof(title));

    // Se encontrar algo parecido, avisa no console
    if (wcsstr(title, L"Hidrômetro") || wcsstr(title, L"Hidrometro")) {
        std::wcout << L"[DEBUG] Janela candidata encontrada: '" << title << L"'" << std::endl;
    }
    return TRUE;
}

bool SHALocalAdapter::verificarStatusEquipamento() {
    // Tenta encontrar a janela exata
    HWND hwnd = FindWindowW(NULL, NOME_JANELA_SHA);

    if (hwnd == NULL) {
        // Se falhar, roda o debug para ver se ela está lá com outro nome
        EnumWindows(EnumWindowsProc, 0); 
        return false;
    }
    return true;
}

void SHALocalAdapter::desligarEquipamento() {
    HWND hwnd = FindWindowW(NULL, NOME_JANELA_SHA);
    if (hwnd != NULL) {
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        std::cout << "[Adapter] Sinal de desligamento enviado para o hardware remoto." << std::endl;
    }
}