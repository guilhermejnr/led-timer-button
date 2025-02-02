#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos
#define LED_BLUE 11    // GPIO11 para LED Azul
#define LED_RED 12     // GPIO12 para LED Vermelho
#define LED_GREEN 13   // GPIO13 para LED Verde
#define BUTTON_PIN 5   // GPIO5 para o Botão

// Variáveis globais
volatile bool button_enabled = true;
volatile int led_state = 0;
volatile uint32_t last_button_time = 0;
#define DEBOUNCE_TIME_MS 200

// Protótipos das funções de callback
int64_t turn_off_first_led_callback(alarm_id_t id, void *user_data);
int64_t turn_off_second_led_callback(alarm_id_t id, void *user_data);
int64_t turn_off_third_led_callback(alarm_id_t id, void *user_data);

// Função para tratar o debounce do botão
bool check_debounce() {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_button_time < DEBOUNCE_TIME_MS) {
        return false;
    }
    last_button_time = current_time;
    return true;
}

// Callbacks dos temporizadores
int64_t turn_off_first_led_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    printf("Desligando primeiro LED\n");
    add_alarm_in_ms(3000, turn_off_second_led_callback, NULL, false);
    return 0;
}

int64_t turn_off_second_led_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    printf("Desligando segundo LED\n");
    add_alarm_in_ms(3000, turn_off_third_led_callback, NULL, false);
    return 0;
}

int64_t turn_off_third_led_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    printf("Desligando terceiro LED\n");
    button_enabled = true;  // Habilita o botão novamente
    return 0;
}

// Callback do botão
void button_callback(uint gpio, uint32_t events) {
    if (!check_debounce()) return;  // Verifica debounce
    
    if (button_enabled && gpio == BUTTON_PIN) {
        if (events & GPIO_IRQ_EDGE_FALL) {  // Botão pressionado
            printf("Botão pressionado - Iniciando sequência\n");
            button_enabled = false;  // Desabilita o botão durante a sequência
            
            // Liga todos os LEDs
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 1);
            
            // Inicia a sequência de desligamento
            add_alarm_in_ms(3000, turn_off_first_led_callback, NULL, false);
        }
    }
}

int main() {
    // Inicializa o stdio
    stdio_init_all();
    
    // Configura os LEDs
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    // Configura o botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    // Loop principal
    while (true) {
        sleep_ms(100);  // Pequeno delay para reduzir uso do processador
    }
}