# 🚦 Temporizador One Shot com Raspberry Pi Pico W

Este projeto foi desenvolvido como parte do programa **EmbarcaTech**, tendo como objetivo a implementação de um sistema de temporização utilizando a função `add_alarm_in_ms()` do **Pico SDK**. O sistema controla LEDs que são acionados por um botão (pushbutton) e desligados de forma sequencial utilizando um temporizador de um disparo (one-shot timer).

## 🛠️ Componentes Utilizados

- 💻 **Microcontrolador:** Raspberry Pi Pico W
- 🔵 **LED Azul:** GPIO 11
- 🔴 **LED Vermelho:** GPIO 12
- 🟢 **LED Verde:** GPIO 13
- 🎛️ **Botão (Pushbutton):** GPIO 5
- ⚡ **Resistores:** 3x 330Ω

## 🎯 Funcionalidade

1. Quando o usuário pressiona o botão, os três LEDs são ligados simultaneamente.
2. Após 3 segundos, o LED azul apaga.
3. Após mais 3 segundos, o LED vermelho apaga.
4. Após mais 3 segundos, o LED verde apaga.
5. O botão só pode ser pressionado novamente após a sequência ser concluída.
6. Implementação de **debounce** via software para evitar múltiplos acionamentos indesejados.

## 📝 Código-Fonte

O código principal foi escrito em **C** utilizando o **Pico SDK**. Ele pode ser encontrado no repositório do projeto:

🔗 [Repositório do Projeto](https://github.com/guilhermejnr/led-timer-button.git)

---

Desenvolvido no programa **EmbarcaTech** 🚀

