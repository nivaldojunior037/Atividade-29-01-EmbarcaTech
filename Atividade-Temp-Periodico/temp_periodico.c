// Declaração das bibliotecas necessárias para a execução do código
#include <stdio.h>
#include "pico/stdlib.h"   
#include "hardware/timer.h" 

#define LED_PIN_GREEN 11        //Definição da porta GPIO do LED vermelho do conjunto RGB
#define LED_PIN_YELLOW 12       //Definição da porta GPIO do LED amarelo (azul do conjunto RGB)
#define LED_PIN_RED 13          //Definição da porta GPIO do LED verde do conjunto RGB
#define BUTTON_A 5              //Definição da porta GPIO do botão A


static volatile int a = 1;      //Declaração da variável que determinará qual LED será aceso
static volatile int estado = 1; //Declaração da variável que determinará a mensagem emitida a cada 1000 ms

// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
bool repeating_timer_callback(struct repeating_timer *t) {
    estado = a;                                     //Atualização da variável estado

    // Se o código for executado na BitDogLab, o botão A deve estar pressionado
    // Cada LED será aceso a depender do valor de a
    if(gpio_get(BUTTON_A) == 0){ 
        if(a == 3){                         //O LED verde será aceso
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_GREEN, true);
            a++;
        } else if(a == 2){                  //Combinação de LEDS que mostrará cor amarela
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_GREEN, true);
            a++;
        } else if(a == 1){                  //O LED vermelho será aceso
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_GREEN, false);
            a++;
        } 

    // Caso o botão não esteja pressionado, os LEDs serão acesos como planejado para o circuito criado no Wokwi
    } else {  
        if(a == 3){                             //O LED verde será aceso
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_YELLOW, false);
            gpio_put(LED_PIN_GREEN, true);
            a++;
        } else if(a == 2){                      //O LED amarelo será aceso
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_YELLOW, true);
            gpio_put(LED_PIN_GREEN, false);
            a++;
        } else if(a == 1){                      //O LED vermelho será aceso
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_YELLOW, false);
            gpio_put(LED_PIN_GREEN, false);
            a++;
        } 

    }
    // Se a chegar a 4, é retornado a 1 para que o ciclo de luzes recomece
    if(a > 3){ 
        a = 1;
    }
    
    return true;
}

int main() {

    // Iniciaização da biblioteca para comunicação serial
    stdio_init_all();
    
    // Inicialização dos LEDs e definição como saídas
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,GPIO_OUT);

    // Inicialização dos botão A, definição como entrada e ativação de pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Declaração de uma estrutura de temporizador de repetição
    // Esta estrutura armazenará informações sobre o temporizador configurado
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 3 segundos
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução
    while (true) {
        
        //A cada 1 segundo é emitida uma mensagem que declara a luz emitida no momento
        //Como cada estado de LED dura 3 segundos, devem ser emitidas 3 mensagens a cada estado
        if(estado == 1){
            printf("Luz de semáforo atual: Vermelho\n");
            sleep_ms(1000);
        } else if(estado == 2){
            printf("Luz de semáforo atual: Amarelo\n");
            sleep_ms(1000);
        } else if(estado == 3){
            printf("Luz de semáforo atual: Verde\n");
            sleep_ms(1000);
        }
    }
    return 0;
}
