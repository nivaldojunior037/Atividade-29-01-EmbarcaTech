# Atividade - Temporizador Periódico

Este é um repositório que armazena o projeto da primeira atividade do dia 29/01 do EmbarcaTech, a qual aborda um temporizador periódico 

## Como Usar 

Para usar o código, siga as etapas seguintes: 

1. Caso não tenha aberto ainda, abra a pasta:

Como é provável que a pasta principal esteja já clonada em seu dispositivo, basta que a pasta onde este README.md está inserido esteja aberta em seu ambiente de desenvolvimento. 

2. Execute o código em seu dispositivo: 

Certifique-se de ter as extensões e ambientes adequados à execução do código, como a Pico-SDK e o ambiente Wokwi integrado ao VS Code. Feito isso, compile o código .c e escolha se ele será executado na simulação do ambiente Wokwi integrado ou na placa BitDogLab.

3. ATENÇÃO!!!

Se optar por executar o código no Wokwi, não se preocupe com nenhuma outra ação a ser tomada. Contudo, se optar por usar a BitDogLab, é necessário manter o botão A da placa pressionado para que a sequência de luzes seja executada corretamente. Como o código foi idealizado para ser executado nos dois circuitos, foi necessário adaptar a porta GPIO 12 (a qual comporta um LED azul e não amarelo, como seria adequado à atividade) para ser ligada apenas se o botão A não estiver pressionado. Se o botão estiver pressionado, a porta GPIO 12 é substituída pela combinação dos LEDs vermelho e verde, de modo que é emitida uma luz amarelada, mesmo na BitDogLab. Por isso, reitera-se:
    SE DESEJAR USAR A BITDOGLAB, MANTENHA O BOTÃO A DA PLACA PRESSIONADO!!!

4. Execução: 

Não é necessário inserir nenhum dado durante a execução do código na BitDogLab, bastando monitorar a comunicação serial em um ambiente adequado, como o Putty ou o monitor serial do VS Code.