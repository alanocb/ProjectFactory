
![iade-logo](https://github.com/alanocb/ProjectFactory/assets/99679262/f7c9ca45-15a6-4dfe-93aa-b28cc2fd8867)

# Project Factory
# Computação física e IOT

![smartcamp](https://github.com/alanocb/ProjectFactory/assets/99679262/b3b81274-1b1b-438d-8809-49ef4b894c44)

### Autores
- Alano Baptista – 20190818
- Luquenia Galiano – 20210451

## Arquitetura do Sistema

### ESP8266
O ESP8266 desempenha um papel fundamental no sistema, servindo como ponte entre os dispositivos físicos e a internet. Suas principais funções incluem:

- **Conexão à Internet**: Capaz de se conectar a redes Wi-Fi, o ESP8266 permite que o sistema aceda à internet, proporcionando conectividade contínua e comunicação remota.
- **Interface para Controladores**: Atua como uma interface para dispositivos como LEDs, sensores e outros controladores físicos. Ele recebe solicitações HTTP e JSON do servidor Node.js ou da aplicação móvel, interpreta esses comandos e os traduz em ações físicas nos dispositivos conectados. Isto garante uma comunicação eficaz entre o sistema central e os dispositivos periféricos, proporcionando uma resposta rápida e coordenada às necessidades dos utilizadores.
- **Recolha de Dados de Sensores**: Além de controlar dispositivos, o ESP8266 recolhe dados de sensores conectados a ele. Esses dados podem ser enviados para o servidor para processamento posterior ou fornecidos em tempo real para a aplicação móvel, permitindo o monitoramento contínuo e a tomada de decisões informadas.

### Servidor Node.js
O servidor Node.js é o núcleo do sistema, agindo como uma ponte entre o ESP8266 e a aplicação móvel. Suas principais funções incluem:

- **Interface de Comunicação**: Fornece uma API RESTful que permite a comunicação entre o ESP8266 e a aplicação móvel por meio de endpoints definidos, como /led, /temperature, /humidity, etc. Isto facilita a troca de informações de forma padronizada e segura.
- **Recepção de Solicitações do ESP8266**: Processa as solicitações recebidas do ESP8266, atualizando o estado interno do sistema conforme necessário. O servidor pode responder ao ESP8266 com confirmações ou outras informações relevantes, garantindo a sincronia do sistema.
- **Comunicação com a Aplicação Móvel**: Responde às solicitações da aplicação móvel, fornecendo dados de sensores ou encaminhando comandos para o ESP8266 para execução. Isto assegura que os utilizadores possam monitorizar e controlar os dispositivos de forma eficiente e em tempo real.

### Aplicação Móvel (Android Studio)
A aplicação móvel serve como interface do utilizador para o sistema, permitindo que os utilizadores monitorizem e controlem os dispositivos conectados. Suas principais funções incluem:

- **Interface de Utilizador**: Oferece uma interface gráfica intuitiva para interação com o sistema, incluindo botões para ligar/desligar dispositivos e para exibir dados de sensores. A interface é projetada para ser fácil de usar, permitindo que utilizadores de diferentes níveis de habilidade possam interagir com o sistema sem dificuldade.
- **Interação com o Servidor Node.js**: Comunica-se com o servidor Node.js para obter informações sobre o estado dos dispositivos e enviar comandos para controlá-los via requisições HTTP para os endpoints definidos. Isto permite que os utilizadores mantenham controle sobre os dispositivos de maneira centralizada.
- **Exibição de Dados de Sensores**: Exibe dados de sensores em tempo real, atualizando a interface do utilizador conforme as informações são recebidas do servidor. Isto permite um monitoramento contínuo e a visualização de tendências ou mudanças nas condições monitorizadas.

![Screenshot 2024-06-02 113152](https://github.com/alanocb/ProjectFactory/assets/99679262/63ba4861-2112-41fd-bbb3-4371a570bc6b)


## Descrição Atual do Projeto

### LED (Iluminação Exterior)
- **Função**: O LED é um componente de iluminação essencial em nossa tenda, usado para iluminação exterior.
- **Controle**: Através do ESP8266, podemos ligar e desligar o LED remotamente, proporcionando controle de iluminação para os usuários por meio da aplicação móvel.

### LED RGB (KY-016) (Iluminação Interior)
- **Função**: O LED RGB KY-016 é utilizado para iluminação interior da tenda.
- **Controle de Cor**: Através da aplicação móvel, os usuários podem controlar a cor do LED RGB, escolhendo entre diversas opções para criar a atmosfera desejada dentro da tenda.

### Sensor de Temperatura e Umidade (KY-015)
- **Função**: O sensor de temperatura e umidade KY-015 é utilizado para monitorar as condições ambientais dentro da tenda.
- **Dados**: Através do ESP8266, os dados de temperatura e umidade são coletados pelo sensor KY-015 e enviados para o servidor Node.js.
- **Monitoramento**: Esses dados são então disponibilizados na aplicação móvel, permitindo aos usuários monitorar as condições internas da tenda em tempo real e tomar medidas apropriadas conforme necessário.

### Sensor de Batimentos Cardíacos (KY-039)
- **Função**: O sensor KY-039 é utilizado para verificar os batimentos cardíacos dos usuários.
- **Coleta de Dados**: Através do ESP8266, os dados de BPM (batimentos por minuto) são coletados pelo sensor KY-039 e enviados para o servidor Node.js.
- **Monitoramento**: Esses dados são disponibilizados na aplicação móvel, permitindo aos usuários monitorar seus batimentos cardíacos em tempo real.

### Alarme de Incêndio (KY-026, KY-012, LED Vermelho)
- **Função**: O sistema de alarme de incêndio é composto pelos sensores KY-026 e KY-012, juntamente com um LED vermelho.
- **Deteção**: Quando o sensor de chama KY-026 deteta uma possível ameaça de incêndio, ele ativa o sensor KY-012 e aciona o LED vermelho para alertar os usuários sobre a emergência.
- **Coordenação**: O ESP8266 coordena essa ação, garantindo uma resposta rápida e eficaz em caso de incêndio na tenda.

### Caixote do Lixo Automático (HC-SR501 e Servo Motor)
- **Função**: O sensor de movimento HC-SR501 deteta a presença de movimento dentro da tenda.
- **Ação**: Quando ativado, o ESP8266 aciona o servo motor para abrir a tampa do caixote do lixo, permitindo aos usuários descartar resíduos de forma conveniente e higiênica.
- **Integração**: Essa integração entre o sensor de movimento e o servo motor oferece uma solução eficaz para a gestão de resíduos na tenda, promovendo uma experiência mais limpa e organizada para os usuários.

## Aplicação Móvel (Android Studio)
A aplicação móvel é a interface principal para os utilizadores interagirem com o sistema, oferecendo uma variedade de funcionalidades para monitorizar e controlar os dispositivos conectados. As principais características da aplicação incluem:

### Controle de Iluminação Exterior
- **Luzes Exteriores**: A aplicação móvel permite aos utilizadores ligar e desligar os LEDs exteriores com um simples toque num botão. Esta funcionalidade proporciona controlo fácil e rápido da iluminação exterior da tenda.

### Controle de Iluminação Interior
- **Controle de Cor do LED RGB Interior**: Através da aplicação, os utilizadores podem selecionar e ajustar as cores do LED RGB KY-016 interior, permitindo a criação de diferentes ambientes dentro da tenda. A aplicação fornece uma paleta de cores ou um selector de cores para fácil personalização.

### Monitorização de Sensores
- **Verificação de Temperatura e Humidade**: A aplicação exibe dados em tempo real do sensor KY-015, permitindo aos utilizadores monitorizar a temperatura e a humidade dentro da tenda. Os dados são apresentados em gráficos e/ou indicadores numéricos, facilitando a interpretação.
- **Monitorização de Batimentos Cardíacos**: Os dados de BPM recolhidos pelo sensor KY-039 são exibidos na aplicação, permitindo que os utilizadores monitorizem os seus batimentos cardíacos em tempo real. Esta funcionalidade é particularmente útil para a gestão da saúde e bem-estar dos utilizadores.

## Circuito Atual do Projeto

### Circuito Caixote de Lixo Automático

![caixote-de-lixo-circuito](https://github.com/alanocb/ProjectFactory/assets/99679262/854f671d-e6d7-472e-b951-06d9e85e0fe5)

Devido à limitação de pinos e para garantir que o caixote de lixo funcione de forma independente da tenda, decidimos separar este componente utilizando um outro ESP8266 dedicado. As principais razões e benefícios dessa abordagem incluem:

- **Independência Operacional**: O uso de um ESP8266 separado para o caixote de lixo automático assegura que ele possa operar de forma autônoma, sem depender da funcionalidade geral da tenda. Isto é particularmente útil para manutenção e atualizações, permitindo que o caixote de lixo continue a funcionar mesmo se o sistema principal da tenda estiver temporariamente inoperante.
- **Limitação de Pinos**: O ESP8266 tem um número limitado de pinos GPIO disponíveis. Ao dedicar um ESP8266 exclusivamente ao caixote de lixo, podemos evitar a sobrecarga do microcontrolador principal, garantindo que ambos os sistemas (tenda e caixote de lixo) tenham pinos suficientes para todas as suas funcionalidades.
- **Eficiência de Processamento**: Separar as funções em diferentes microcontroladores pode melhorar a eficiência do sistema como um todo. Cada ESP8266 pode concentrar-se nas suas tarefas específicas sem concorrência pelos recursos de processamento, resultando em respostas mais rápidas e operações mais fiáveis.

Desta forma, o circuito do caixote de lixo automático é projetado com um ESP8266 dedicado, ligado ao sensor de movimento HC-SR501 e ao servo motor responsável pela abertura da tampa.

### Circuito Tenda

![tenda-circuito](https://github.com/alanocb/ProjectFactory/assets/99679262/6bef2bf7-c29d-48dc-891c-ad55ab7246f9)


## Imagens da tenda (colaboração com Licenciatura de Design)

- Poster (informações da tenda)

![Design tenda](https://github.com/alanocb/ProjectFactory/assets/99679262/c15c85bd-1afb-40a1-8155-081dbe3de740)

![Poster](https://github.com/alanocb/ProjectFactory/assets/99679262/feb3cbca-7b82-4cf4-9da2-d8a84f716249)

- Circuito Montado com todos os sensores preparados

![tenda-real-circuito](https://github.com/alanocb/ProjectFactory/assets/99679262/7d7180ff-9013-4076-af9e-a026559dc32f)

- Tenda Preparada para a apresentação

![tenda-real-finalizada](https://github.com/alanocb/ProjectFactory/assets/99679262/59085493-c133-4d2e-8cd3-e157f747c1eb)

