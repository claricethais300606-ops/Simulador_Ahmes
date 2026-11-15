 <div align="center">

# Simulador Ahmes

**Simulador didático de um processador de 8 bits desenvolvido em linguagem C.**

![C](https://img.shields.io/badge/Linguagem-C-00599C?style=flat-square&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/Compilador-GCC-555555?style=flat-square)
![UNIR](https://img.shields.io/badge/UNIR-Ciência%20da%20Computação-174A35?style=flat-square)

</div>

---

## Sobre o projeto

O **Simulador Ahmes** é um projeto desenvolvido como atividade avaliativa da disciplina de **Organização e Arquitetura de Computadores**, do curso de Ciência da Computação da **Universidade Federal de Rondônia (UNIR)**.

Inspirado no simulador Neander, o projeto busca representar o funcionamento de um processador de 8 bits, permitindo observar, na prática, a execução de instruções, o comportamento dos registradores e as operações realizadas pela CPU.

A aplicação é desenvolvida em **linguagem C**, com uma arquitetura modular e interface interativa em terminal.

## Funcionalidades

- Execução de instruções passo a passo.
- Execução contínua de programas.
- Visualização dos registradores AC, PC e IR.
- Monitoramento das flags do processador.
- Operações aritméticas, lógicas e de deslocamento.
- Reinicialização da CPU.
- Tratamento de erros e controle de execução.

## Estrutura do projeto

```text
Simulador_Ahmes/
├── src/
│   ├── main.c
│   ├── nucleo/
│   │   ├── processador.c / .h
│   │   ├── memoria.c / .h
│   │   ├── instrucoes.c / .h
│   │   ├── ciclo.c / .h
│   │   └── ula.c / .h
│   └── interface/
│       ├── interface.c / .h
│       └── controle.c / .h
├── tests/
├── Makefile
├── compilar_windows.bat
└── README.md
```

## Como executar

**Requisito:** compilador GCC instalado.

No Windows, abra o terminal na raiz do projeto e execute:

```powershell
.\compilar_windows.bat
.\build\ahmes.exe
```

Para executar os testes:

```powershell
.\build\ahmes.exe --testes
```

## Informações acadêmicas

| | |
|---|---|
| **Instituição** | Universidade Federal de Rondônia — UNIR |
| **Curso** | Ciência da Computação |
| **Disciplina** | Organização e Arquitetura de Computadores |
| **Tipo** | Trabalho acadêmico avaliativo |
| **Linguagem** | C |

---

<div align="center">

Desenvolvido para fins acadêmicos e educacionais.

**Universidade Federal de Rondônia — UNIR · 2026**

</div>
