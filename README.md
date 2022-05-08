# comunicacao-entre-processos

1 Questão: 
No problema do jantar dos filósofos, deixe o protocolo a seguir ser usado: um filósofo de número par sempre pega o seu garfo esquerdo antes de pegar o direito; um filósofo de número ímpar sempre pega o garfo direito antes de pegar o esquerdo. Esse protocolo vai garantir uma operação sem impasse?

R: SIM, devido ao fato de que se um filosofo par pega primeiro garfo da esquerda e o impar pega primeiro o garfo da direita, eles não vao competir o mesmo garfo.
EX:

0 | 1 | 2 | 3 | 4 | --> 0 | 1 | 2 / 3 | 4 \ --> note que o garfo entre o filosofo 3 e o filoso 4 esta vago para um dos dois pegarem fazendo com que um dos dois coma e consequentemente o outro tambem, evitando o deadlock.

2 Questão: 
Suponha que um hospital veterinário queira implementar o seguinte protocolo: se um cachorro está na sala de repouso, outros cachorros podem entrar, mas nenhum gato, e vice-versa. Um sinal com uma placa móvel na porta de cada sala de repouso indica em quais dos três estados possíveis a sala pode se encontrar:

- Vazia
- Cachorros presentes
- Gatos presentes

Utilizando linguagem C escreva as seguintes rotinas: dogWantsToEnter, catWantsToEnter, dogLeaves, catLeaves. Você pode usar as técnicas de sincronização e contadores que quiser.

R: Código da segunda questão

3 Questão:
Escreva um problema baseado no produtor-consumidor que use threads e compartilhe de um buffer comum. Você pode usar as técnicas de sincronização e contadores que quiser. Discuta sua solução.

R: O problema de produtor-consumidor criado pela equipe se baseia em um array que é o buffer e possui N posições, e a forma de evitar as condições de corrida foi criar uma thread para cada produtor e consumidor dessa forma, utilizando o mutex poderia restringir que entra na região critica. Contudo além de se preocupar com a região critica deve-se criar um contador para saber quando o array do buffer esta completo para assim deixar em modo de espera tanto o produtor como o consumidor quando necessário.
