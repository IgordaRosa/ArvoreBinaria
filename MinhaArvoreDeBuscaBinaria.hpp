#ifndef MINHAARVOREDEBUSCABINARIA_HPP
#define MINHAARVOREDEBUSCABINARIA_HPP

#include "ArvoreDeBuscaBinaria.hpp"
#include <cassert>
#include <utility>

/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template<typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
    /*
    LEMBRETE
    -sempre que mexer com recursividade, deve-se trabalhar com constantes para os dados não se perderem
    -criar outro metodo pra chamar a recursividade
    -


    */
    protected:

    Nodo<T> * NodoRaiz = this->_raiz;

    Nodo<T> * BuscaNaArvore(Nodo<T> * nodo, T chave) const
    {
        while(nodo != nullptr and nodo->chave != chave)
        {
            if(nodo->chave < chave)
            {
                nodo = nodo->filhoDireita;
            }
            else
            {
                nodo = nodo->filhoEsquerda;
            }
        }
        return nodo;
    };

    public:
    ///////////////////////////////////////////////////////////////////////
    ~MinhaArvoreDeBuscaBinaria() override
    {

    };

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    bool vazia() const override
    {
        if(NodoRaiz == nullptr)
        {
             return true;
        }
        return false;
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    int quant(Nodo<T> * nodo) const
    {
        if(nodo == nullptr)
        {
            return 0;
        }
        return 1 + this->quant(nodo->filhoEsquerda) + this->quant(nodo->filhoDireita);
    };

    public:
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    int quantidade() const override
    {
        return this->quant(this->NodoRaiz);
    };

    ///////////////////////////////////////////////////////////////////////

    public:
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    bool contem(T chave) const override
    {
        Nodo<T> * nodo = BuscaNaArvore(NodoRaiz, chave);
        if(nodo != nullptr and nodo->chave == chave)
        {
            return true;
        }
        return false;
    };
    
    ///////////////////////////////////////////////////////////////////////
    protected:
    int alt(Nodo<T> * nodo, int altura = 0) const
    {
        int Esquerda = 0, Direita = 0;
        if(nodo->filhoEsquerda != nullptr)
        {
            Esquerda = 1 + alt(nodo->filhoEsquerda);
        }
        if(nodo->filhoDireita != nullptr)
        {
            Direita = 1 + alt(nodo->filhoDireita);
        }

        if(Esquerda >= Direita)
        {
            altura = Esquerda;
            return altura;
        }
        altura = Direita;
        return altura;
    };

    public:
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<int> altura(T chave) const override
    {
        Nodo<T> * nodo = BuscaNaArvore(NodoRaiz, chave);
        if(nodo == nullptr)
        {
            return std::nullopt;
        }
        return alt(nodo);
    }

    ///////////////////////////////////////////////////////////////////////
    protected:
    void inse(Nodo<T> * nodo, T chave) const
    {   
        if(chave < nodo->chave)
        {
            if(nodo->filhoEsquerda == nullptr)
            {
                Nodo<T> * novoNodo = new Nodo<T>();
                novoNodo->chave = chave;
                novoNodo->altura = nodo->altura + 1;
                nodo->filhoEsquerda = novoNodo;
            }
            else
            {
                inse(nodo->filhoEsquerda, chave);
            }
        }
        else
        {
            if(nodo->filhoDireita == nullptr)
            {
                Nodo<T> * novoNodo = new Nodo<T>();
                novoNodo->chave = chave;
                novoNodo->altura = nodo->altura + 1;
                nodo->filhoDireita = novoNodo;
            }
            else
            {
                inse(nodo->filhoDireita, chave);
            }
        }
    };

    public:
    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
    void inserir(T chave) override
    {
        if(vazia())
        {
            Nodo<T> * novoNodo = new Nodo<T>();
            novoNodo->chave = chave;
            novoNodo->altura = 0;
            delete NodoRaiz;
            NodoRaiz = novoNodo;
            return;
        }
        inse(this->NodoRaiz, chave);    
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void rem(Nodo<T> * nodo, T chave) const
    {
        
    };

    public:
    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    void remover(T chave) override
    {
        this->rem(NodoRaiz, chave);
    };

    ///////////////////////////////////////////////////////////////////////
    
    public:
    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<T> filhoEsquerdaDe(T chave) const override
    {
        Nodo<T> * nodo = BuscaNaArvore(NodoRaiz, chave);
        if(nodo == nullptr or nodo->filhoEsquerda == nullptr)
        {
            return std::nullopt;
        }
        return nodo->filhoEsquerda->chave;
    };

    ///////////////////////////////////////////////////////////////////////
    
    public:
    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
    std::optional<T> filhoDireitaDe(T chave) const override
    {
        Nodo<T> * nodo = BuscaNaArvore(NodoRaiz, chave);
        if(nodo == nullptr or nodo->filhoDireita == nullptr)
        {
            return std::nullopt;
        }
        return nodo->filhoDireita->chave;
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void em(ListaEncadeadaAbstrata<T> * lista, Nodo<T> * nodo) const
    {
        if(nodo == nullptr)
        {
            return;
        }
        this->em(lista, nodo->filhoEsquerda);
        lista->adicionaNoFim(nodo->chave);
        this->em(lista, nodo->filhoDireita);
    };

    public:
    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    ListaEncadeadaAbstrata<T>* emOrdem() const override
    {
        ListaEncadeadaAbstrata<T> * emordem = new MinhaListaEncadeada<T>();
        this->em(emordem, this->NodoRaiz);
        return emordem;
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void pre(ListaEncadeadaAbstrata<T> * lista, Nodo<T> * nodo) const
    {
        if(nodo == nullptr)
        {
            return;
        }
        lista->adicionaNoFim(nodo->chave);
        this->pre(lista, nodo->filhoEsquerda);
        this->pre(lista, nodo->filhoDireita);
    };

    public:
    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    ListaEncadeadaAbstrata<T>* preOrdem() const override
    {
        ListaEncadeadaAbstrata<T> * preordem = new MinhaListaEncadeada<T>();
        this->pre(preordem, this->NodoRaiz);
        return preordem;
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void pos(ListaEncadeadaAbstrata<T> * lista, Nodo<T> * nodo) const
    {
        if(nodo == nullptr)
        {
            return;
        }
        this->pos(lista, nodo->filhoEsquerda);
        this->pos(lista, nodo->filhoDireita);
        lista->adicionaNoFim(nodo->chave);
    };

    public:
    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    ListaEncadeadaAbstrata<T>* posOrdem() const override
    {
        ListaEncadeadaAbstrata<T> * posordem = new MinhaListaEncadeada<T>();
        this->pos(posordem, this->NodoRaiz);
        return posordem;
    };
    ///////////////////////////////////////////////////////////////////////
};

#endif
