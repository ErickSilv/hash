#include <iostream>
#include "./hashtable.h"

// >>> Beginning of prime functions. <<< //
bool is_prime( int n ){

	if( n == 0 || n == 1 )
	{
		return false;
	}

	//Verifica se n é primo.
    for( auto i(2); i <= std::sqrt(n); ++i )
    {
        if ( n % i == 0 ) 
        {
            return false;
        }
    }
  	return true;

}

int next_prime( int n ){

	//Calcula o pŕoximo primo disponível.
	while( not is_prime(n) ){
		++n;
	}

	//Após todas chamadas retorna o primo encontrado.
	return n;
}
// >>> Ending of prime functions. <<< //

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert( const KeyType & k_, const DataType & d_ )
{
	//Se a tabela estiver cheia, chamar o rehash()
	if( m_count == m_size )
	{
		rehash();
	}

	// Functors.
	KeyHash func_hash;
	KeyEqual func_equal;
	
	// Calcula a nova entrada para a tabela.
	Entry new_entry( k_, d_ );
	
	// Calcula o endereço com base na chave.
	auto address = func_hash( k_ ) % m_size;
	
	// Tenta inserir o novo elemento na tabela.
	if( m_data_table[ address ].empty() )
	{
		m_data_table[ address ].push_front( new_entry );
		m_count++;
		return true;

	}
	else
	{
		// Definindo o range [first, last) da tabela 
		auto first = m_data_table[ address ].begin();
		auto last = m_data_table[ address ].end();

		for( /*Empty*/; first != last; ++first )
		{
			if( func_equal( (*first).m_key, new_entry.m_key ) )
			{
				(*first).m_data = d_;
				return false;
			}
		}

		//Alocando a nova inserção na tabela
		m_data_table[ address ].push_front( new_entry );

		//Incrementando a quantidade de elementos.
		++m_count;
		return true;
	}

}


template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove( const KeyType & k_ )
{
	// Functors.
	KeyHash func_hash;
	KeyEqual func_equal;
	
	// Calcula o endereço com base na chave.
	auto address = func_hash( k_ ) % m_size;

	// Define o range da tabela [first, last), além do elemento a ser removido.
	auto tb = m_data_table[ address ].before_begin(); 
	auto first = m_data_table[ address ].begin();
	auto last = m_data_table[ address ].end();
	
	// Verifica se no endereço onde a chave supostamente deveria estar tem dados.
	if( m_data_table[ address ].empty() )
	{
		return false;
	}

	// Percorrendo a tabela até achar a chave.
	for( /*Empty*/; first != last; ++first )
	{
		if( func_equal( (*first).m_key, k_ ) )
		{	
			//Apagando os dados da respectiva chave.
			m_data_table[ address ].erase_after( tb );

			//Avançará na lista do endereço address.
			++tb;

			//Decrementando a quantidade de elementos.
			--m_count;
			return true;
		}

	}
	return false;

}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
size_t HashTbl<KeyType, DataType, KeyHash, KeyEqual>::size()
{
	return m_size;
}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash(){

	KeyHash func_hash;
	
	// Define o tamanho da tabela para o próximo primo maior que o atual.
	auto new_size = next_prime( m_size*2 );
	//Aloca memória de uma nova tabela com o novo tamanho.
	auto new_table = new std::forward_list<Entry>[ new_size ];

	// Copia os elementos para a nova tabela.
	for( auto i(0ul); i != m_size; ++i )
	{
		// Define o range [first, last) da tabela. 
		auto first = m_data_table[ i ].begin();
		auto last = m_data_table[ i ].end();

		// Recalcula os endereços e insere na nova tabela os elementos da antiga.
		for(/* Empty */; first != last; ++first )
		{
			auto address = func_hash( (*first).m_key ) % new_size;
			new_table[ address ].push_front(*first);
		}
	}

	//Deleta a antiga tabela.
	delete [] m_data_table;

	// Redefine a tabela e o tamanho.
	m_data_table = new_table;
	m_size = new_size;

}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve( const KeyType & k_, DataType & d_ ) const
{
	// Functors.
	KeyHash func_hash;
	KeyEqual func_equal;

	// Calcula o endereço;
	auto address = func_hash(k_)%m_size;
	
	// Verifica se naquele endereço há dados.
	if( m_data_table[ address ].empty() )
	{
		return false;
	}

	
	// Define o range [first, last) da tabela. 
	auto first = m_data_table[ address ].begin();
	auto last = m_data_table[ address ].end();
	
	// Recuperando os dados dentro do range.
	for( /*Empty*/; first != last; ++first )
	{
		if( func_equal( (*first).m_key, k_) ){
			d_ = (*first).m_data;
			return true;
		}
	}
	return false;

}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear( void )
{
	//Percorre e limpa posição à posição da tabela.
	for( auto i(0ul); i < m_size; ++i ){
		m_data_table[ i ].clear();
	}

}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty( void ) const
{
	//Percorre a tabela e caso haja endereço onde tenha dados, então não está vazia.
	for( auto i(0ul); i < m_size; ++i )
	{
		if( not m_data_table[ i ].empty() ){
			return false;
		}
	}
	return true;

}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
unsigned long int HashTbl<KeyType, DataType, KeyHash, KeyEqual>::count( void ) const
{
	return m_count;
}

template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::print() const
{

	//Cabeçalho
	std::cout << "======================= Accounts =======================\n";
	std::cout << "| Key |    Name    | Bank | Agency | Account | Balance |\n";
	std::cout << "--------------------------------------------------------\n";

	for( auto i(0ul); i < m_size; ++i )
	{
		//Define o range [first, last) da tabela. 
		auto first = m_data_table[ i ].begin();
		auto last = m_data_table[ i ].end();
		
		//Imprime os dados do iterator first na posição atual.
		for(/* Empty */; first != last; ++first )
		{
			auto data = (*first).m_data;
			std::cout << "|  " << i;
			std::cout << "  \a|  " << data.client_name;
			std::cout << "  |   " << data.bank;
			std::cout << "  |  " << data.agency;
			std::cout << "  |  " << data.n_account;
			std::cout << "  | " << data.balance << " |\n";
		}
	}

}