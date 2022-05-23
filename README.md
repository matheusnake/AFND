# AFND

Trabalho 2 que simula um autômato finito não-determinístico.

Objeto que contem um tripla.

```
class AFND {
    public:
        AFND(string line){
            vector<string> w = split(line);
            state = w.at(0);
            word = w.at(1);
            nextState = w.at(2);
        };
        ~AFND(){};
        string word,state,nextState;
};

```

Função que pega a entrada digitada e separa dos espação em um vector.

```
vector<string> split (const string &s) {
        vector<string> result;
        stringstream ss (s);
        string item;

        while (getline (ss, item, ' ')) {
            result.push_back (item);
        }
        
        return result;
}
```

Com o fornecimento das entradas, as triplas são guardadas em um std::list<AFND> (lista dos objetos "AFND") e as entradas são todas guardadas em vectors.

```
std::list<AFND> list;
```
  
  Após isto, é testado o conjunto de palavras que irá ser testada na maquina de estados, após separar as palavras, para cada letra ela é enviada para a função sim, que irá retornar a palavra conseguiu atingir o estado final espercificado ou não.

```
    for (int i = 0; i<(int)words.size(); i++) {

        string wPointer = words.at(i);
        stateA = stateInit;

        if(sim(list,wPointer,stateInit,stateFinal)) cout << "S" << endl;
        else cout << "N" << endl;

    }
    
```

 A função "sim" irá ter o seguinte sequencia

- Pegar o conjunto de palavras e analisar um por vez
- Iniciar no estado incial introduzido anteoriamente
- Pecorrerá a lista analisando na sequencia = (estado,palavra)
- Armazenará o proximo estado na lista helper
- Após pecorrer toda a lista do automato, atualizará a lista de estados finais atingindos final_states
- Por fim retornará um booleano se o automato chegou no estado final sugerido.

```
 bool sim(list<AFND> afndL, string w, string init,vector<string> final){

    std::list<string> final_states,helper;
    final_states.insert(final_states.begin(),init);

    for(int k=0; k<(int)w.size(); k++) {
        helper.clear();
        for (auto x : final_states){
                for (const AFND & afnd : afndL) {                    
                    if(x == afnd.state){
                        if(afnd.word.at(0) == w[k]){                 
                            helper.insert(helper.end(),afnd.nextState);
                        }                    
                    }
                }
        }
        final_states = helper;
    }

    bool warning = false;  
        for (auto u : final_states){
            for(auto x : final){
                if(x == u){
                    return true;
                }
            }
        } 
    return warning;
}
```
Como espercificado no problema, S para sim, N para não, se o AFD reconhece a palavra.
                                  
