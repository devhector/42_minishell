# 42_minishell

### Padrão de commits
 -   `test`: indica qualquer tipo de criação ou alteração de códigos de teste. **Exemplo:** Criação de testes unitários.
-   `feat`: indica o desenvolvimento de uma nova _feature a_o projeto. **Exemplo:** Acréscimo de um serviço, funcionalidade, _endpoint_, etc.
-   `refactor`: usado quando houver uma refatoração de código que não tenha qualquer tipo de impacto na lógica/regras de negócio do sistema. **Exemplo:** Mudanças de código após um _code review_
-   `style`: empregado quando há mudanças de formatação e estilo do código que **não alteram** o sistema de nenhuma forma.  
    **Exemplo:** Mudar o _style-guide_, mudar de convenção _lint_, arrumar indentações, remover espaços em brancos, remover comentários, etc..
-   `fix`: utilizado quando há correção de erros que estão gerando bugs no sistema.  
    **Exemplo:** Aplicar tratativa para uma função que não está tendo o comportamento esperado e retornando erro.
-   `chore`: indica mudanças no projeto que não afetem o sistema ou arquivos de testes. São mudanças de desenvolvimento.  
    **Exemplo:** Mudar regras do _eslint_, adicionar _prettier_, adicionar mais extensões de arquivos ao ._gitignore_
-   `docs`: usado quando há mudanças na documentação do projeto.  
    **Exemplo:** adicionar informações na documentação da API, mudar o _README_, etc.
-   `build`: utilizada para indicar mudanças que afetam o processo de build do projeto ou dependências externas.  
    **Exemplo:** _Gulp_, adicionar/remover dependências do _npm_, etc.
-   `perf`: indica uma alteração que melhorou a performance do sistema.  
    **Exemplo:** alterar _ForEach_ por _while_, melhorar a query ao banco, etc.
-   `ci`: utilizada para mudanças nos arquivos de configuração de CI.  
    **Exemplo:** _Circle_, _Travis_, _BrowserStack_, etc.
-   `revert`: indica a reverão de um _commit_ anterior.

### Fazer pull request:
[Link](https://docs.github.com/pt/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request)

### Criar nova branch:
-  `git checkout -b <nome-da-branch>`

mudar de branch:
-  `git checkout <nome-da-branch>`

deletar branch:
-  `git branch -d <nome-da-branch>`
