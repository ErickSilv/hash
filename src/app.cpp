#include <iostream>
#include <string>
#include <tuple>
#include "../include/hashtable.h"

using AcctKey = std::tuple<std::string, int, int, int>;

// Struct de uma conta no banco.
struct Account
{

	// Parametros de uma conta.
	AcctKey key;
	std::string client_name;
	int bank;
	int agency;
	int n_account;
	float balance;

	//Construtor padrão.
	Account( std::string c_n = "N", int bk = 0, int agc = 0000, int n_acc = 0000, float blc = 00.00 )
		: key(c_n, bk, agc, n_acc)
		, client_name(c_n)
		, bank(bk)
		, agency(agc)
		, n_account(n_acc)
		, balance(blc)
	{/* Empty */}

	// Retorna a chave
	AcctKey get_key( void ){
		return key;
	}

};

// Functor primária, do cliente.
struct KeyHash
{
	//Sobrecarga para obter a chave.
	size_t operator()( const AcctKey & k_ ) const
	{

		auto c_n = std::get<0>(k_);
		auto bk = std::get<1>(k_);
		auto agc = std::get<2>(k_);
		auto n_acc = std::get<3>(k_);

		return std::hash<std::string>()(c_n) xor
			   std::hash<int>()(bk) xor
			   std::hash<int>()(agc) xor
			   std::hash<int>()(n_acc);

	}

};

// Functor para comparar Chaves.
struct KeyEqual
{
	
	bool operator()( const AcctKey & lhs, const AcctKey & rhs ) const
	{
		return lhs == rhs;
	}

};

int main(){

	HashTbl<AcctKey, Account, KeyHash, KeyEqual> bank_table;

	// Preenchendo a tabela
	Account conta_1 = { "Erick   ",    1, 3404, 29157, 3578.99 };
	Account conta_2 = { "Anderson",    7, 6512, 54982, 8895.89 };
	Account conta_3 = { "Caio    ",    6, 1658, 34897, 4782.73 };
	Account conta_4 = { "Rayan   ",    5, 7985, 16589, 1025.26 };
	Account conta_5 = { "Luis    ",    2, 4462, 76538, 7985.41 };
	Account conta_6 = { "Bianca  ",    3, 5678, 76538, 3000.19 };

	// Insert
	std::cout << ">>> Inserindo as contas <<< \n";
	bank_table.insert( conta_1.get_key(), conta_1 );
	bank_table.insert( conta_2.get_key(), conta_2 );
	bank_table.insert( conta_3.get_key(), conta_3 );
	bank_table.insert( conta_4.get_key(), conta_4 );
	bank_table.insert( conta_5.get_key(), conta_5 );
	bank_table.insert( conta_6.get_key(), conta_6 );

	// Print
	bank_table.print();
	std::cout << std::endl;
	
	// Remove
	std::cout << ">>> Removendo usuários : " << conta_3.client_name << ", " << conta_6.client_name << " <<< \n";
	bank_table.remove( conta_3.get_key() );
	bank_table.remove( conta_6.get_key() );
	bank_table.print();
	std::cout << std::endl;

	/// Retrive
	std::cout << ">>> Recuperando dados do usuario 2 <<< \n";
	
	//Receberá os dados recuperados
	Account conta;
	bank_table.retrieve( conta_2.get_key(), conta );
	std::cout << ">>> Usuario 2 <<< \nNome : " << conta.client_name << "\n";
	std::cout << "Banco : " << conta.bank << "\n";
	std::cout << "Agencia : " << conta.agency << "\n";
	std::cout << "Account Nº : " << conta.n_account << "\n";
	std::cout << "Balance : " << conta.balance << "\n";

	std::cout << std::endl;

	// Testando o redimensionamento de tabela.
	std::cout << ">>> Redimensionando a tabela <<< \n";
	HashTbl<AcctKey, Account, KeyHash, KeyEqual> bank_table2(5);

	//Criando uma nova tabela para teste de Redimensionamento.
	Account c_conta_1 = { "Erick   ",     1, 3404, 29157, 3578.99 };
	Account c_conta_2 = { "Anderson",     7, 6512, 54982, 8895.89 };
	Account c_conta_3 = { "Gabriel ",     6, 1658, 34897, 4782.73 };
	Account c_conta_4 = { "Rayan   ",     5, 7985, 16589, 1025.26 };
	Account c_conta_5 = { "Luis    ",     4, 4462, 76538, 7985.41 };
	Account c_conta_6 = { "Bianca  ",     3, 5678, 76538, 3000.19 };

	bank_table2.insert( c_conta_1.get_key(), c_conta_1 );
	bank_table2.insert( c_conta_2.get_key(), c_conta_2 );
	bank_table2.insert( c_conta_3.get_key(), c_conta_3 );
	bank_table2.insert( c_conta_4.get_key(), c_conta_4 );
	bank_table2.insert( c_conta_5.get_key(), c_conta_5 );


	std::cout << std::endl;

	std::cout << "Tamanho com as primeiras inserções de usuarios: " << bank_table2.size() << "\n";
	std::cout << "Quantidade de usuarios: " << bank_table2.count() << "\n";
	bank_table2.print();
	std::cout << std::endl;


	bank_table2.insert( c_conta_6.get_key(), c_conta_6 );
	std::cout << "Novo tamanho após inserção de mais um usuario: " << bank_table2.size() << "\n";
	std::cout << "Quantidade de usuarios: " << bank_table2.count() << "\n";
	bank_table2.print();
	

}