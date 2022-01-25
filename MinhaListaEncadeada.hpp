#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.hpp"

template <typename T>
class MinhaListaEncadeada :  public ListaEncadeadaAbstrata<T>
{
    public:
    ~MinhaListaEncadeada() override
    {
        for(Elemento<T>  * aux = this->_primeiro;
            aux != nullptr;)
        {
            Elemento<T> * destruir = aux;
            aux = aux->_proximo;
            delete destruir;
        }
    };

    bool estaVazia() override
    {
        if(getTamanho() == 0 or this->_primeiro == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    int getTamanho() override
    {
        return this->_tamanho;
    };

    int posicao(T umDado) override
    {
        if(estaVazia())
    {
        throw lista_encadeada_vazia_exception{};
    }
    int pos = 0;
    for(Elemento<T> * elemento = this->_primeiro;
        elemento != nullptr; 
        elemento = elemento->_proximo, pos++)
        {
        if(umDado == elemento->_dado)
            {
                return pos;
            }
        }
    throw posicao_invalida_exception{};
    };

    bool contem(T umDado) override
    {
        for(Elemento<T> * elemento = this->_primeiro;
        elemento != nullptr; 
        elemento = elemento->_proximo)
        {
        if(umDado == elemento->_dado)
            {
                return true;
            }
        }
    return false;
    };

    void adicionaNoInicio(T umDado) override
    {
        Elemento<T> * novoElemento = new Elemento<T>();
        novoElemento->_dado = umDado;
        novoElemento->_proximo = this->_primeiro;
        this->_primeiro = novoElemento;
        this->_tamanho ++;
    };

    void adicionaNaPosicao(T umDado, int umaPosicao)
    { 
        if(umaPosicao < 0 or umaPosicao > getTamanho())
        {
            throw posicao_invalida_exception();
        }
        if(umaPosicao == 0)
        {
            this->adicionaNoInicio(umDado);
            return;
        }
        if(umaPosicao == getTamanho())
        {
            this->adicionaNoFim(umDado);
            return;
        }
        Elemento<T>  * Eauxiliar = this->_primeiro;
        for(int i = 1; i < umaPosicao;
        Eauxiliar = Eauxiliar->_proximo, i++){}

        Elemento<T> * novoElemento = new Elemento<T>();
        novoElemento->_dado = umDado;
        novoElemento->_proximo = Eauxiliar->_proximo;
        Eauxiliar->_proximo = novoElemento;
        this->_tamanho ++;
    };

    void adicionaNoFim(T umDado) override
    {
        if(estaVazia())
        {   
            adicionaNoInicio(umDado);
            return;
        }
        Elemento<T>  * ultimo = this->_primeiro;
        while(ultimo->_proximo != nullptr)
        {
            ultimo = ultimo->_proximo;
        }
        Elemento<T>  * novoElemento = new Elemento<T>();
        novoElemento->_dado = umDado;
        novoElemento->_proximo = nullptr;
        ultimo->_proximo = novoElemento;
        this->_tamanho ++;
    };

    T retiraDoInicio() override
    {
        if(estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }
        Elemento<T>  * elemento = this->_primeiro;
        T dado = elemento->_dado;
        this->_primeiro = elemento->_proximo;
        delete elemento;
        this->_tamanho --;
        return dado;
    };

    T retiraDaPosicao(int umaPosicao) override
    {
        if(umaPosicao < 0 or umaPosicao >= getTamanho())
        {
            throw posicao_invalida_exception();
        }
        if(umaPosicao == 0)
        {
            return this->retiraDoInicio();
        }
        if(umaPosicao == getTamanho() - 1)
        {
            return this->retiraDoFim();
        }
        Elemento<T>  * aux = this->_primeiro;
        for(int i = 1; i < umaPosicao;
        aux = aux->_proximo, i++) {}
        Elemento<T>  * deletar = aux->_proximo;
        aux->_proximo = deletar->_proximo;
        T dado = deletar->_dado;
        delete deletar;
        this->_tamanho --;
        return dado;
    };

    T retiraDoFim() override
    {
        if(estaVazia())
        {
            throw lista_encadeada_vazia_exception();
        }
        if(getTamanho() == 1)
        {
            return this->retiraDoInicio();
        }
        Elemento<T>  * pultimo = this->_primeiro;
        for(int i = 0; i < getTamanho() - 2;
        pultimo = pultimo->_proximo, i++) {}
        Elemento<T>  * ultimo = pultimo->_proximo;
        T dado = ultimo->_dado;
        pultimo->_proximo = nullptr;
        delete ultimo;
        this->_tamanho --;
        return dado;
    };

    T retiraEspecifico(T umDado) override
    {
        return this->retiraDaPosicao(this->posicao(umDado));
    };
};

#endif