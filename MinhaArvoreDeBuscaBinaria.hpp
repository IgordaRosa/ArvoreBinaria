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
        if(this->NodoRaiz == nullptr)
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
    protected:
    bool cont(Nodo<T> * nodo, T chave) const
    {
        if(vazia())
        {
            return false;
        }
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
        if(nodo->chave == chave)
        {
            return true;
        }
        return false;
    };

    public:
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    bool contem(T chave) const override
    {
        return cont(this->NodoRaiz, chave);
    };
    
    ///////////////////////////////////////////////////////////////////////
    protected:
    int alt(Nodo<T> * nodo,T chave) const
    {   
        if(vazia())
        {
            return 0;
        }
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
        if(nodo->chave == chave)
        {
            return AlturaDaArvore(nodo);
        }
        return -50;
    };

    int AlturaDaArvore(Nodo<T> * nodo, int altura = 0, int Direita = 0, int Esquerda = 0) const
    {
        if(nodo == nullptr)
        {
            return altura;
        }
        Esquerda = AlturaDaArvore(nodo->filhoDireita, altura + 1);
        Direita = AlturaDaArvore(nodo->filhoEsquerda, altura + 1);

        if(Direita <= Esquerda)
        {
            return Direita;   
        }
        else
        {
            return Esquerda; 
        }
    }

    public:
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<int> altura(T chave) const override
    {
        if(contem(chave))
        {
            return alt(NodoRaiz, chave);
        }
        return std::nullopt;
    };

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
        if(vazia())
        {
            return;
        }
        while(nodo->filhoDireita != nullptr and nodo->filhoEsquerda != nullptr and nodo->filhoEsquerda->chave != chave and nodo->filhoDireita->chave != chave)
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
        if(nodo->chave == chave)
            {
                this->RaizContem(nodo, chave);
                return;
            }
        
        if(nodo->filhoDireita->chave == chave)
            {
                this->FDContem(nodo, chave);
                return;
            }
        
        if(nodo->filhoEsquerda->chave == chave)
            {
                this->FEContem(nodo, chave);
                return;
            }
    };

    void RaizContem(Nodo<T> * nodo, T chave) const
    {

    };

    void FEContem(Nodo<T> * nodo, T chave) const
    {

    };

    void FDContem(Nodo<T> * nodo, T chave) const
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
    protected:
    std::optional<T> FE(Nodo<T> * nodo, T chave) const
    {
        if(vazia())
        {
            return std::nullopt;
        }
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
        if(nodo->chave == chave)
            {
                return nodo->filhoEsquerda->chave;
            }
        return std::nullopt;
    };
    
    public:
    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<T> filhoEsquerdaDe(T chave) const override
    {
        return FE(NodoRaiz, chave);
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    std::optional<T> FD(Nodo<T> * nodo, T chave) const
    {
        if(vazia())
        {
            return std::nullopt;
        }
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
        if(nodo->chave == chave)
            {
                return nodo->filhoDireita->chave;
            }
        return std::nullopt;
    };
    
    public:
    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
    std::optional<T> filhoDireitaDe(T chave) const override
    {
        return FD(NodoRaiz, chave);
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void em(MinhaListaEncadeada<T> * lista, Nodo<T> * nodo) const
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
        MinhaListaEncadeada<T> * emordem = new MinhaListaEncadeada<T>();
        this->em(emordem, this->NodoRaiz);
        return emordem;
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void pre(MinhaListaEncadeada<T> * lista, Nodo<T> * nodo) const
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
        MinhaListaEncadeada<T> * preordem = new MinhaListaEncadeada<T>();
        this->pre(preordem, this->NodoRaiz);
        return preordem;
    };

    ///////////////////////////////////////////////////////////////////////
    protected:
    void pos(MinhaListaEncadeada<T> * lista, Nodo<T> * nodo) const
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
        MinhaListaEncadeada<T> * posordem = new MinhaListaEncadeada<T>();
        this->pos(posordem, this->NodoRaiz);
        return posordem;
    };
    ///////////////////////////////////////////////////////////////////////
};

#endif
