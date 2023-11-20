# Projeto de Monitoramento Ambiental com NodeMCU, DHT11 e MQTT

## Descrição do Projeto:
Este repositório contém o código-fonte e documentação do projeto de monitoramento ambiental utilizando NodeMCU, sensor DHT11 e MQTT. O sistema é projetado para medir a temperatura e umidade ambiente, enviando os dados para um servidor MQTT para posterior análise.

## Funcionamento e Uso

O sistema é iniciado quando o NodeMCU se conecta à rede Wi-Fi configurada. Em seguida, o sensor DHT11 realiza leituras periódicas de temperatura e umidade. Os dados são formatados em mensagens JSON e enviados para um servidor MQTT, permitindo o monitoramento remoto em tempo real.

## Hardware Utilizado

**Microcontrolador:** NodeMCU ESP8266.

**Sensor:** DHT11 para medição de temperatura e umidade.

**Atuador:** Buzzer Ativo 3V

**Outros:** Protoboard, Jumpers

## Como Reproduzir:

Clone este repositório: 
```bash
    git clone https://github.com/seu-usuario/nome-do-repo.git
```
Siga as instruções de montagem no diretório /docs para conectar o NodeMCU e o sensor DHT11.

Carregue o código-fonte do projeto para o NodeMCU.

Acesse o servidor MQTT configurado e subscreva-se aos tópicos relevantes para receber os dados.


## Licença

Este projeto é distribuído sob a licença MIT. Consulte o arquivo [MIT license](LICENSE) para obter mais detalhes.
