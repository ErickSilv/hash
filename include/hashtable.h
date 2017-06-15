#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <forward_list>
#include <iostream>
#include <cmath>

template<class KeyType, class DataType>
class HashEntry
{
		
	public:

		//Constructor padrão do tipo HashEntry
		HashEntry (KeyType k_, DataType d_)
			: m_key(k_)
			, m_data(d_)
		{ /* Empty */ }
		KeyType m_key;
		DataType m_data;

};

template<typename KeyType, 
		 typename DataType, 
		 typename KeyHash = std::hash<KeyType>,
		 typename KeyEqual = std::equal_to<KeyType>>

class HashTbl
{

	using Entry = HashEntry<KeyType, DataType>; 
	
	public:

		// Constructor padrão
		HashTbl(int tbl_size_ = DEFAULT_SIZE)
			: m_size (tbl_size_) 								  //!< Actual size of the table.
			, m_count(0)										  //!< Count the elements storaged int the elements.
			, m_data_table(new std::forward_list<Entry>[m_size])  //!< Store data.
		{/* Empty */}

		// Desconstructor padrão
		virtual ~HashTbl(){

			clear();
			delete [] m_data_table;

		}

		// Functions of HashTable

		/*! @brief Insere na tabela a informação contida em d_ e associada a uma chave k_ .
		 *			A classe calcula o endereço end que a informação d_ 
		 *			deve ocupar na tabela e o armazena na
		 *			lista de colisão correspondente, ou seja, 
		 *			em m_data_table[ end ].
		 *
		 * @param k_ Chave que está associada ao elemento à ser inserido.
		 * @param d_ Dados a serem inseridos na tabela.
		 *
		 * @return true caso seja o primeiro elemento associado àquela chave, senão retorna falso,
		 *			pois não é a primeira inserção associada à chave k_.
		 *
		 */
		bool insert( const KeyType & k_, const DataType & d_ );

		/*! @brief Remove um item de tabela identificado por sua chave k_ .
		 *
		 * @param k_ Chave que está associada ao elemento à ser removido.
		 *
		 * @return true caso a chave k_ seja encontrada, senão retorna falso.
		 *
		 */
		bool remove( const KeyType & k_ );

		/*! @brief Recupera em d_ a informação associada a chave k_ passada como 
		 *			argumento para o método.
		 *
		 * @param k_ Chave que está associada ao elemento à ser removido.
		 * @param d_ Parametro onde serão salvos os elementos resgatados
		 *
		 * @return true caso a chave k_ seja encontrada, senão retorna falso.
		 *
		 */
		bool retrieve( const KeyType & k_, DataType & d_ ) const;

		/*! @brief Verifica se a tabela está vazia 
		 *
		 * @return true se a tabela de dispersão estiver vazia, ou false caso contrário.
		 *
		 */
		bool empty( void ) const;

		/*! @brief Libera toda a memória associada às listas de colisão da tabela, removendo todos
		 *			seus elementos.
		 *
		 */
		void clear( void );

		/*! @brief Imprime a tabela toda, com formatação.
		 *
		 */
		void print() const;

		/*! @brief Busca o tamanho da tabela.
		 *
		 * @return Tamanho da tabela de dispersão.
		 */
		size_t size( void );

		/*! @brief Busca a quantidade de elementos da tabela.
		 *
		 * @return Quantidade de elemento atualmente armazenados na tabela.
		 */
		unsigned long int count( void ) const;

	private:
		/*! @brief É um método privado que deve ser chamado quando o fator de carga 'λ' for maior
		 *			que 1.0. O fator de carga é a razão entre o número de elementos na tabela e seu tamanho.
		 *			Este método vai criar uma nova tabela cujo tamanho será igual ao menor número primo maior
		 *			que o dobro do tamanho da tabela antes da chamada rehash().
		 *
		 */
		void rehash();

		unsigned int m_size;
		unsigned int m_count;
		std::forward_list< Entry > * m_data_table;
		static const short DEFAULT_SIZE = 11;

};

#include "hashtable.inl"

#endif